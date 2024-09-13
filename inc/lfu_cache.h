#ifndef LFU_CACHES_H_
#define LFU_CACHES_H_

#include "cache.h"

template <typename T, typename KeyT = int>
class LFU_cache_t {
public:
    size_t       max_size;
    size_t       curr_size;
    size_t       hits_counter;
    std::list<T> cache;

    using it_list = typename std::list<T>::iterator; 
    struct hash_elem_t {
        it_list iter;
        size_t  counter;
        hash_elem_t(it_list it): iter(it), 
                                 counter(1){}
        hash_elem_t():           counter(0){}
    };
    std::unordered_map<KeyT, hash_elem_t> hash;

    LFU_cache_t(size_t size): max_size(size), 
                              curr_size(0), 
                              hits_counter(0) {}

    bool is_cache_full() {
        return curr_size == max_size;
    }

    it_list bin_search(it_list current, it_list begin, size_t distance) {
        it_list middle = std::next(begin, distance / 2);

        if(*middle == cache.back() || middle == cache.end()) {
            return cache.end();
        }

        it_list next_middle = std::next(middle, 1);
        if(hash[*middle].counter <= hash[*current].counter) {
            return bin_search(current, next_middle, distance / 2);
        }

        if(hash[*current].counter < hash[*next_middle].counter) {
            return middle;
        }

        return bin_search(current, begin, distance / 2);
    }

    bool lookup_update(T list_elem) {
        KeyT key = list_elem; //in this hash: key = value
        auto hit = hash.find(key);
        if(hit == hash.end()) {
            if(is_cache_full()) {
                hash.erase(cache.front());
                cache.pop_front();
            }
            else {
                curr_size++;
            }

            cache.push_front(list_elem);
            hash_elem_t hash_elem(cache.begin());
            hash[key] = hash_elem;
        }
        else {
            hits_counter++;
            hash[key].counter++;
        }

        //update elem place
        it_list curr_elem_iter = hash[key].iter;
        it_list next_elem_iter = std::next(curr_elem_iter,1);
        cache.splice(bin_search(curr_elem_iter, next_elem_iter, 
                                std::distance(next_elem_iter, cache.end())), 
                     cache, 
                     hash[key].iter);
        
    }
};

#endif // #define LFU_CACHES_H_