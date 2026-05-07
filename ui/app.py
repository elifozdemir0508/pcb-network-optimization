import dash
from dash import html, dcc, Input, Output, State
import dash_cytoscape as cyto
import json

# Dash uygulamasını başlat
app = dash.Dash(__name__)

# Başlangıç için örnek veri (Faz 3 testleri için)
baslangic_dugumleri = [
    {'data': {'id': '0', 'label': 'Bileşen 0'}, 'position': {'x': 100, 'y': 200}},
    {'data': {'id': '1', 'label': 'Bileşen 1'}, 'position': {'x': 350, 'y': 400}}
]

# Görselleştirme Stilleri (MST kenarları burada yeşil olacak)
stil_sayfasi = [
    # Düğüm stili
    {
        'selector': 'node',
        'style': {
            'content': 'data(label)',
            'background-color': '#0074D9',
            'color': 'white',
            'text-valign': 'center',
            'font-size': '12px'
        }
    },
    # Varsayılan kenar (bağlantı) stili
    {
        'selector': 'edge',
        'style': {
            'line-color': '#CCCCCC',
            'width': 2
        }
    },
    # MST bulunduğunda kenarlara eklenecek 'mst-edge' sınıfının stili
    {
        'selector': '.mst-edge',
        'style': {
            'line-color': '#2ECC40', # Yeşil renk
            'width': 4,
            'transition-property': 'line-color, width',
            'transition-duration': '0.5s' # Animasyon hissi için
        }
    }
]

# Arayüz Tasarımı (Layout)
app.layout = html.Div([
    html.H2("PCB Bağlantı Ağı Optimizasyonu (MST Görselleştirme)", style={'textAlign': 'center', 'fontFamily': 'Arial'}),
    
    # Kontrol Paneli (Butonlar)
    html.Div([
        html.Button('Yeni Düğüm Ekle', id='btn-dugum-ekle', n_clicks=0, style={'marginRight': '15px', 'padding': '10px'}),
        html.Button('MST Hesapla (C Servisine Gönder)', id='btn-hesapla', n_clicks=0, style={'padding': '10px'}),
        html.Div(id='sistem-mesaji', style={'marginTop': '15px', 'fontWeight': 'bold'})
    ], style={'padding': '20px', 'backgroundColor': '#f8f9fa', 'borderBottom': '2px solid #dee2e6'}),

    # Cytoscape Graf Alanı
    cyto.Cytoscape(
        id='graf-ekrani',
        layout={'name': 'preset'}, # 'preset' kullanımı, senin verdiğin x, y koordinatlarını zorunlu kılar (Proje isteri)
        style={'width': '100%', 'height': '600px', 'border': '1px solid #ccc'},
        stylesheet=stil_sayfasi,
        elements=baslangic_dugumleri
    )
], style={'fontFamily': 'Arial'})


# Dinamik Düğüm Ekleme İşlemi (Callback)
@app.callback(
    Output('graf-ekrani', 'elements'),
    Input('btn-dugum-ekle', 'n_clicks'),
    State('graf-ekrani', 'elements')
)
def yeni_dugum_ekle(tiklanma_sayisi, mevcut_elemanlar):
    if tiklanma_sayisi > 0:
        # Mevcut düğüm sayısını bul (kenarları sayma)
        dugum_sayisi = len([eleman for eleman in mevcut_elemanlar if 'source' not in eleman['data']])
        yeni_id = str(dugum_sayisi)
        
        # Ekranda rastgele/kaydırılmış bir pozisyonda yeni düğüm oluştur
        yeni_dugum = {
            'data': {'id': yeni_id, 'label': f'Bileşen {yeni_id}'},
            'position': {'x': 200 + (tiklanma_sayisi * 30), 'y': 200 + (tiklanma_sayisi * 20)} 
        }
        
        mevcut_elemanlar.append(yeni_dugum)
        
        # TODO: İlerleyen aşamada burada düğümler arası Öklid mesafesi hesaplanıp tüm kenarlar (edges) da eklenecek.
        
    return mevcut_elemanlar

if __name__ == '__main__':
    app.run_server(debug=True, port=8050)
