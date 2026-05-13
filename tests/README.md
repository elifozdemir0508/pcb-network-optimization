# tests/ — Test ve Demo Dizini

Bu dizin, projenin tüm **birim testlerini**, **algoritma testlerini** ve **uçtan uca demo** ikililerini barındırır. Amaç: `core/` ve `algorithms/` altında geliştirilen yapı ve algoritmaların doğruluğunu, kaynak dizinlerine dokunmadan, tek bir merkezi yerden derleyip çalıştırabilmek.

Build sistemi olarak **CMake + CTest** kullanılır. Her test ayrı bir `add_executable` hedefidir; CTest hepsini tek komutla koşturur.

## Dizin yapısı

```
tests/
├── CMakeLists.txt        # Build sistemi — yeni test eklerken burayı düzenle
├── README.md             # Bu dosya
├── .gitignore            # build/ dizinini yok sayar
│
├── test_queue.c          # core/Queue.c için birim testi
├── test_stack.c          # core/Stack.c için birim testi
├── test_graph.c          # core/graph.c için birim testi
├── test_bfs.c            # core/Bfs.c için birim testi
├── test_dfs.c            # core/Dfs.c için birim testi
├── test_connectedness.c  # core/Connectedness.c için birim testi
├── kruskal_test.c        # algorithms/kruskal.c için algoritma testi
└── pcb_demo.c            # graph + connectedness + kruskal uçtan uca demo
```

> **Not:** Build çıktıları `tests/build/` altına gider, `.gitignore` tarafından kapsanır — sürüm kontrolüne girmez.

## Gereksinimler

- CMake **≥ 3.10**
- C11 destekleyen bir C derleyici (GCC veya Clang)
- `make` veya `ninja`

## Derleme ve çalıştırma

Aşağıdaki komutları **proje kök dizininden** çalıştır:

### 1. Build dizinini hazırla (bir kere)

```bash
cmake -S tests -B tests/build
```

### 2. Tüm testleri derle

```bash
cmake --build tests/build
```

İkililer `tests/build/bin/` altına düşer.

### 3. Tüm testleri koştur (CTest ile)

```bash
ctest --test-dir tests/build --output-on-failure
```

Örnek çıktı:
```
Test project .../tests/build
    Start 1: test_queue
1/8 Test #1: test_queue ...........  Passed
...
8/8 Test #8: pcb_demo .............  Passed

100% tests passed, 0 tests failed out of 8
```

### Tek bir testi koştur

```bash
./tests/build/bin/test_queue
# veya CTest filtresiyle:
ctest --test-dir tests/build -R test_queue --output-on-failure
```

### Sıfırdan başla

```bash
rm -rf tests/build
```

## Yeni bir test eklemek

Diyelim ki `core/Foo.c` için bir test yazıyorsun.

### Adım 1 — Test dosyasını yaz

`tests/test_foo.c` dosyasını oluştur:

```c
#include <stdio.h>
#include "Foo.h"   // core/ include yoluna otomatik eklenir

int main(void) {
    // ... testler ...
    if (/* bir koşul başarısız */) {
        printf("FAIL: aciklama\n");
        return 1;       // 0 dışı dönüş = test başarısız
    }
    printf("OK\n");
    return 0;           // 0 dönüş = test başarılı
}
```

> **Kural:** CTest, programın **dönüş kodunu** test sonucu olarak kabul eder. `0` → başarılı, başka her şey → başarısız. Bu yüzden testlerin yalnızca `printf` ile durum bildirmesi yetmez; hata bulduğunda `return 1` döndürmesi gerekir.

### Adım 2 — `CMakeLists.txt` içine bir satır ekle

[CMakeLists.txt](CMakeLists.txt) içinde `# Unit tests` bölümünün altına yeni testini ekle. Söz dizimi:

```cmake
pcb_add_test(<test_adi> <kaynak_dosyalar...>)
```

Örnekler:

```cmake
# Sadece bir core kaynağına bağımlı basit test:
pcb_add_test(test_foo test_foo.c ${CORE_DIR}/Foo.c)

# Birden fazla core kaynağına bağımlı test:
pcb_add_test(test_bar
    test_bar.c
    ${CORE_DIR}/Bar.c
    ${CORE_DIR}/graph.c
)

# core + algorithms birleşik:
pcb_add_test(test_baz
    test_baz.c
    ${CORE_DIR}/graph.c
    ${ALGO_DIR}/baz.c
)
```

