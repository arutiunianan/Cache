#ifndef PCA_CACHES_H_
#define PCA_CACHES_H_

#include "cache.h"

int NO_ELEM = 0xD2003;

template <typename T, typename KeyT = int>
class PCA_cache_t {
public:
    size_t       max_size;
    size_t       curr_size;
    size_t       arr_size;
    size_t       hits_counter;

    std::list<T> cache;

    using it_list = typename std::list<T>::iterator; 
    std::unordered_map<KeyT, it_list> hash;

    PCA_cache_t(size_t m_size, size_t a_size): max_size(m_size), 
                                               arr_size(a_size), 
                                               curr_size(0), 
                                               hits_counter(0) {}

    bool is_cache_full() {
        return curr_size == max_size;
    }

    T most_far_elem(int* data, size_t i) {
        std::list<T> buf_cache     = cache;
        size_t       buf_curr_size = curr_size;
        bool         flag          = false;

        for(size_t pos = i; pos < arr_size; pos++) {
            for(size_t j = 0; j < max_size; j++) {
                it_list elem = std::next(buf_cache.begin(), j);
                if(data[pos] == *elem) {
                    buf_cache.erase(elem);
                    buf_curr_size--;
                    break;
                }
            }
            if(buf_curr_size == 1){
                break;
            }
        }
        return buf_cache.back();
    }

    bool lookup_update(int* data, size_t i) {
        KeyT key = data[i]; //in this hash: key = value

        auto hit = hash.find(key);
        if(hit == hash.end()) {
            if (is_cache_full()) {
                size_t far_elem = most_far_elem(data, i);
                cache.erase(hash[far_elem]);
                hash.erase(far_elem);
            }
            else {
                curr_size++;
            }
 
            cache.push_front(key);
            hash[key] = cache.begin();
            
        }
        else {
            hits_counter++;

            auto eltit = hit->second;
            if (eltit != cache.begin()) {
                cache.splice(cache.begin(), cache,
                        eltit, std::next(eltit));
            }
        }
    }
};

#endif // #define PCA_CACHES_H_