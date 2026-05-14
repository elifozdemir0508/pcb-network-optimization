import dash
from dash import html, dcc, Input, Output, State
import dash_cytoscape as cyto
import json
import math
import os

# Dash uygulamasını başlat
app = dash.Dash(__name__)

# C Servisi ile haberleşmek için ortak Docker klasörü
SHARED_DIR = "shared_data"
if not os.path.exists(SHARED_DIR):
    os.makedirs(SHARED_DIR)

# Görselleştirme Stilleri
stil_sayfasi = [
    {'selector': 'node', 'style': {'content': 'data(label)', 'background-color': '#0074D9', 'color': 'white', 'text-valign': 'center', 'font-size': '12px', 'z-index': 10}},
    {'selector': 'edge', 'style': {'line-color': '#CCCCCC', 'width': 2, 'opacity': 0.3}}, 
    {'selector': '.mst-edge', 'style': {'line-color': '#2ECC40', 'width': 5, 'opacity': 1, 'transition-property': 'line-color, width', 'transition-duration': '0.8s', 'z-index': 5}} 
]

app.layout = html.Div([
    html.H2("PCB Bağlantı Ağı Optimizasyonu", style={'textAlign': 'center', 'fontFamily': 'Arial'}),
    
    html.Div([
        html.Button('Yeni Bileşen (Düğüm) Ekle', id='btn-dugum-ekle', n_clicks=0, style={'marginRight': '15px', 'padding': '10px', 'cursor': 'pointer'}),
        html.Div(id='sistem-mesaji', style={'marginTop': '15px', 'fontWeight': 'bold', 'color': '#333'}),
        
        # Arka planda C servisinden gelen dosyayı dinleyen gizli zamanlayıcı
        dcc.Interval(id='dosya-dinleyici', interval=2000, n_intervals=0)
    ], style={'padding': '20px', 'backgroundColor': '#f8f9fa', 'borderBottom': '2px solid #dee2e6'}),

    cyto.Cytoscape(
        id='graf-ekrani',
        layout={'name': 'preset'},
        style={'width': '100%', 'height': '600px', 'border': '1px solid #ccc'},
        stylesheet=stil_sayfasi,
        elements=[]
    )
], style={'fontFamily': 'Arial'})

@app.callback(
    Output('graf-ekrani', 'elements'),
    Output('sistem-mesaji', 'children'),
    Input('btn-dugum-ekle', 'n_clicks'),
    Input('dosya-dinleyici', 'n_intervals'),
    State('graf-ekrani', 'elements')
)
def arayuz_yoneticisi(btn_tiklanma, interval_tetik, mevcut_elemanlar):
    tetikleyen_olay = dash.ctx.triggered_id
    mesaj = "Sistem hazır. Yeni bileşen eklenebilir veya C servisinden MST yanıtı beklenebilir."
    
    # 1. OLAY: KULLANICI YENİ DÜĞÜM EKLEDİ
    if tetikleyen_olay == 'btn-dugum-ekle' and btn_tiklanma > 0:
        dugumler = [eleman for eleman in mevcut_elemanlar if 'source' not in eleman['data']]
        yeni_id = str(len(dugumler))
        
        yeni_x = 100 + (btn_tiklanma * 75 % 600)
        yeni_y = 100 + (btn_tiklanma * 45 % 400)
        dugumler.append({'data': {'id': yeni_id, 'label': f'N{yeni_id}'}, 'position': {'x': yeni_x, 'y': yeni_y}})

        kenarlar = []
        for i in range(len(dugumler)):
            for j in range(i + 1, len(dugumler)):
                n1, n2 = dugumler[i], dugumler[j]
                mesafe = math.sqrt((n2['position']['x'] - n1['position']['x'])**2 + (n2['position']['y'] - n1['position']['y'])**2)
                kenarlar.append({'data': {'source': n1['data']['id'], 'target': n2['data']['id'], 'weight': round(mesafe, 2)}})
        
        # C ekibi için girdiyi hazırla
        export_data = {
            "request_meta": {"algorithm": "kruskal", "action": "calculate_mst", "node_count": len(dugumler)},
            "nodes": [{"id": int(d['data']['id']), "x": d['position']['x'], "y": d['position']['y']} for d in dugumler],
            "edges": [{"source": int(k['data']['source']), "target": int(k['data']['target']), "weight": k['data']['weight']} for k in kenarlar]
        }

        # ÖNCE JSON DOSYASINI YAZ
        with open(os.path.join(SHARED_DIR, "input_graph.json"), 'w', encoding='utf-8') as f:
            json.dump(export_data, f, indent=4)
            
        # JSON YAZMA İŞLEMİ BİTTİKTEN SONRA FLAG DOSYASINI OLUŞTUR (C servisini tetikler)
        with open(os.path.join(SHARED_DIR, "calculate.flag"), 'w', encoding='utf-8') as f:
            f.write("ready")
        
        return dugumler + kenarlar, f"Yeni grafik ({len(dugumler)} düğüm) oluşturuldu. C servisine hesaplama emri verildi."

    # 2. OLAY: ZAMANLAYICI C SERVİSİNİN YANITINI KONTROL EDİYOR
    elif tetikleyen_olay == 'dosya-dinleyici':
        mst_dosyasi = os.path.join(SHARED_DIR, "output_mst.json")
        if os.path.exists(mst_dosyasi):
            try:
                with open(mst_dosyasi, 'r', encoding='utf-8') as f:
                    mst_verisi = json.load(f)
                
                mst_kenarlari = [(str(edge['source']), str(edge['target'])) for edge in mst_verisi.get('mst_edges', [])]
                
                for eleman in mevcut_elemanlar:
                    if 'source' in eleman['data']:
                        src, tgt = str(eleman['data']['source']), str(eleman['data']['target'])
                        if (src, tgt) in mst_kenarlari or (tgt, src) in mst_kenarlari:
                            eleman['classes'] = 'mst-edge'
                        else:
                            eleman['classes'] = '' 

                maliyet = mst_verisi.get('response_meta', {}).get('total_cost', "Bilinmiyor")
                mesaj = f"✅ MST Başarıyla Çizildi! Toplam Bağlantı Maliyeti: {maliyet}"
            except Exception as e:
                mesaj = "C servisinden veri okunurken veya işlenirken hata oluştu."
                
    return mevcut_elemanlar, mesaj

if __name__ == '__main__':
    app.run_server(debug=True, host='0.0.0.0', port=8050)
