# PCB Ağ Optimizasyonu

Bu proje, Veri Yapıları dersi kapsamında geliştirilmiştir. Projenin amacı, PCB üzerindeki bağlantı noktalarını graf veri yapısı ile modellemek ve bu bağlantı noktalarını minimum toplam maliyetle birbirine bağlayan uygun ağı oluşturmaktır.

PCB üzerindeki bağlantı noktaları graf düğümleri, bağlantı ihtimalleri graf kenarları, bağlantı maliyetleri ise kenar ağırlıkları olarak temsil edilmiştir. Minimum maliyetli bağlantı ağını elde etmek için Minimum Spanning Tree yaklaşımı kullanılmıştır. Bu kapsamda Kruskal algoritması ve döngü kontrolü için Union-Find veri yapısı tercih edilmiştir.

---

## Projenin Amacı

Bu projede temel amaç, PCB üzerindeki bağlantı noktaları arasında en düşük toplam maliyetli bağlantı ağını oluşturmaktır.

Proje kapsamında:

* PCB bağlantı noktaları graf düğümü olarak modellenmiştir.
* Bağlantılar ağırlıklı kenar olarak tanımlanmıştır.
* Graf yapısı komşuluk matrisi ve kenar listesi ile temsil edilmiştir.
* BFS algoritması ile genişlik öncelikli graf dolaşımı yapılmıştır.
* DFS algoritması ile derinlik öncelikli graf dolaşımı yapılmıştır.
* Grafın bağlı olup olmadığı kontrol edilmiştir.
* Kruskal algoritması ile Minimum Spanning Tree oluşturulmuştur.
* Union-Find veri yapısı ile döngü oluşumu engellenmiştir.
* MST toplam maliyeti hesaplanmıştır.
* Sonuçlar kullanıcı arayüzü ve çıktı dosyaları üzerinden gösterilmiştir.

---

## Kullanılan Veri Yapıları ve Algoritmalar

Projede kullanılan temel veri yapıları ve algoritmalar şunlardır:

* Graph
* Edge
* Adjacency Matrix
* Edge List
* Queue
* Stack
* BFS
* DFS
* Connectedness Control
* Union-Find
* Kruskal Algorithm
* Minimum Spanning Tree

Bu projede MST hesaplaması için ana algoritma olarak Kruskal algoritması tercih edilmiştir. Kruskal algoritması, kenarları ağırlıklarına göre küçükten büyüğe sıralar ve Union-Find veri yapısı yardımıyla döngü oluşturmayan kenarları seçerek minimum maliyetli bağlantı ağını oluşturur.

---

## Sistem Mimarisi

Proje modüler bir yapı ile geliştirilmiştir. Temel veri yapıları, algoritmalar, veri giriş-çıkış işlemleri, test dosyaları, arayüz ve Docker yapılandırmaları ayrı klasörlerde tutulmuştur.

Genel sistem akışı şu şekildedir:

1. Kullanıcı arayüz veya örnek veri dosyası üzerinden graf verisini oluşturur.
2. Graf düğümleri ve kenarları sisteme eklenir.
3. Grafın bağlılık durumu BFS/DFS tabanlı kontrollerle analiz edilir.
4. Kruskal algoritması çalıştırılır.
5. Union-Find veri yapısı ile döngü oluşturacak kenarlar elenir.
6. MST kenarları ve toplam maliyet hesaplanır.
7. Sonuçlar arayüzde ve çıktı dosyalarında gösterilir.

Projede frontend ve backend bileşenleri birbirinden bağımsız çalışacak şekilde tasarlanmıştır. Kullanıcı arayüzü Python Dash ile ayrı bir bileşen olarak çalışırken, graf verilerini işleyen ve MST/Kruskal hesaplamasını yapan C backend ayrı bir hesaplama motoru olarak çalışmaktadır.

Frontend ve backend doğrudan aynı bellek alanını paylaşmak yerine JSON dosyaları ve flag mekanizması üzerinden haberleşmektedir. Bu yapı sayesinde sistem daha modüler, daha kontrollü ve bağımsız çalışabilir hale getirilmiştir.

> Not: Projede ayrı bir yapay zekâ servisi bulunmamaktadır. Değerlendirme maddesindeki bağımsız/asenkron çalışma yaklaşımı, bu projede C tabanlı algoritma motoru ve Python tabanlı frontend bileşenlerinin ayrılmasıyla sağlanmıştır.

