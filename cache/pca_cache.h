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
    PCA_cache_t(int m_size, int a_size, std::vector<int>& data): 
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

    ~PCA_cache_t() {}

private:
    bool is_cache_full() {
        return curr_size == max_size;
    }

    T most_far_elem(T& list_elem, std::unordered_map<T, std::queue<int>>& hash_entry_elem) {
        auto& list_elem_entry = hash_entry_elem[list_elem];
        if(list_elem_entry.empty()) {
            return list_elem;
        }

        T far_elem;
        int far_elem_entry = -1;
        it_list elem = cache.end();
        for(int i = 0; i < curr_size; i++) {
            T curr_elem = *--elem;

            auto& entry = hash_entry_elem[curr_elem];

            if(entry.empty()) {
                return curr_elem;
            }

            if(entry.front() >= far_elem_entry) {
                far_elem_entry = entry.front();
                far_elem = curr_elem;
            }
        }
        if(list_elem_entry.front() >= far_elem_entry) {
            return list_elem;
        }

        return far_elem;
    }

#ifndef OPTIMIZATION
    int chech_errors(int i) {
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
    int lookup_update(T& list_elem, std::unordered_map<T, std::queue<int>>& hash_entry_elem, int i) {
        #ifndef OPTIMIZATION
            assert(log);

            if(chech_errors(i)) {
                return errors;
            }
        #endif

        KeyT key = list_elem; //in this hash: key = value
        hash_entry_elem[list_elem].pop();

        auto hit = hash.find(key);
        if(hit == hash.end()) {
            if(is_cache_full()) {
                int far_elem = most_far_elem(list_elem, hash_entry_elem);
                if(far_elem == list_elem) {
                    #ifndef OPTIMIZATION
                        return chech_errors(i);
                    #else
                        return 1;
                    #endif
                }
                cache.erase(hash[far_elem]);
            }
            else {
                curr_size++;
            }
 
            cache.push_front(key);
            hash[key] = cache.begin();

            #ifndef OPTIMIZATION
                return chech_errors(i);
            #else
                return 1;
            #endif
        }
        hits_counter++;

        #ifndef OPTIMIZATION
            return chech_errors(i);
        #endif
    }
};

#endif // #define PCA_CACHES_H_