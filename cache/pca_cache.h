#ifndef PCA_CACHES_H_
#define PCA_CACHES_H_

#include "log.h"

template <typename T, typename KeyT = int>
class PCA_cache_t {
public:
    int hits_counter = 0;

private:
    int max_size;
    int curr_size = 0;
    int arr_size;

    std::list<T> cache;

    using it_list = typename std::list<T>::iterator; 
    std::unordered_map<KeyT, it_list> hash;

    #ifndef OPTIMIZATION
        std::ofstream log;
        int    number_of_call = 1;
        int    errors         = 0;
    #endif

public:
    PCA_cache_t(int m_size, int a_size, T* data): 
        max_size(m_size), 
        arr_size(a_size) {
        #ifndef OPTIMIZATION
            log.open("logs/pca_log.txt");

            log << "=======================================\n";
            log << "           PCA CACHE DUMP\n";
            log << "=======================================\n\n";
            log << "CACHE SIZE: " << m_size << "\n";
            log << "DATA: ";
            for(int i = 0; i < a_size; i++) {
                log << data[i] << " ";
            }
            log << "\n\n";
        #endif
    }

    ~PCA_cache_t() {
        cache.clear();
        hash.clear();

        max_size     = 0xDEAD;
        curr_size    = 0xDEAD;
        arr_size     = 0xDEAD;
        hits_counter = 0xDEAD;

        #ifndef OPTIMIZATION
            log.close();
            number_of_call = 0xDEAD;
            errors         = 0xDEAD;
        #endif
    }

private:
    bool is_cache_full() {
        return curr_size == max_size;
    }

    T most_far_elem(int* data, int i) {
        std::list<T> buf_cache     = cache;
        int          buf_curr_size = curr_size + 1;
        buf_cache.push_front(data[i]);

        for(int pos = i + 1; pos < arr_size; pos++) {
            for(int j = 0; j < buf_curr_size; j++) {
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
        #ifndef OPTIMIZATION
            if(cache.empty()) {
                errors |= CACHE_IS_EMPTY;
            }
            if(hash.find(key) == hash.end()) {
                errors |= HASH_HAST_THIS_KEY;
            }
            if(errors != 0) {
                return;
            }
        #endif

        auto eltit = hash[key];
        if (eltit != cache.begin()) {
            cache.splice(cache.begin(), cache,
                    eltit, std::next(eltit));
        }
    }

#ifndef OPTIMIZATION
    int chech_errors(int* data, int i) {
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
#endif

public:
    int lookup_update(T* data, int i) {
        #ifndef OPTIMIZATION
            assert(log);

            if(chech_errors(data, i)) {
                return errors;
            }
        #endif

        KeyT key = data[i]; //in this hash: key = value

        auto hit = hash.find(key);
        if(hit == hash.end()) {
            if(is_cache_full()) {
                int far_elem = most_far_elem(data, i);
                if(far_elem == data[i]) {
                    #ifndef OPTIMIZATION
                        return chech_errors(data, i);
                    #else
                        return 1;
                    #endif
                }
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

        #ifndef OPTIMIZATION
            return chech_errors(data, i);
        #endif
    }
};

#endif // #define PCA_CACHES_H_