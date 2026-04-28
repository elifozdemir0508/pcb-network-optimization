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

uint32_t union_find_find(UnionFind *uf, uint32_t x) {
	if (!uf || x >= uf->n) {
		return x;
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