---

## Proje Klasör Yapısı

```text
pcb-network-optimization/
│
├── algorithms/
│   └── Kruskal ve MST algoritma dosyaları
│
├── core/
│   └── Graph, Queue, Stack, BFS, DFS, Connectedness ve Union-Find modülleri
│
├── data/
│   └── Örnek giriş ve çıkış JSON dosyaları
│
├── docker/
│   └── Docker yapılandırma dosyaları
│
├── docs/
│   └── Proje raporu, UML diyagramları ve dokümantasyon dosyaları
│
├── io/
│   └── JSON veri okuma/yazma ve veri dönüştürme işlemleri
│
├── tests/
│   └── Test dosyaları ve örnek çalışma senaryoları
│
├── traversals/
│   └── Graf dolaşım işlemlerinin dokümantasyonu
│
├── ui/
│   └── Görselleştirme ve kullanıcı arayüzü dosyaları
│
├── .gitignore
├── CMakeLists.txt
├── docker-compose.yml
└── README.md
```

---

## Takım ve Görev Dağılımı

| Takım Üyesi      | Görev Alanı                                                            |
| ---------------- | ---------------------------------------------------------------------- |
| Elif Ozdemir     | Graph yapısı, temel veri yapıları ve proje entegrasyonu                |
| Niyazi Han       | BFS, DFS, Stack/Queue kullanımı ve connectedness kontrolü              |
| Cafer Tura Cetin | Kruskal algoritması, Union-Find ve algoritma analizi                   |
| Evin Yilmaz      | Arayüz, görselleştirme ve dinamik graf güncellemeleri                  |
| Azra Tashan      | JSON veri entegrasyonu, test verileri, Docker ve dokümantasyon desteği |

---

## GitHub Branch Yapısı ve Çalışma Akışı

Projede GitHub üzerinde branch ve Pull Request tabanlı bir geliştirme süreci kullanılmıştır. `main` branch doğrudan geliştirme için kullanılmamış, kararlı ve teslim edilebilir proje sürümünü temsil edecek şekilde korunmuştur.

Kullanılan branch yapısı:

* `main`: Teslim edilecek kararlı proje sürümünü içerir.
* `dev`: Ekip üyelerinden gelen geliştirmelerin birleştirildiği entegrasyon branchidir.
* `feature/...`: Belirli bir modül veya özellik için açılan geliştirme branchleridir.
* `fix/...`: Hata düzeltmeleri için açılan branchlerdir.
* `docs/...`: Dokümantasyon ve README güncellemeleri için kullanılan branchlerdir.

Genel iş akışı:

1. Her ekip üyesi kendi görev alanı için ayrı branch oluşturmuştur.
2. Geliştirmeler ilgili branch üzerinde commit edilmiştir.
3. Değişiklikler Pull Request açılarak kontrol edilmiştir.
4. Uygun görülen değişiklikler `dev` veya proje akışına göre `main` branchine merge edilmiştir.
5. `main` branch projenin çalışan ve teslim edilebilir son halini temsil etmektedir.

Bu yapı sayesinde takım üyelerinin katkıları commit ve Pull Request geçmişi üzerinden takip edilebilir hale getirilmiştir.

---

## Kullanılan Temel Modüller

### Graph

Graph modülü, PCB üzerindeki bağlantı noktalarını ve bu noktalar arasındaki bağlantıları temsil eder.

Graph yapısında:

* `nodeCount`: Düğüm sayısını tutar.
* `edgeCount`: Kenar sayısını tutar.
* `adjacencyMatrix`: Bağlantıların matris temsilini tutar.
* `edges`: Kruskal algoritması için kenar listesini tutar.

Komşuluk matrisi BFS, DFS ve bağlılık kontrolünde kullanılır. Kenar listesi ise Kruskal algoritmasında kenarların ağırlıklarına göre sıralanması için kullanılır.

### Queue

Queue veri yapısı BFS algoritmasında kullanılmıştır. FIFO prensibiyle çalışır. İlk eklenen düğüm ilk çıkarılır. Bu sayede graf genişlik öncelikli olarak dolaşılır.

### Stack

Stack veri yapısı DFS algoritmasında kullanılmıştır. LIFO prensibiyle çalışır. Son eklenen düğüm ilk çıkarılır. Bu sayede graf derinlik öncelikli olarak dolaşılır.

