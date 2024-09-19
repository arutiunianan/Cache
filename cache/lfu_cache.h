#ifndef LFU_CACHES_H_
#define LFU_CACHES_H_

#include "log.h"

template <typename T, typename KeyT = int>
class LFU_cache_t {
public:
    size_t hits_counter = 0;

private:
    size_t max_size;
    size_t curr_size = 0;
    
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

    std::ofstream log;
    size_t number_of_call = 1;
    int    errors         = 0;

public:
    LFU_cache_t(size_t m_size, size_t a_size, T* data): 
        max_size(m_size) {
        log.open("logs/lfu_log.txt");

        log << "=======================================\n";
        log << "           LFU CACHE DUMP\n";
        log << "=======================================\n\n";
        log << "CACHE SIZE: " << m_size << "\n";
        log << "DATA: ";
        for(size_t i = 0; i < a_size; i++) {
            log << data[i] << " ";
        }
        log << "\n\n";
    }

    ~LFU_cache_t() {
        cache.clear();
        hash.clear();

        max_size     = 0xDEAD;
        curr_size    = 0xDEAD;
        hits_counter = 0xDEAD;

        log.close();
        number_of_call = 0xDEAD;
        errors         = 0xDEAD;
    }

private:
    bool is_cache_full() {
        return curr_size == max_size;
    }

    it_list bin_search(it_list current, it_list begin, size_t distance) {
        it_list middle = std::next(begin, distance / 2);
        if((*middle == cache.back() && hash[*middle].counter <= hash[*current].counter) 
            || middle == cache.end()) {
            return cache.end();
        }
        if(*middle == cache.back()) {
            return std::next(cache.end(), -1);
        }
        
        it_list next_middle = std::next(middle, 1);
        
        if(hash[*current].counter < 1 
           || hash[*middle].counter < 1 
           || hash[*next_middle].counter < 1) {
            errors |= NEGATIVE_ELEM_COUNTER;
        }
        if(errors) {
            return current;
        }
        
        if(hash[*middle].counter <= hash[*current].counter) {
            return bin_search(current, next_middle, distance / 2 - 1);
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

public:
    int lookup_update(T list_elem) {
        assert(log);

        if(chech_errors()) {
            return errors;
        }
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