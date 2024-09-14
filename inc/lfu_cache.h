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

    std::ofstream log;
    int           errors;

    LFU_cache_t(size_t m_size, size_t a_size, T* data): 
        max_size(m_size), 
        curr_size(0), 
        hits_counter(0),
        errors(0)        {
        log.open("logs/lfu_log.txt");

        log << "=======================================\n" 
            << "           LFU CACHE DUMP\n"
            << "=======================================\n\n";
        log << "CACHE SIZE: " << m_size << "\n";
        log << "DATA: ";
        for(size_t i = 0; i < a_size; i++) {
            log << data[i] << " ";
        }
        log << "\n\n";
    }

    bool is_cache_full() {
        return curr_size == max_size;
    }

    it_list bin_search(it_list current, it_list begin, size_t distance) {
        it_list middle = std::next(begin, distance / 2);
        it_list next_middle = std::next(middle, 1);

        if(hash[*current].counter < 1 || hash[*middle].counter < 1 || hash[*next_middle].counter < 1) {
            errors |= NEGATIVE_ELEM_COUNTER;
        }
        if(errors != 0) {
            return current;
        }

        if(*middle == cache.back() || middle == cache.end()) {
            return cache.end();
        }
        
        if(hash[*middle].counter <= hash[*current].counter) {
            return bin_search(current, next_middle, distance / 2);
        }

        if(hash[*current].counter < hash[*next_middle].counter) {
            return middle;
        }

        return bin_search(current, begin, distance / 2);
    }


    void dump() {
        static size_t number_of_call = 1;
	    log <<  "=======================================\nDUMP CALL #" << (number_of_call + 1) / 2 << "." 
                                                                       << (number_of_call + 1) % 2 + 1 << "\n";
        if(errors)
	    {
		    log << "-------------ERRORS------------\n";
            if(errors & CACHE_IS_EMPTY)         log << "CACHE IS EMPTY\n";
		    if(errors & HASH_HAST_THIS_KEY)     log << "HASH HAS'T ELEMENT WITH THIS KEY\n";
		    if(errors & NEGATIVE_CURR_SIZE)     log << "NEGATIVE CURRENT CACHE SIZE\n";
	        if(errors & NEGATIVE_MAX_SIZE)      log << "NEGATIVE MAXIMUM CACHE SIZE\n";
	        if(errors & NEGATIVE_HITS_COUNTER)  log << "NEGATIVE HITS COUNTER \n";
            if(errors & NEGATIVE_ELEM_COUNTER)  log << "NEGATIVE ELEMENT COUNTER \n";
            if(errors & NEGATIVE_INDEX_OF_DATA) log << "NEGATIVE INDEX OF DATA\n";
	        if(errors & NEGATIVE_DATA_SIZE)     log << "NEGATIVE DATA SIZE \n";
            if(errors & NEGATIVE_ELEM_COUNTER)  log << "DATA IS NULLPTR \n";

		    log << "----------END_OF_ERRORS--------\n";
	    }
	    else
        {
		    log << "------------NO_ERRORS----------\n";
            log << "Current Cache\n";

            std::list<int>::iterator it = cache.begin();
            for(size_t i = 0; i < curr_size; i++) {
                log << *(it++) << " ";
            }
            log << "\n";

        }
	    log << "=======================================\n\n";
	    number_of_call++;
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
        dump();
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