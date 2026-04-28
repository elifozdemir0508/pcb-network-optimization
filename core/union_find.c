#include "union_find.h"

#include <stdlib.h>

UnionFind *union_find_create(uint32_t n) {
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

void union_find_destroy(UnionFind *uf) {
	if (!uf) {
		return;
	}

	free(uf->parent);
	free(uf->rank);
	free(uf);
}
