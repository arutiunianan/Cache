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

    #ifdef NO_OPTIMIZATION
        std::ofstream log;
        int    number_of_call = 1;
        int    errors         = 0;
    #endif

public:
    PCA_cache_t(int m_size, int a_size
                #ifdef NO_OPTIMIZATION 
                    , std::vector<int>& data 
                #endif
                ):
        max_size(m_size), 
        arr_size(a_size) {
        #ifdef NO_OPTIMIZATION
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
    inline bool is_cache_full() {
        return curr_size == max_size;
    }

    T most_far_elem(T& list_elem, std::unordered_map<T, std::queue<int>>& hash_entry_elem) {
        const auto& list_elem_entry = hash_entry_elem[list_elem];

        T far_elem = list_elem;
        int far_elem_entry = list_elem_entry.front();
        it_list elem = cache.end();
        for(int i = 0; i < curr_size; i++) {
            elem = std::prev(elem);
            T curr_elem = *elem;
            auto& entry = hash_entry_elem[curr_elem];
            if(entry.front() >= far_elem_entry) {
                far_elem_entry = entry.front();
                far_elem = curr_elem;
            }
        }

        return far_elem;
    }

#ifdef NO_OPTIMIZATION
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
#endif

public:
    int lookup_update(T& list_elem, std::unordered_map<T, std::queue<int>>& hash_entry_elem) {
        #ifdef NO_OPTIMIZATION
            if(chech_errors()) {
                return errors;
            }
        #endif

        KeyT key = list_elem; //in this hash: key = value
        auto& queue = hash_entry_elem[list_elem];
        queue.pop();

        auto hit = hash.find(key);
        if(hit == hash.end()) {
            if(queue.empty()) {
                return 0;
            }
            if(is_cache_full()) {
                int far_elem = most_far_elem(list_elem, hash_entry_elem);
                if(far_elem == list_elem) {
                    #ifdef NO_OPTIMIZATION
                        return chech_errors(i);
                    #else
                        return 0;
                    #endif
                }
                cache.erase(hash[far_elem]);
                hash.erase(far_elem);
            }
            else { 
                ++curr_size;
            }
 
            cache.push_front(key);
            hash[key] = cache.begin();

            #ifdef NO_OPTIMIZATION
                return chech_errors(i);
            #else
                return 0;
            #endif
        }
        ++hits_counter;
        if(queue.empty()) {
            cache.erase(hash[list_elem]);
            hash.erase(list_elem);
            --curr_size;
        }

        #ifdef NO_OPTIMIZATION
            return chech_errors(i);
        #endif
        return 0;
    }
};

#endif // #define PCA_CACHES_H_