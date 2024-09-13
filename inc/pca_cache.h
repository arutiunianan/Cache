#ifndef PCA_CACHES_H_
#define PCA_CACHES_H_

#include <iostream>
#include <list>
#include <unordered_map>


template <typename T, typename KeyT = int>
struct PCA_cache_t {
    public:
    size_t       max_size;
    size_t       curr_size;
    size_t       hits_counter;
    std::list<T> cache;

    using it_list = typename std::list<T>::iterator; 
    /*struct hash_elem_t {
        it_list iter;
        hash_elem_t(it_list it): iter(it),      counter(0) {}
        hash_elem_t():           counter(0)                {}
    };*/
    //std::unordered_map<KeyT, hash_elem_t> hash;
    std::unordered_map<KeyT, it_list> hash;

    //PCA_cache_t(size_t size): max_size(size), curr_size(0), hits_counter(0) {}
    PCA_cache_t(size_t size): max_size(size), hits_counter(0) {}

    bool is_cache_full() {
        return curr_size == max_size;
    }

    /*void hash_and_cache_elems_swap(KeyT key1, KeyT key2) {
        T elem_buf    = *(hash[key1]);
        *(hash[key1]) = *(hash[key2]);
        *(hash[key2]) = elem_buf;

        it_list it_buf  = hash[key1];
        hash[key1]      = hash[key2];
        hash[key2]      = it_buf;
    }*/

    bool lookup_update(T list_elem) {
        KeyT key = list_elem; //in this hash: key = value
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
            //hash_elem_t hash_elem(cache.begin());
            //hash[key] = hash_elem;
            hash[key] = cache.begin();
            return false;
        }
        hits_counter++;
        //update elem place
        auto eltit = hit->second;
        if (eltit != cache.begin()) {
            cache.splice(cache.begin(), cache, eltit, std::next(eltit));
        }
        return true;
    }
};


#endif // #define PCA_CACHES_H_