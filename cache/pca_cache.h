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

    T most_far_elem(T list_elem, std::unordered_map<T, std::list<int>> hash_entry_elem) {
        T far_elem = -1;
        if(hash_entry_elem[list_elem].begin() == hash_entry_elem[list_elem].end()) {
            return list_elem;
        }

        it_list elem = cache.end();
        for(int i = 0; i < curr_size; i++) {
            elem--;
            T curr_elem = *elem;
            if(hash_entry_elem[curr_elem].begin() == hash_entry_elem[curr_elem].end() 
               || hash_entry_elem[curr_elem].front() >= far_elem) {
                far_elem = curr_elem;
            }
        }
        if(hash_entry_elem[list_elem].front() >= far_elem) {
            return list_elem;
        }

        return far_elem;
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
    int lookup_update(T list_elem, std::unordered_map<T, std::list<int>>& hash_entry_elem, int i) {
        #ifndef OPTIMIZATION
            assert(log);

            if(chech_errors(i)) {
                return errors;
            }
        #endif

        KeyT key = list_elem; //in this hash: key = value
        hash_entry_elem[list_elem].pop_front();

        /*std::list<int>::iterator p = hash_entry_elem[list_elem].begin();
        std::cout << list_elem <<": ";
        while(p != hash_entry_elem[list_elem].end()) {
            std::cout << *p << " ";
            p++;
        }
        std::cout << "\n";
        

        std::list<int>::iterator pip = hash_entry_elem[list_elem].begin();
        std::cout << list_elem <<": ";
        while(pip != hash_entry_elem[list_elem].end()) {
            std::cout << *pip << " ";
            pip++;
        }
        std::cout << "\n\n";*/

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
            return chech_errors(i);
        #endif
    }
};

#endif // #define PCA_CACHES_H_