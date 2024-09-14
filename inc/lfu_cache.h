#ifndef LFU_CACHES_H_
#define LFU_CACHES_H_

#include "log.h"

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

    FILE*  log;
    size_t number_of_call;
    int    errors;

    LFU_cache_t(size_t m_size, size_t a_size, T* data): 
        max_size(m_size), 
        curr_size(0), 
        hits_counter(0),
        number_of_call(1),
        errors(0)         {
        log = fopen("logs/lfu_log.txt", "wb");

        fprintf(log, "=======================================\n");
        fprintf(log, "           LFU CACHE DUMP\n");
        fprintf(log, "=======================================\n\n");
        fprintf(log, "CACHE SIZE: %d\n", m_size);
        fprintf(log, "DATA: ");
        for(size_t i = 0; i < a_size; i++) {
            fprintf(log,"%d ", data[i] );
        }
        fprintf(log,"\n\n");
    }

    ~LFU_cache_t() {
        cache.clear();
        hash.clear();

        max_size     = 0xDEAD;
        curr_size    = 0xDEAD;
        hits_counter = 0xDEAD;

        fclose(log);
        number_of_call = 0xDEAD;
        errors         = 0xDEAD;
    }

    bool is_cache_full() {
        return curr_size == max_size;
    }

    it_list bin_search(it_list current, it_list begin, size_t distance) {
        it_list middle = std::next(begin, distance / 2);
        if(*middle == cache.back() || middle == cache.end()) {
            return cache.end();
        }

        it_list next_middle = std::next(middle, 1);
        
        if(hash[*current].counter < 1 || hash[*middle].counter < 1 || hash[*next_middle].counter < 1) {//
            errors |= NEGATIVE_ELEM_COUNTER;
        }
        if(errors) {
            return current;
        }

        if(hash[*middle].counter <= hash[*current].counter) {
            return bin_search(current, next_middle, distance / 2);
        }

        if(hash[*current].counter < hash[*next_middle].counter) {
            return middle;
        }

        return bin_search(current, begin, distance / 2);
    }

    void update_elem_place(KeyT key) {
        if(cache.empty()) {
            errors |= CACHE_IS_EMPTY;
        }
        if(hash.find(key) == hash.end()) {
            errors |= HASH_HAST_THIS_KEY;
        }
        if(errors) {
            return;
        }

        it_list curr_elem_iter = hash[key].iter;
        it_list next_elem_iter = std::next(curr_elem_iter,1);
        cache.splice(bin_search(curr_elem_iter, next_elem_iter, 
                                std::distance(next_elem_iter, cache.end())), 
                     cache, 
                     hash[key].iter);
    }

    int chech_errors() {
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

    int lookup_update(T list_elem) {
        assert(log);

        if(chech_errors()) {
            return errors;
        }
//4 12 1 2 3 4 1 2 5 1 2 4 3 4
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

        update_elem_place(key);

        return chech_errors();
    }

};

#endif // #define LFU_CACHES_H_