`pcb_add_test` şunları otomatik yapar:
- `add_executable` ile ikiliyi oluşturur
- `${CORE_DIR}` ve `${ALGO_DIR}` yollarını include path'e ekler (`#include "Foo.h"` doğrudan çalışır)
- `add_test()` ile CTest'e kaydeder

`all_tests` özel hedefi varsayılan olarak her şeyi derlemek için kullanılır; yeni testini de oraya eklemek istersen [CMakeLists.txt](CMakeLists.txt) sonundaki `add_custom_target(all_tests DEPENDS ...)` listesine adını eklemen yeterli.

### Adım 3 — Derle ve koştur

```bash
cmake --build tests/build
ctest --test-dir tests/build -R test_foo --output-on-failure
```

> **İpucu:** Yeni `.c` dosyası eklediğinde CMake bunu otomatik fark eder; `cmake -S tests -B tests/build` komutunu tekrar çalıştırmana **gerek yoktur**, `cmake --build` aşaması yeniden generate eder. Ancak `CMakeLists.txt`'i değiştirip generator hata verirse build dizinini silip yeniden konfigüre et.

## Test yazım önerileri

- **Tek sorumluluk:** Her test dosyası bir modülü hedeflesin (`Queue`, `Stack`, vb.)
- **Bağımsızlık:** Testler birbirini çağırmasın; her biri kendi başına `main` ile çalışsın.
- **Dönüş kodu disiplini:** Hata bulunca mutlaka `return 1` — yoksa CTest yeşil görür.
- **Sessiz başarı, gürültülü başarısızlık:** Başarılı testler kısa `OK` çıktısı vermek yeterli; başarısız durumlar net hata mesajı yazsın.
- **Determinizm:** `rand()`, sistem saati, dosya yolu gibi değişkenlere bağımlı testler yazma; hep aynı girdiyle aynı sonucu üretsin.

## Sorun giderme

| Belirti | Olası neden | Çözüm |
|---|---|---|
| `undefined reference to <func>` | Bir bağımlılık `.c` dosyası `pcb_add_test`'e eklenmemiş | İlgili `${CORE_DIR}/X.c` veya `${ALGO_DIR}/X.c` dosyasını ekle |
| `<X.h>: No such file or directory` | Header farklı bir dizinde | Include zaten `core/` ve `algorithms/` için açık; yeni bir dizinden include gerekiyorsa `target_include_directories` yardımcı fonksiyonunda yol ekle |
| CTest "Failed" ama stdout temiz | Test programı `0` dışı dönüş yapıyor | Test `main`'inin sonunda `return 0;` olduğundan emin ol |
| Aynı sembol birden çok yerde tanımlı | İki `.c` dosyası aynı isimli fonksiyon/struct içeriyor (örn. `Queue.c` ile `Stack.c` her ikisi de `newNode` tanımlıyor) | Aynı binary'ye girmesinler — testleri ayrı tut veya isimleri farklılaştır |
| Build dizini bozuldu | Konfigürasyon yarıda kaldı | `rm -rf tests/build && cmake -S tests -B tests/build` |

## Mevcut testler — özet

| Test | Kapsam |
|---|---|
| `test_queue` | FIFO kuyruk yapısı (`enqueue`, `dequeue`, `show`) |
| `test_stack` | LIFO yığın yapısı (`push`, `pop`, `say`, `listele`) |
| `test_graph` | Graph init, kenar ekleme, komşuluk matrisi yazdırma |
| `test_bfs` | Genişlik öncelikli arama, statik 5 düğümlü graf |
| `test_dfs` | Derinlik öncelikli arama, `Graph` yapısı üzerinden |
| `test_connectedness` | Bağlı / kopuk graf ayırt etme — DFS tabanlı |
| `kruskal_test` | Kruskal MST: bağlı ve kopuk graf senaryoları (assert'li) |
| `pcb_demo` | Uçtan uca: graf → bağlantı kontrolü → MST → doğrulama |
