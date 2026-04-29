# PCB Ağ Optimizasyonu

Bu proje, Veri Yapıları dersi kapsamında hazırlanmıştır. Projenin amacı, PCB üzerindeki bağlantı noktalarını bir graf yapısı olarak modellemek ve bağlantı maliyetini en aza indirecek en uygun bağlantı ağını oluşturmaktır.

Projede graf veri yapısı, BFS, DFS, Kruskal algoritması ve Union-Find veri yapısı kullanılmaktadır. PCB üzerindeki bağlantı noktaları düğüm, bu noktalar arasındaki bağlantılar ise kenar olarak temsil edilmektedir. Kenar ağırlıkları bağlantı maliyetini göstermektedir.

---

## Projenin Amacı

Bu projede temel hedef, PCB üzerindeki bağlantı noktaları arasında en düşük toplam maliyetli bağlantı ağını oluşturmaktır. Bunun için Minimum Spanning Tree yani Minimum Yayılan Ağaç yaklaşımı kullanılmaktadır.

Proje kapsamında:

- Graf yapısı oluşturulur.
- Düğümler ve kenarlar tanımlanır.
- Kenar ağırlıkları saklanır.
- Komşuluk listesi oluşturulur.
- Komşuluk matrisi oluşturulur.
- BFS algoritması ile graf üzerinde genişlik öncelikli arama yapılır.
- DFS algoritması ile graf üzerinde derinlik öncelikli arama yapılır.
- Grafın bağlantılı olup olmadığı kontrol edilir.
- Kruskal algoritması ile Minimum Spanning Tree bulunur.
- Union-Find veri yapısı ile döngü oluşumu kontrol edilir.
- Toplam MST maliyeti hesaplanır.
- Sonuçlar kullanıcıya anlaşılır şekilde gösterilir.

---

## Kullanılan Veri Yapıları ve Algoritmalar

Projede aşağıdaki veri yapıları ve algoritmalar kullanılmaktadır:

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

---

## Proje Kapsamı

Bu proje, PCB bağlantı ağının graf olarak modellenmesini ve bu graf üzerinde temel veri yapıları algoritmalarının uygulanmasını kapsamaktadır.

Proje kapsamında yapılacak temel işlemler şunlardır:

- PCB bağlantı noktalarını düğüm olarak tanımlama
- Bağlantıları kenar olarak tanımlama
- Kenarlara ağırlık değeri verme
- Grafı komşuluk listesi ile gösterme
- Grafı komşuluk matrisi ile gösterme
- BFS geçişini uygulama
- DFS geçişini uygulama
- Grafın bağlantılı olup olmadığını kontrol etme
- Kruskal algoritması ile MST oluşturma
- Toplam MST maliyetini hesaplama
- Sonuçları kullanıcıya anlaşılır şekilde gösterme

---

## Takım Sorumlulukları

Proje ekip üyeleri tarafından farklı branchler üzerinden geliştirilmektedir. Her ekip üyesi kendi görev alanındaki kodları kendi branchinde hazırlamakta ve daha sonra ana geliştirme dalına eklemektedir.

---

### 1. Graf Çekirdeği

Bu bölüm, projenin temel graf yapısından sorumludur.

Görevler:

- Graf veri yapısını oluşturmak
- Düğüm yapısını tanımlamak
- Kenar yapısını tanımlamak
- Düğüm ekleme fonksiyonunu yazmak
- Kenar ekleme fonksiyonunu yazmak
- Kenar ağırlıklarını saklamak
- Komşuluk listesi yapısını oluşturmak
- Komşuluk matrisi yapısını oluşturmak

---

### 2. BFS ve DFS Algoritmaları

Bu bölüm, graf üzerinde arama ve gezinme algoritmalarından sorumludur.

Görevler:

- BFS algoritmasını uygulamak
- BFS için kuyruk mantığını kullanmak
- DFS algoritmasını uygulamak
- DFS için yığın veya özyinelemeli yapı kullanmak
- Grafın bağlantılı olup olmadığını kontrol etmek
- BFS ve DFS sonuçlarını ekrana yazdırmak

---

### 3. Kruskal ve Union-Find

Bu bölüm, Minimum Spanning Tree hesabından sorumludur.

Görevler:

- Kenarları ağırlıklarına göre sıralamak
- Union-Find veri yapısını oluşturmak
- Find işlemini uygulamak
- Union işlemini uygulamak
- Döngü oluşumunu engellemek
- Kruskal algoritmasını uygulamak
- MST kenarlarını belirlemek
- Toplam MST maliyetini hesaplamak

