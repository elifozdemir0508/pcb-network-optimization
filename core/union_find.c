#include "union_find.h"

#include <stdlib.h>

/**
 * @brief union find veri yapısını bellekte oluşturur ve ilk atamaları yapar.
 * 
 * @param n: union find veri yapısının boyutunu belirler
 * 
 * @retval NULL: geçersiz durumlarda (bellekten yer ayrılamaması, parametrelerin hatalı olması vb.) hatalı kullanımların önüne geçilmesi için döndürülür.
 * @retval uf: bellekte oluşturulmuş ve ilk değerleri hazırlanmış UnionFind tipinde pointer adresi döndürülür.
 * 
 * @author: Cafer Tura Çetin
 * 
 * @note: O(n) karmaşıklığına sahiptir statik diziler oluşturulduktan sonra ilk atamalar için eleman sayısı (n) kadar çalışan döngü kullanılmıştır 
 */
UnionFind *union_find_create(uint32_t n) {
    if (n == 0) return NULL;
    if (n > SIZE_MAX / sizeof(uint32_t)) {
        return NULL;
    }

	UnionFind *uf = (UnionFind *)malloc(sizeof(UnionFind));
	if (!uf) {
		return NULL;
	}

	uf->n = n;
	uf->parent = (uint32_t *)malloc(sizeof(uint32_t) * n);
	uf->rank = (uint32_t *)malloc(sizeof(uint32_t) * n);

	if (!uf->parent || !uf->rank) {
		free(uf->parent);
		free(uf->rank);
		free(uf);
		return NULL;
	}

	for (uint32_t i = 0; i < n; ++i) {
		uf->parent[i] = i;
		uf->rank[i] = 0;
	}

	return uf;
}

/**
 * @brief Bellekte ayrılmış union find yapılarını serbest bırakır.
 * 
 * @param uf: Serbest bırakılacak UnionFind yapısının işaretçisi
 * 
 * @author: Cafer Tura Çetin
 * 
 * @note: O(1) karmaşıklığına sahiptir. Bellek sızıntılarını önlemek için kullanılmalıdır.
 */
void union_find_destroy(UnionFind *uf) {
/**
 * @brief Verilen düğümün ait olduğu kümenin kökünü (root) bulur. Yol sıkıştırma (path compression) işlemi yapar.
 * 
 * @param uf: Üzerinde işlem yapılacak UnionFind yapısı
 * @param x: Kökü bulunacak düğüm
 * 
 * @retval UINT32_MAX: Geçersiz parametre durumunda döndürülür
 * @retval uf->parent[x]: Düğümün bulunduğu kümenin kök düğümü döndürülür
 * 
 * @author: Cafer Tura Çetin
 * 
 * @note: Yol sıkıştırma kullanıldığından ortalama zaman karmaşıklığı O(α(n))'dir.
 */
	if (!uf) {
		return;
	}

	free(uf->parent);
	free(uf->rank);
	free(uf);
}
/**
 * @brief Verilen iki düğümü aynı kümeye birleştirir. Sıraya göre birleştirme (union by rank) kullanır.
 * 
 * @param uf: Üzerinde işlem yapılacak UnionFind yapısı
 * @param a: Birleştirilecek birinci düğüm
 * @param b: Birleştirilecek ikinci düğüm
 * 
 * @retval false: Düğümler zaten aynı kümedeyse veya geçersiz parametre varsa döndürülür
 * @retval true: Birleştirme işlemi başarılı olduysa döndürülür
 * 
 * @author: Cafer Tura Çetin
 * 
 * @note: Ortalama O(α(n)) zaman karmaşıklığı ile çalışır. Köklerin rank değerine göre ağaç derinliği dengede tutulur.
 */

uint32_t union_find_find(UnionFind *uf, uint32_t x) {
	if (!uf || x >= uf->n) {
		return UINT32_MAX;
	}

	if (uf->parent[x] != x) {
		uf->parent[x] = union_find_find(uf, uf->parent[x]);
	}

	return uf->parent[x];
}

bool union_find_union(UnionFind *uf, uint32_t a, uint32_t b) {
	if (!uf || a >= uf->n || b >= uf->n) {
		return false;
	}

	uint32_t root_a = union_find_find(uf, a);
	uint32_t root_b = union_find_find(uf, b);

	if (root_a == root_b) {
		return false;
/**
 * @brief Verilen iki düğümün aynı kümede olup olmadığını kontrol eder.
 * 
 * @param uf: Üzerinde işlem yapılacak UnionFind yapısı
 * @param a: Kontrol edilecek birinci düğüm
 * @param b: Kontrol edilecek ikinci düğüm
 * 
 * @retval false: Düğümler farklı kümelerde ise veya geçersiz parametre varsa
 * @retval true: Düğümler aynı kümede ise
 * 
 * @author: Cafer Tura Çetin
 * 
 * @note: union_find_find fonksiyonunu arka planda kullandığı için karmaşıklığı ortalama O(α(n))'dir.
 */
	}

	if (uf->rank[root_a] < uf->rank[root_b]) {
		uf->parent[root_a] = root_b;
	} else if (uf->rank[root_a] > uf->rank[root_b]) {
		uf->parent[root_b] = root_a;
	} else {
		uf->parent[root_b] = root_a;
		uf->rank[root_a] += 1;
	}

	return true;
}

bool union_find_connected(UnionFind *uf, uint32_t a, uint32_t b) {
	if (!uf || a >= uf->n || b >= uf->n) {
		return false;
	}

	return union_find_find(uf, a) == union_find_find(uf, b);
}