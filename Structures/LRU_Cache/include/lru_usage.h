#pragma once

//Cache data struct (info hiding)
typedef struct lru_cache lru_cache_t;

//Every usage function
lru_cache_t *lru_cache_create(int capacity);

int lru_cache_get(int key, lru_cache_t *ptr);

void lru_cache_put(int key, int value, lru_cache_t *ptr);

void lru_cache_print(lru_cache_t *ptr);

void lru_cache_clear(lru_cache_t *ptr);

void lru_cache_make_logs(lru_cache_t *ptr);

void lru_cache_remove_LRU(lru_cache_t *ptr);
