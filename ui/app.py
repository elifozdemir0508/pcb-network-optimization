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
    {'selector': ':selected', 'style': {'background-color': '#FF4136', 'line-color': '#FF4136', 'border-width': 2, 'border-color': 'black'}}, 
    {'selector': 'edge', 'style': {'line-color': '#CCCCCC', 'width': 2, 'opacity': 0.8, 'label': 'data(weight)', 'text-rotation': 'autorotate', 'font-size': '10px'}}, 
    {'selector': '.mst-edge', 'style': {'line-color': '#2ECC40', 'width': 5, 'opacity': 1, 'transition-property': 'line-color, width', 'transition-duration': '0.8s', 'z-index': 5}} 
]

app.layout = html.Div([
    html.H2("PCB Bağlantı Ağı Optimizasyonu", style={'textAlign': 'center', 'fontFamily': 'Arial'}),
    
    html.Div([
        html.Button('Yeni Düğüm Ekle', id='btn-dugum-ekle', n_clicks=0, style={'marginRight': '10px', 'padding': '8px', 'cursor': 'pointer'}),
        html.Button('Seçili 2 Düğümü Bağla', id='btn-kenar-ekle', n_clicks=0, style={'marginRight': '10px', 'padding': '8px', 'cursor': 'pointer'}),
        html.Button('Seçili Kenarı Sil', id='btn-kenar-sil', n_clicks=0, style={'marginRight': '10px', 'padding': '8px', 'backgroundColor': '#FF851B', 'color': 'white', 'cursor': 'pointer'}),
        html.Button('C Servisine Gönder (Hesapla)', id='btn-hesapla', n_clicks=0, style={'marginRight': '15px', 'padding': '8px', 'backgroundColor': '#2ECC40', 'color': 'white', 'fontWeight': 'bold', 'cursor': 'pointer'}),
        
        html.Div(id='sistem-mesaji', style={'marginTop': '15px', 'fontWeight': 'bold', 'color': '#333'}),
        
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


# ---------------------------------------------------------
# Yazar: Evin Yılmaz
# Açıklama: Graf üzerindeki mevcut kenarların ağırlıklarını,
# düğümlerin güncel 2D koordinatlarına göre yeniden hesaplar.
# ---------------------------------------------------------
def kenar_agirliklarini_guncelle(elemanlar):
    dugum_konumlari = {e['data']['id']: e['position'] for e in elemanlar if 'source' not in e['data'] and 'position' in e}
    for e in elemanlar:
        if 'source' in e['data']:
            src = e['data']['source']
            tgt = e['data']['target']
            if src in dugum_konumlari and tgt in dugum_konumlari:
                p1 = dugum_konumlari[src]
                p2 = dugum_konumlari[tgt]
                mesafe = math.sqrt((p2['x'] - p1['x'])**2 + (p2['y'] - p1['y'])**2)
                e['data']['weight'] = round(mesafe, 2)
    return elemanlar


# ---------------------------------------------------------
# Yazar: Evin Yılmaz
# Açıklama: Düğüm/kenar manipülasyonlarını, sürükleme olaylarını
# ve C mikroservis girdi/çıktı süreçlerini yöneten ana callback.
# ---------------------------------------------------------
@app.callback(
    Output('graf-ekrani', 'elements'),
    Output('sistem-mesaji', 'children'),
    Input('btn-dugum-ekle', 'n_clicks'),
    Input('btn-kenar-ekle', 'n_clicks'),
    Input('btn-kenar-sil', 'n_clicks'),
    Input('btn-hesapla', 'n_clicks'),
    Input('dosya-dinleyici', 'n_intervals'),
    Input('graf-ekrani', 'dragNodeEnd'),
    State('graf-ekrani', 'elements'),
    State('graf-ekrani', 'selectedNodeData'),
    State('graf-ekrani', 'selectedEdgeData')
)
def arayuz_yoneticisi(btn_dugum, btn_kenar, btn_sil, btn_hesapla, interval_tetik, drag_sonu, mevcut_elemanlar, secili_dugumler, secili_kenarlar):
    tetikleyen_olay = dash.ctx.triggered_id
    mesaj = "Sistem hazır. Shift tuşuna basılı tutarak birden fazla düğüm/kenar seçebilirsiniz."
    
    if mevcut_elemanlar is None:
        mevcut_elemanlar = []

    # 1. OLAY: KULLANICI YENİ DÜĞÜM EKLEDİ
    if tetikleyen_olay == 'btn-dugum-ekle':
        dugumler = [eleman for eleman in mevcut_elemanlar if 'source' not in eleman['data']]
        yeni_id = str(len(dugumler))
        yeni_x = 100 + (btn_dugum * 75 % 600)
        yeni_y = 100 + (btn_dugum * 45 % 400)
        mevcut_elemanlar.append({'data': {'id': yeni_id, 'label': f'N{yeni_id}'}, 'position': {'x': yeni_x, 'y': yeni_y}})
        mesaj = f"Yeni düğüm (N{yeni_id}) eklendi. Bağlamak istediğiniz 2 düğümü seçip 'Bağla' butonuna basınız."
        return mevcut_elemanlar, mesaj

    # 2. OLAY: MANUEL KENAR EKLEME
    elif tetikleyen_olay == 'btn-kenar-ekle':
        if secili_dugumler and len(secili_dugumler) == 2:
            n1_id, n2_id = secili_dugumler[0]['id'], secili_dugumler[1]['id']
            
            kenar_var = any('source' in e['data'] and ((e['data']['source'] == n1_id and e['data']['target'] == n2_id) or (e['data']['source'] == n2_id and e['data']['target'] == n1_id)) for e in mevcut_elemanlar)
            if kenar_var:
                return mevcut_elemanlar, "Uyarı: Bu iki düğüm arasında zaten bir bağlantı var!"

            pos1, pos2 = None, None
            for e in mevcut_elemanlar:
                if 'source' not in e['data']:
                    if e['data']['id'] == n1_id: pos1 = e['position']
                    if e['data']['id'] == n2_id: pos2 = e['position']

            if pos1 and pos2:
                mesafe = math.sqrt((pos2['x'] - pos1['x'])**2 + (pos2['y'] - pos1['y'])**2)
                yeni_kenar = {'data': {'source': n1_id, 'target': n2_id, 'weight': round(mesafe, 2)}}
                mevcut_elemanlar.append(yeni_kenar)
                mesaj = f"Başarılı: N{n1_id} ve N{n2_id} arasına kenar eklendi."
        else:
            mesaj = "Hata: Kenar eklemek için graf üzerinden tam olarak 2 düğüm seçmelisiniz."
        return mevcut_elemanlar, mesaj

    # 3. OLAY: KENAR SİLME
    elif tetikleyen_olay == 'btn-kenar-sil':
        if secili_kenarlar:
            silinecek_idler = [(k['source'], k['target']) for k in secili_kenarlar]
            mevcut_elemanlar = [e for e in mevcut_elemanlar if not ('source' in e['data'] and (e['data']['source'], e['data']['target']) in silinecek_idler)]
            mesaj = f"{len(silinecek_idler)} adet kenar silindi."
        else:
            mesaj = "Hata: Silmek için graf üzerinden bir kenar seçmelisiniz."
        return mevcut_elemanlar, mesaj

    # 4. OLAY: DÜĞÜM SÜRÜKLENDİ (Konum Değiştiğinde Mesafeleri Dinamik Güncelle)
    elif tetikleyen_olay == 'graf-ekrani':
        mevcut_elemanlar = kenar_agirliklarini_guncelle(mevcut_elemanlar)
        mesaj = "Bileşen konumu değiştirildi; bağlantı mesafeleri dinamik olarak güncellendi."
        return mevcut_elemanlar, mesaj

    # 5. OLAY: HESAPLA (C SERVİSİNE GÖNDER)
    elif tetikleyen_olay == 'btn-hesapla':
        # Göndermeden önce konumları ve mesafeleri son kez doğrula
        mevcut_elemanlar = kenar_agirliklarini_guncelle(mevcut_elemanlar)
        
        dugumler = [e for e in mevcut_elemanlar if 'source' not in e['data']]
        kenarlar = [e for e in mevcut_elemanlar if 'source' in e['data']]

        export_data = {
            "request_meta": {"algorithm": "kruskal", "action": "calculate_mst", "node_count": len(dugumler), "edge_count": len(kenarlar)},
            "nodes": [{"id": int(d['data']['id']), "x": d['position']['x'], "y": d['position']['y']} for d in dugumler],
            "edges": [{"source": int(k['data']['source']), "target": int(k['data']['target']), "weight": float(k['data']['weight'])} for k in kenarlar]
        }

        with open(os.path.join(SHARED_DIR, "input_graph.json"), 'w', encoding='utf-8') as f:
            json.dump(export_data, f, indent=4)
            
        with open(os.path.join(SHARED_DIR, "calculate.flag"), 'w', encoding='utf-8') as f:
            f.write("ready")

        for e in mevcut_elemanlar:
            e['classes'] = ''

        mesaj = "Güncel graf koordinatları kaydedildi. C servisine hesaplama emri verildi..."
        return mevcut_elemanlar, mesaj

    # 6. OLAY: ZAMANLAYICI KONTROLÜ (C'den gelen sonucu okuma)
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
                
                os.remove(mst_dosyasi)
                
            except Exception as e:
                mesaj = "C servisinden veri okunurken veya işlenirken hata oluştu."
                
    return mevcut_elemanlar, mesaj

if __name__ == '__main__':
    # Modern Dash standartlarına uygun çalıştırma
    app.run(debug=True, host='0.0.0.0', port=8050)