### BFS

BFS algoritması, grafı genişlik öncelikli olarak dolaşır. Başlangıç düğümü kuyruğa eklenir. Kuyruk boşalana kadar düğümler sırayla çıkarılır ve ziyaret edilmemiş komşular kuyruğa eklenir.

### DFS

DFS algoritması, grafı derinlik öncelikli olarak dolaşır. Bu projede DFS, Stack veri yapısı kullanılarak gerçekleştirilmiştir. DFS sonucunda ulaşılan düğüm sayısı bağlılık kontrolünde kullanılır.

### Connectedness Control

Connectedness kontrolü, grafın bağlı olup olmadığını anlamak için kullanılır. DFS sonucunda ulaşılan düğüm sayısı toplam düğüm sayısına eşitse graf bağlı kabul edilir.

### Union-Find

Union-Find veri yapısı, Kruskal algoritmasında döngü oluşumunu engellemek için kullanılır. Her düğüm başlangıçta kendi kümesindedir. Kenarlar incelenirken iki düğüm aynı kümede değilse bu kenar MST’ye eklenir ve kümeler birleştirilir.

### Kruskal Algorithm

Kruskal algoritması, Minimum Spanning Tree oluşturmak için kullanılmıştır. Algoritma, kenarları ağırlıklarına göre küçükten büyüğe sıralar ve Union-Find veri yapısı yardımıyla döngü oluşturmayan kenarları seçer.

---

## Zaman Karmaşıklığı Analizi

| Modül / İşlem         | Zaman Karmaşıklığı | Açıklama                                   |
| --------------------- | -----------------: | ------------------------------------------ |
| Graph başlatma        |              O(V²) | Komşuluk matrisi sıfırlanır                |
| Kenar ekleme          |               O(1) | Matrix ve edge list güncellenir            |
| Queue enqueue         |               O(1) | Kuyruğun sonuna ekleme yapılır             |
| Queue dequeue         |               O(1) | Kuyruğun başından eleman çıkarılır         |
| Stack push            |               O(1) | Stack başına eleman eklenir                |
| Stack pop             |               O(1) | Stack başından eleman çıkarılır            |
| BFS                   |              O(V²) | Komşuluk matrisi üzerinden dolaşım yapılır |
| DFS                   |              O(V²) | Komşuluk matrisi üzerinden dolaşım yapılır |
| Connectedness Control |              O(V²) | DFS tabanlı bağlılık kontrolü yapılır      |
| Union-Find find       |            O(α(n)) | Path compression kullanılır                |
| Union-Find union      |            O(α(n)) | Union by rank kullanılır                   |
| Kruskal               |         O(E log E) | Kenar sıralama işlemi baskındır            |

Burada `V` düğüm sayısını, `E` kenar sayısını ifade eder. `α(n)` inverse Ackermann fonksiyonudur ve pratikte neredeyse sabit zaman gibi kabul edilir.

---

## Alan Karmaşıklığı Analizi

Projede graf yapısı komşuluk matrisi ile temsil edildiği için Graph modülünün alan karmaşıklığı `O(V²)` olarak değerlendirilir. Kruskal algoritması için ayrıca kenar listesi tutulduğu için kenar bilgileri `O(E)` alan kullanır.

Genel olarak:

| Bileşen          | Alan Karmaşıklığı | Açıklama                                          |
| ---------------- | ----------------: | ------------------------------------------------- |
| Adjacency Matrix |             O(V²) | Düğümler arası bağlantıları matris üzerinde tutar |
| Edge List        |              O(E) | Kruskal algoritması için kenarları tutar          |
| Queue            |              O(V) | BFS sırasında ziyaret edilecek düğümleri tutar    |
| Stack            |              O(V) | DFS sırasında ziyaret edilecek düğümleri tutar    |
| Union-Find       |              O(V) | Parent ve rank dizilerini tutar                   |

---

## Derleme ve Çalıştırma

Proje, C11 standardında yazılmış backend modülleri ve Python tabanlı görselleştirme arayüzü içermektedir. Backend tarafında CMake kullanılmıştır.

### Ön Gereksinimler

Sistemi çalıştırmak için aşağıdaki araçların kurulu olması gerekir:

* GCC, MinGW veya Clang
* CMake 3.10 veya üzeri
* Python 3.8 veya üzeri
* pip
* Docker ve Docker Compose

---

## Backend Derleme

