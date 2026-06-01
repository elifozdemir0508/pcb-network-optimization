# PCB Ağ Optimizasyonu

Bu proje, Veri Yapıları dersi kapsamında hazırlanmıştır. Projenin amacı, PCB üzerindeki bağlantı noktalarını bir graf yapısı olarak modellemek ve bağlantı maliyetini en aza indirecek uygun bağlantı ağını oluşturmaktır.

Projede graf veri yapısı, BFS, DFS, Kruskal algoritması, Union-Find veri yapısı ve temel görselleştirme yaklaşımları kullanılacaktır. PCB üzerindeki bağlantı noktaları düğüm, bu noktalar arasındaki bağlantılar ise kenar olarak temsil edilmektedir. Kenar ağırlıkları bağlantı maliyetini göstermektedir.

---

## Projenin Amacı

Bu projede temel hedef, PCB üzerindeki bağlantı noktaları arasında en düşük toplam maliyetli bağlantı ağını oluşturmaktır. Bunun için Minimum Spanning Tree yani Minimum Yayılan Ağaç yaklaşımı kullanılacaktır.

Proje kapsamında:

- PCB bağlantı noktaları düğüm olarak tanımlanacaktır.
- Bağlantılar kenar olarak tanımlanacaktır.
- Kenarlara ağırlık değeri atanacaktır.
- Graf komşuluk listesi ve komşuluk matrisi ile temsil edilecektir.
- BFS algoritması ile genişlik öncelikli arama yapılacaktır.
- DFS algoritması ile derinlik öncelikli arama yapılacaktır.
- Grafın bağlantılı olup olmadığı kontrol edilecektir.
- Kruskal algoritması ile Minimum Spanning Tree oluşturulacaktır.
- Union-Find veri yapısı ile döngü oluşumu kontrol edilecektir.
- Toplam MST maliyeti hesaplanacaktır.
- Sonuçlar kullanıcıya anlaşılır şekilde gösterilecektir.

---

## Kullanılacak Veri Yapıları ve Algoritmalar

Projede aşağıdaki veri yapıları ve algoritmalar kullanılacaktır:

- Graf veri yapısı
- Komşuluk listesi
- Komşuluk matrisi
- Kuyruk veri yapısı
- Yığın / özyinelemeli DFS mantığı
- BFS algoritması
- DFS algoritması
- Kruskal algoritması
- Union-Find veri yapısı
- Minimum Spanning Tree
- Alternatif olarak Prim algoritması
- Min-Heap yapısı
- JSON tabanlı test verileri
- Grafiksel görselleştirme

---

## Takım ve Görev Dağılımı

### Elif — Graf Yapısı ve Temel Veri Yapıları

Elif, projenin temel graf yapısından ve grafı temsil edecek veri yapılarından sorumludur.

Görevler:

- Graf veri yapısının oluşturulması
- Düğüm yapısının tanımlanması
- Kenar yapısının tanımlanması
- Komşuluk listesi yapısının hazırlanması
- Komşuluk matrisi yapısının hazırlanması
- Kenar ağırlıklarının saklanması
- Graf yapısının diğer algoritmalarla uyumlu hale getirilmesi

---

### Niyazi — BFS, DFS ve Bağlantı Kontrolü

Niyazi, graf üzerinde arama ve gezinme algoritmalarından sorumludur.

Görevler:

- Kuyruk veri yapısının kullanılması
- Yığın veya özyinelemeli DFS yapısının kullanılması
- BFS algoritmasının uygulanması
- DFS algoritmasının uygulanması
- Grafın bağlantılı olup olmadığının kontrol edilmesi
- BFS ve DFS sonuçlarının ekrana yazdırılması

---

### Cafer — MST Algoritmaları ve Karmaşıklık Analizi

Cafer, Minimum Spanning Tree algoritmalarından ve algoritma analizinden sorumludur.

Görevler:

