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

    std::ofstream log;
    int           errors;

    PCA_cache_t(size_t m_size, size_t a_size, T* data): 
        max_size(m_size), 
        arr_size(a_size), 
        curr_size(0), 
        hits_counter(0), 
        errors(0)         {
        log.open("logs/pca_log.txt");

        log << "=======================================\n" 
            << "           PCA CACHE DUMP\n"
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
        dump();
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