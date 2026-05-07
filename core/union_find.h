#ifndef UNION_FIND_H_
#define UNION_FIND_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint32_t n;
	uint32_t *parent;
	uint32_t *rank;
} UnionFind;

UnionFind *union_find_create(uint32_t n);
void union_find_destroy(UnionFind *uf);

uint32_t union_find_find(UnionFind *uf, uint32_t x);
bool union_find_union(UnionFind *uf, uint32_t a, uint32_t b);
bool union_find_connected(UnionFind *uf, uint32_t a, uint32_t b);

#endif