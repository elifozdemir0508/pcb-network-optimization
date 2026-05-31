# Traversals

Bu klasör, PCB Bağlantı Ağı Optimizasyonu projesinde kullanılan graf dolaşım işlemlerini açıklamak amacıyla oluşturulmuştur.

Mevcut proje yapısında BFS, DFS ve bağlılık kontrolü işlemleri `core/` klasörü altında implemente edilmiştir:

- `core/Bfs.c` ve `core/Bfs.h`
- `core/Dfs.c` ve `core/Dfs.h`
- `core/Connectedness.c` ve `core/Connectedness.h`

## Amaç

Traversal algoritmaları, graf üzerinde düğümlerin erişilebilirliğini ve bağlantı durumunu analiz etmek için kullanılır.

Bu projede traversal işlemleri şu amaçlarla kullanılmaktadır:

- PCB üzerindeki bileşenlerin birbirine bağlı olup olmadığını kontrol etmek
- Graf üzerinde BFS ve DFS dolaşımı gerçekleştirmek
- Minimum Spanning Tree oluşturulduktan sonra tüm düğümlerin erişilebilir olduğunu doğrulamak
- Kullanıcı arayüzünden yapılan dinamik değişikliklerden sonra bağlantı analizini yeniden yapmak

## Kullanılan Algoritmalar

### BFS

BFS, grafı genişlik öncelikli olarak dolaşır. Bu işlem sırasında Queue veri yapısı kullanılır. Başlangıç düğümünden başlanır, önce komşu düğümler ziyaret edilir ve daha sonra onların komşularına geçilir.

### DFS

DFS, grafı derinlik öncelikli olarak dolaşır. Bu işlem sırasında Stack veri yapısı kullanılır. Başlangıç düğümünden başlanır ve mümkün olduğunca derine gidilerek graf gezilir.

### Connectedness Control

Connectedness kontrolü, grafın bağlı olup olmadığını anlamak için kullanılır. DFS sonucunda ulaşılan düğüm sayısı, grafın toplam düğüm sayısına eşitse graf bağlı kabul edilir.

## Projedeki Yeri

Traversal işlemleri, projenin temel graf analiz adımlarından biridir. Kruskal algoritması ile Minimum Spanning Tree oluşturulmadan önce veya oluşturulduktan sonra, grafın bağlantı durumu bu dolaşım algoritmaları yardımıyla kontrol edilebilir.
