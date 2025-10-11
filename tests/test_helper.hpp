#pragma once

#include "Cache/Cache.h"
#include <type_traits>

// Helper to insert into key-value cache
template<typename Key, typename Value, template<typename> class CachePolicy, 
         typename Lock, template<typename...> class StatsProvider, typename Storage, 
         typename U, typename V>
void insert_helper(Cache<Key, Value, CachePolicy, Lock, StatsProvider, Storage>& cache, 
                   const U& key, const V& value) {
    cache.insert(key, value);
}

// Helper to insert into key-only cache (specialized for void)
template<typename Key, template<typename> class CachePolicy, 
         typename Lock, template<typename...> class StatsProvider, typename Storage,
         typename U, typename V>
void insert_helper(Cache<Key, void, CachePolicy, Lock, StatsProvider, Storage>& cache, 
                   const U& key, const V& /* ignored */) {
    cache.insert(key);
}