- Kruskal algoritmasının uygulanması
- Union-Find veri yapısının hazırlanması
- Find işleminin uygulanması
- Union işleminin uygulanması
- Döngü oluşumunun engellenmesi
- Alternatif olarak Prim algoritmasının incelenmesi
- Min-Heap yapısının araştırılması
- Algoritmaların zaman karmaşıklığı analizinin yapılması

---

### Evin — Arayüz ve Grafiksel Görselleştirme

Evin, proje çıktılarının kullanıcıya anlaşılır şekilde gösterilmesinden ve grafiksel görselleştirmeden sorumludur.

Görevler:

- Düğüm ve kenar çizimlerinin hazırlanması
- Grafın görsel olarak gösterilmesi
- MST kenarlarının renklendirilmesi
- Algoritma adımlarının görselleştirilmesi
- Animasyon veya adım adım gösterim mantığının hazırlanması
- Kullanıcı etkileşiminin düzenlenmesi

---

### Azra — Entegrasyon, Test, Docker, README ve Rapor

Azra, projenin birleştirilmesi, test edilmesi ve dokümantasyonundan sorumludur.

Görevler:

- JSON test verilerinin hazırlanması ve doğrulanması
- Kodların birlikte çalışmasının kontrol edilmesi
- Docker kurulumunun hazırlanması
- Repository düzeninin kontrol edilmesi
- README dosyasının güncellenmesi
- Proje raporunun hazırlanması
- Proje videosu için gerekli içeriklerin hazırlanması

---

## Proje Klasör Yapısı

Projede kullanılacak temel klasör yapısı aşağıdaki gibidir:

```txt
pcb-network-optimization/
│
├── algorithms/
│   └── BFS, DFS, Kruskal, Prim ve diğer algoritmalar
│
├── core/
│   └── Graf veri yapısı ve temel fonksiyonlar
│
├── data/
│   └── Örnek giriş ve JSON test verileri
│
├── docker/
│   └── Docker kurulumu ve çalıştırma dosyaları
│
├── docs/
│   └── Rapor ve açıklama dosyaları
│
├── tests/
│   └── Test dosyaları
│
├── traversals/
│   └── BFS ve DFS geçiş işlemleri
│
├── ui/
│   └── Çıktı ve görselleştirme işlemleri
│
├── .gitignore
└── README.md
```

---

## GitHub Kullanımı

Proje geliştirme sürecinde GitHub kullanılmaktadır. Ekip üyeleri kendi görev alanlarına göre farklı branchler üzerinde çalışacaktır.

Kullanılan temel GitHub adımları:

- Repository oluşturuldu.
- Projenin konusu ve kapsamı belirlendi.
- Proje klasör yapısı hazırlandı.
- Takım üyelerinin sorumlulukları belirlendi.
- Görev branchleri oluşturuldu.
- Her ekip üyesinin kendi görev alanında çalışması planlandı.
- Issue bölümü yapılacak işler, hatalar ve geliştirme adımlarını takip etmek için kullanılacaktır.
- Değişiklikler main/master branchine eklenmeden önce pull request ile kontrol edilecektir.
- README dosyası güncellendi.
- Ara rapor için GitHub bağlantısı hazır hale getirildi.

---

## Ara Rapor Gelişmeleri

Ara rapor aşamasında aşağıdaki çalışmalar yapılmıştır:

- GitHub reposu oluşturuldu.
- Projenin konusu ve kapsamı belirlendi.
- Takım üyeleri arasında görev dağılımı yapıldı.
- Proje klasör yapısı oluşturuldu.
- Görev branchleri oluşturuldu.
- README dosyası düzenlendi.
- Her ekip üyesinin kendi görev alanında çalışma yapması planlandı.
- Pull request kullanımı ile ekip çalışmasının takip edilmesi hedeflendi.
- Issue bölümü ile yapılacak işler ve geliştirme adımlarının takip edilmesi planlandı.

---

## Derleme ve Çalıştırma Kılavuzu