Projenin kök dizininde terminal açılarak aşağıdaki komutlar çalıştırılır.

### Linux / macOS

```bash
cmake -B build
cmake --build build
./PCBNetworkOptimization
```

### Windows PowerShell / CMD

MinGW kullanılıyorsa:

```bash
cmake -G "MinGW Makefiles" -B build
cmake --build build
.\PCBNetworkOptimization.exe
```

---

## Frontend Arayüzünü Çalıştırma

Yeni bir terminal açılarak `ui/` klasörüne geçilir.

```bash
cd ui
pip install -r requirements.txt
python app.py
```

Backend motoru ve frontend arayüzü birlikte çalıştırıldığında kullanıcı graf üzerinde düğüm/kenar işlemlerini görüntüleyebilir ve MST sonucunu takip edebilir.

---

## Docker ile Çalıştırma

Docker yapılandırması, frontend ve backend bileşenlerinin bağımlılık sorunu yaşamadan tek komutla çalıştırılmasını sağlamak için hazırlanmıştır.

Projenin kök dizininde aşağıdaki komut çalıştırılır:

```bash
docker-compose up --build
```

Bu komut ile:

* Frontend servisi başlatılır.
* Backend hesaplama motoru başlatılır.
* Frontend ve backend arasında kullanılan ortak veri dosyaları erişilebilir hale gelir.
* Kullanıcı arayüzü üzerinden MST hesaplama süreci takip edilebilir.

Docker kullanımı sayesinde proje farklı bilgisayarlarda ek kurulum adımı gerektirmeden çalıştırılabilir.

> Not: Projede ayrı bir AI servisi bulunmamaktadır. Docker yapısında temel olarak frontend ve backend servisleri yer almaktadır.

---

## JSON Tabanlı Veri Akışı

Projede frontend ve backend arasındaki veri iletişimi JSON dosyaları ve flag sistemi üzerinden yapılmaktadır.

Genel veri akışı:

1. Kullanıcı arayüzde graf bilgisini oluşturur.
2. Frontend, graf verisini `input_graph.json` dosyasına yazar.
3. Frontend, backend’e hesaplama isteği göndermek için `calculate.flag` dosyasını oluşturur.
4. Backend bu flag dosyasını izler.
5. Flag dosyası oluştuğunda backend graf verisini okur.
6. Kruskal algoritması çalıştırılır.
7. MST sonucu `output_mst.json` dosyasına yazılır.
8. Frontend sonucu okuyarak kullanıcıya gösterir.

Bu yapı sayesinde frontend ve backend birbirinden ayrılmış, daha kontrollü ve modüler bir çalışma düzeni oluşturulmuştur.

---

## Örnek Veri Yapısı

Örnek giriş verisi:

```json
{
  "request_meta": {
    "algorithm": "kruskal",
    "action": "calculate_mst",
    "node_count": 3,
    "edge_count": 3
  },
  "nodes": [
    {"id": 0, "x": 100, "y": 200},
    {"id": 1, "x": 350, "y": 400},
    {"id": 2, "x": 500, "y": 150}
  ],
  "edges": [
    {"source": 0, "target": 1, "weight": 320},
    {"source": 0, "target": 2, "weight": 403},
    {"source": 1, "target": 2, "weight": 180}
  ]
}
```

Örnek çıkış verisi:

```json
{
  "response_meta": {
    "status": "success",
    "algorithm_used": "kruskal",
    "total_cost": 1123,
    "is_connected": true
  },
  "mst_edges": [
    {"source": 1, "target": 3, "weight": 180},
    {"source": 1, "target": 4, "weight": 223},
    {"source": 0, "target": 3, "weight": 316},
    {"source": 0, "target": 2, "weight": 403}
  ]
}
```

---

## Test ve Doğrulama

Projede test ve doğrulama işlemleri aşağıdaki adımlarla yapılmıştır:

* Graph veri yapısının başlangıç durumu kontrol edilmiştir.
* Kenar ekleme işlemleri test edilmiştir.
* BFS ve DFS dolaşım sonuçları kontrol edilmiştir.
* Connectedness fonksiyonu ile grafın bağlı olup olmadığı test edilmiştir.
* Kruskal algoritmasının ürettiği MST kenarları incelenmiştir.
* Union-Find ile döngü oluşumunun engellendiği doğrulanmıştır.
* JSON giriş/çıkış yapısı örnek verilerle test edilmiştir.
* UI tarafında graf ve MST görselleştirme çıktıları kontrol edilmiştir.
* Docker ile sistemin tek komutla çalıştırılması kontrol edilmiştir.