---

### 4. Kullanıcı Arayüzü ve Çıktı Gösterimi

Bu bölüm, program çıktılarının kullanıcıya anlaşılır şekilde gösterilmesinden sorumludur.

Görevler:

- Komşuluk listesini ekrana yazdırmak
- Komşuluk matrisini ekrana yazdırmak
- BFS sonucunu göstermek
- DFS sonucunu göstermek
- MST kenarlarını göstermek
- Toplam MST maliyetini göstermek
- Program çıktısını düzenli ve okunabilir hale getirmek

---

### 5. Belge ve Entegrasyon

Bu bölüm, proje dokümantasyonu ve parçaların birleştirilmesinden sorumludur.

Görevler:

- README.md dosyasını güncellemek
- Proje klasör yapısını düzenlemek
- Örnek test verilerini hazırlamak
- Kodların birlikte çalışmasını kontrol etmek
- Entegrasyon notlarını hazırlamak
- Ara rapor için gerekli GitHub bağlantısını hazırlamak

---

## Klasör Yapısı

Projede kullanılan temel klasörler aşağıdaki gibidir:

```txt
pcb-network-optimization/
│
├── algoritmalar/
│   └── Algoritma kodları
│
├── cekirdek/
│   └── Graf veri yapısı ve temel fonksiyonlar
│
├── veri/
│   └── Örnek giriş verileri
│
├── belgeler/
│   └── Rapor ve açıklama dosyaları
│
├── testler/
│   └── Test dosyaları
│
├── gecisler/
│   └── BFS ve DFS geçiş işlemleri
│
├── kullanici-arayuzu/
│   └── Çıktı ve kullanıcıya gösterim işlemleri
│
├── .gitignore
└── README.md
```

---

## Derleme ve Çalıştırma

Proje C dili ile geliştirilmektedir. Dosyalar tamamlandığında aşağıdaki komut ile derlenebilir:

```bash
gcc main.c graph.c bfs_dfs.c kruskal.c -o pcb_network
```

Linux veya macOS ortamında çalıştırmak için:

```bash
./pcb_network
```

Windows ortamında çalıştırmak için:

```bash
pcb_network.exe
```

---

## GitHub Kullanımı

Proje geliştirme sürecinde GitHub kullanılmaktadır. Ekip üyeleri kendi branchleri üzerinde çalışmaktadır.

Kullanılan temel GitHub adımları:

- Repository oluşturuldu.
- Proje klasör yapısı hazırlandı.
- Görev alanlarına göre branchler açıldı.
- Her ekip üyesi kendi görev alanında geliştirme yaptı.
- Yapılan değişiklikler commit edildi.
- Branchlerden ana geliştirme dalına pull request açıldı.
- README dosyası güncellendi.
- Ara rapor için GitHub bağlantısı hazır hale getirildi.

---

## Ara Rapor Durumu

Ara rapor aşamasında proje iskeleti oluşturulmuştur. GitHub reposu hazırlanmış, klasör yapısı kurulmuş, görev paylaşımı yapılmış ve ekip üyeleri kendi branchleri üzerinde çalışmaya başlamıştır.

Bu aşamada amaç, projenin temel yapısını oluşturmak ve ilerleyen süreçte algoritmaların tamamlanarak entegre edilmesini sağlamaktır.

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

Devam eden işlemler:

- Graf çekirdeğinin tamamlanması
- BFS ve DFS algoritmalarının tamamlanması
- Kruskal algoritmasının tamamlanması
- Union-Find veri yapısının tamamlanması
- Test verilerinin hazırlanması
- Kodların birleştirilmesi
- Son çıktıların düzenlenmesi

---

## Sonuç

Bu proje ile graf veri yapısının gerçek bir problem üzerinde uygulanması hedeflenmektedir. PCB bağlantı noktaları graf olarak modellenmekte ve bağlantı maliyetini en aza indirmek için Kruskal algoritması ile Minimum Spanning Tree hesaplanmaktadır.

Proje, Veri Yapıları dersinde öğrenilen graf, BFS, DFS, Union-Find ve MST konularının birlikte kullanıldığı uygulamalı bir çalışmadır.

## How to Compile

```bash
gcc main.c graph.c bfs_dfs.c kruskal.c -o pcb_network
