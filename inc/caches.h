#ifndef CACHES_H_
#define CACHES_H_

#include <iostream>
#include <list>
#include <unordered_map>

template <typename T, typename KeyT = int>
struct LFU_cache_t {
    public:
    size_t       max_size;
    size_t       curr_size;
    std::list<T> cache;

    using it_list = typename std::list<T>::iterator; 
    struct hash_elem_t {
        it_list iter;
        int     counter;
        hash_elem_t(it_list it): iter(it),      counter(1) {}
        hash_elem_t():           counter(0)                {}
    };
    std::unordered_map<KeyT, hash_elem_t> hash;

    LFU_cache_t(size_t size): max_size(size), curr_size(0) {}
    /*    max_size  = size;
        curr_size = 0;

        cache = new std::list<T>[max_size];
    }*/

    bool is_cache_full() {
        return curr_size == max_size;
    }

    bool lookup_update(T list_elem, KeyT key) {
        auto hit = hash.find(key);
        if(hit == hash.end()) {
            if(is_cache_full()) {
                hash.erase(cache.back());
                cache.pop_back();
            }
            else {
                curr_size++;
            }

            cache.push_front(list_elem);
            hash_elem_t hash_elem(cache.begin());
            hash[key] = hash_elem;
            return false;
        }

        hash[key].counter++;
        /*if()
        //auto eltit = hit->second;

        //while(eltit != cache.begin()) {
            
        //}

        do {

        } while();*/

    }

};

#endif // #define CACHES_H_