---

## Proje Raporu ve UML Diyagramları

Proje raporu `docs/` klasörü altında yer almaktadır. Raporda aşağıdaki başlıklar bulunmaktadır:

* Proje amacı
* Sistem mimarisi
* Kullanılan veri yapıları
* Algoritma açıklamaları
* UML diyagramları
* Big-O analizleri
* Alan karmaşıklığı analizleri
* AI prompt dökümleri
* Test ve doğrulama sonuçları
* Sonuç ve değerlendirme

Hazırlanan UML diyagramları:

* Use Case Diagram
* Class Diagram
* Activity Diagram
* Sequence Diagram
* Component Diagram

Teslim raporu: [Proje Teslim Raporu](https://drive.google.com/file/d/11TxMT-Hmre03BCa9V1XXBzqKBMeqlJlY/view?usp=sharing)
---

## Sunum ve Demo

Proje sunumu kapsamında sistemin genel amacı, kullanılan veri yapıları, algoritma akışı ve arayüz üzerinden MST hesaplama süreci gösterilecektir.

Sunumda özellikle aşağıdaki noktalar ele alınacaktır:

* PCB bağlantı noktalarının graf düğümü olarak modellenmesi
* Kenarların ağırlıklı bağlantı olarak temsil edilmesi
* Graph, Queue, Stack ve Union-Find veri yapılarının projedeki kullanımı
* BFS/DFS ile graf dolaşımı ve bağlılık kontrolü
* Kruskal algoritması ile Minimum Spanning Tree oluşturulması
* Frontend ve backend arasındaki JSON/flag tabanlı veri akışı
* Docker ile sistemin tek komutla çalıştırılması

Demo videosunda kullanıcı arayüzü üzerinden graf verisinin görüntülenmesi, MST hesaplama işleminin başlatılması ve elde edilen minimum maliyetli bağlantı ağının gösterilmesi hedeflenmektedir.

Demo video linki:

```text
https://drive.google.com/file/d/1blBZGRAs0hHGHob9XFrBDY2DLQd4JKaC/view?usp=sharing
```

---

## Proje Durumu

Projenin temel veri yapıları, algoritma modülleri, GitHub iş akışı, Docker yapısı ve dokümantasyon yapısı tamamlanmıştır.

Tamamlanan çalışmalar:

* GitHub reposu oluşturuldu.
* Branch ve Pull Request tabanlı geliştirme süreci kullanıldı.
* Graph veri yapısı oluşturuldu.
* Queue ve Stack veri yapıları implemente edildi.
* BFS ve DFS algoritmaları yazıldı.
* Connectedness kontrolü eklendi.
* Union-Find veri yapısı implemente edildi.
* Kruskal MST algoritması yazıldı.
* JSON tabanlı örnek veri yapısı hazırlandı.
* UI tarafında graf ve MST görselleştirme çalışmaları yapıldı.
* Docker yapılandırması hazırlandı.
* UML diyagramları hazırlandı.
* Proje raporu oluşturuldu.
* README dosyası teslim formatına uygun şekilde düzenlendi.

Teslim öncesi son kontrol adımları:

* Demo videosu linkinin README’ye eklenmesi
* Proje raporunun final PDF halinin `docs/` klasörüne eklenmesi
* Docker komutunun son kez test edilmesi

---

## Sonuç

Bu proje ile graf veri yapısının gerçek hayat problemlerinden biri olan PCB bağlantı ağı optimizasyonu üzerinde nasıl kullanılabileceği gösterilmiştir. PCB bağlantı noktaları graf düğümleri olarak, bağlantılar ise ağırlıklı kenarlar olarak modellenmiştir.

Kruskal algoritması ve Union-Find veri yapısı kullanılarak döngü içermeyen, tüm düğümleri kapsayan ve toplam bağlantı maliyeti minimum olan MST yapısı elde edilmiştir. BFS ve DFS algoritmaları ise graf dolaşımı ve bağlantı kontrolü amacıyla kullanılmıştır.

Proje, Veri Yapıları dersinde öğrenilen graph, queue, stack, BFS, DFS, Union-Find ve MST konularının birlikte kullanıldığı uygulamalı bir çalışmadır.
