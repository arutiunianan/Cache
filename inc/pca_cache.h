#ifndef PCA_CACHES_H_
#define PCA_CACHES_H_

#include "log.h"

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

    FILE*  log;
    size_t number_of_call;
    int    errors;

    PCA_cache_t(size_t m_size, size_t a_size, T* data): 
        max_size(m_size), 
        arr_size(a_size), 
        curr_size(0), 
        hits_counter(0),
        number_of_call(1), 
        errors(0)          {
        log = fopen("logs/pca_log.txt", "wb");

        fprintf(log, "=======================================\n");
        fprintf(log, "           LFU CACHE DUMP\n");
        fprintf(log, "=======================================\n\n");
        fprintf(log, "CACHE SIZE: %d\n", m_size);
        fprintf(log, "DATA: ");
        for(size_t i = 0; i < a_size; i++) {
            fprintf(log,"%d ", data[i] );
        }
        fprintf(log,"\n\n");
        //log.close();
    }

    bool is_cache_full() {
        return curr_size == max_size;
    }

    T most_far_elem(int* data, size_t i) {
        std::list<T> buf_cache     = cache;
        size_t       buf_curr_size = curr_size;

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

    void update_elem_place(KeyT key) {
        if(cache.empty()) {
            errors |= CACHE_IS_EMPTY;
        }
        if(hash.find(key) == hash.end()) {
            errors |= HASH_HAST_THIS_KEY;
        }
        if(errors != 0) {
            return;
        }

        auto eltit = hash[key];
        if (eltit != cache.begin()) {
            cache.splice(cache.begin(), cache,
                    eltit, std::next(eltit));
        }
    }

    int chech_errors(int* data, size_t i) {
        if(data == nullptr) {
            errors |= DATA_IS_NULLPTR;
        }
        if(i < 0) {
            errors |= NEGATIVE_INDEX_OF_DATA;
        }
        if(max_size < 0) {
            errors |= NEGATIVE_CURR_SIZE;
        }
        if(curr_size < 0) {
            errors |= NEGATIVE_MAX_SIZE;
        }
        if(hits_counter < 0) {
            errors |= NEGATIVE_HITS_COUNTER;
        }
        dump<T>(log, errors, cache, curr_size, &number_of_call);
        return errors;
    }

    int lookup_update(T* data, size_t i) {
        assert(log);

        if(chech_errors(data, i)) {
            return errors;
        }

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
            update_elem_place(key);
        }

        return chech_errors(data, i);
    }
};

#endif // #define PCA_CACHES_H_