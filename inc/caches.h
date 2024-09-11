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

    void hash_and_cache_elems_swap(KeyT key1, KeyT key2) {
        T elem_buf         = *(hash[key1].iter);
        *(hash[key1].iter) = *(hash[key2].iter);
        *(hash[key2].iter) = elem_buf;

        it_list it_buf  = hash[key1].iter;
        hash[key1].iter = hash[key2].iter;
        hash[key2].iter = it_buf;
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
        it_list curr_elem_iter = hit->second.iter;
        it_list last_elem_iter = cache.end();
        last_elem_iter--;
        while(curr_elem_iter != last_elem_iter) {
            it_list next_elem_iter = curr_elem_iter;
            next_elem_iter++;
            int key1 = *curr_elem_iter;
            int key2 = *(next_elem_iter);
            //std::cout << "\n\n" << key1 << " " << key2 << "\n\n";
            if(hash[key1].counter >= hash[key2].counter) {
                //std::cout << "\n\n" << key1 << " " << key2 << " " << hash[key1].counter << hash[key2].counter << "\n\n";
                hash_and_cache_elems_swap(key1, key2);
                curr_elem_iter++;
            }
            else {
                break;
            }
        }
        return true;

    }

};



#endif // #define CACHES_H_