Proje, yüksek performanslı graf hesaplamaları için **C11** standardında bir backend motoru ve görselleştirme için **Python** tabanlı bir frontend arayüzü barındırmaktadır. Sistem, dosya tabanlı asenkron bir mekanizma (IPC) ile haberleşmektedir.

### Ön Gereksinimler

Sistemi yerelde çalıştırmadan önce bilgisayarınızda aşağıdaki araçların kurulu olduğundan emin olun:
* **C Derleyici:** GCC (Linux/MinGW) veya Clang
* **Derleme Otomasyonu:** CMake (Minimum v3.10)
* **Python:** Python 3.8 veya üzeri

---

### 1. Backend Derleme (Build) İşlemleri

Projenin kök dizininde terminali açarak aşağıdaki adımları sırasıyla uygulayınız. `CMakeLists.txt` konfigürasyonumuz gereği, derlenen executable dosya otomatik olarak projenin **kök dizinine** çıkarılacaktır.

#### Linux ve macOS Ortamında:
```bash
# Derleme dosyalarını oluştur
cmake -B build

# Projeyi derle (Executable kök dizine üretilir)
cmake --build build
```

Windows Ortamında (PowerShell / CMD):
Windows üzerinde varsayılan Visual Studio derleyicisi yerine GCC (MinGW) kullanıyorsanız derleme komutuna generator parametresi eklenmelidir:

```bash
# MinGW ile derleme dosyalarını oluştur
cmake -G "MinGW Makefiles" -B build

# Projeyi derle (Executable.exe kök dizine üretilir)
cmake --build build
```
2. Sistemi Çalıştırma (Execution)
Sistemin kararlı çalışabilmesi için önce Backend Motorunun (dinleme modunda), ardından Frontend Arayüzünün başlatılması gerekmektedir.

#### Adım A: Backend Motorunu Başlatma
Projenin kök dizininde terminal üzerinden derlenen binary dosyayı tetikleyin:
- Linux / macOS:
```bash
./PCBNetworkOptimization
```
- Windows (PowerShell):
```bash
.\PCBNetworkOptimization.exe
```

#### Adım B: Frontend Arayüzü Başlatma
Yeni bir terminal penceresi açın, projenin kök dizininden itibaren ui/ klasörüne geçerek arayüzü tetikleyin:
```bash
# Arayüz klasörüne geçiş yap
cd ui

# Gerekli bağımlılıkları yükle (Eğer varsa)
pip install -r requirements.txt

# Web arayüzünü ayağa kaldır
python app.py
```

Not: Proje dosya yapısı tamamlandığında derleme komutu klasör yapısına göre güncellenecektir.

---

## Proje Durumu

Şu anda proje geliştirme aşamasındadır.

Tamamlanan işlemler:

- GitHub reposu oluşturuldu.
- README dosyası hazırlandı.
- Klasör yapısı oluşturuldu.
- Görev paylaşımı yapıldı.
- Branch yapısı oluşturuldu.
- İlk commitler yapıldı.
- Graf çekirdeğinin tamamlandı.
- BFS ve DFS algoritmalarının yazıldı.
- Kruskal algoritmasının yazıldı.
- Union-Find veri yapısının hazırlandı.

Devam eden işlemler:

- JSON test verilerinin hazırlanması
- Görselleştirme arayüzünün oluşturulması
- Kodların entegre edilmesi
- Docker ve test yapısının hazırlanması
- Rapor ve video içeriklerinin tamamlanması

---

## Sonuç

Bu proje ile graf veri yapısının gerçek bir problem üzerinde uygulanması hedeflenmektedir. PCB bağlantı noktaları graf olarak modellenmekte ve bağlantı maliyetini en aza indirmek için Minimum Spanning Tree algoritmaları kullanılmaktadır.

Proje, Veri Yapıları dersinde öğrenilen graf, BFS, DFS, Union-Find, Kruskal, Prim ve temel veri yapıları konularının birlikte kullanıldığı uygulamalı bir çalışmadır.
