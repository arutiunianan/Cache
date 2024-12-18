#ifndef LFU_CACHES_H_
#define LFU_CACHES_H_

#include "log.h"

template <typename T, typename KeyT = int>
class LFU_cache_t {
private:
    int min_counter = 0;
    std::unordered_map<KeyT, std::list<T>> counter_list;

    int max_size;
    int curr_size = 0;
    
    std::list<T> cache;

    using it_list = typename std::list<T>::iterator; 
    struct hash_elem_t {
        it_list cache_iter;
        it_list counter_iter;
        int     counter;
        hash_elem_t(it_list cache_it, it_list counter_it): 
                                 cache_iter(cache_it),
                                 counter_iter(counter_it),
                                 counter(1){}
        hash_elem_t():           counter(0){}
    };
    std::unordered_map<KeyT, hash_elem_t> hash;

    #ifdef NO_OPTIMIZATION
        std::ofstream log;
        int    number_of_call = 1;
        int    errors         = 0;
    #endif

public:
    LFU_cache_t(int m_size ): max_size(m_size) {}

    #ifdef NO_OPTIMIZATION
        LFU_cache_t(int m_size, int a_size, std::vector<int>& data):
            max_size(m_size) {
            log.open("logs/lfu_log.txt");

            log << "=======================================\n";
            log << "           LFU CACHE DUMP\n";
            log << "=======================================\n\n";
            log << "CACHE SIZE: " << m_size << "\n";
            log << "DATA: ";
            for(int i = 0; i < a_size; i++) {
                log << data[i] << " ";
            }
            log << "\n\n";
        }
    #endif

    ~LFU_cache_t() {}

private:
    bool is_cache_full() const {
        return curr_size == max_size;
    }

    void update_elem_place(KeyT key) {
        #ifdef NO_OPTIMIZATION
            if(cache.empty()) {
                errors |= CACHE_IS_EMPTY;
            }
            if(hash.find(key) == hash.end()) {
                errors |= HASH_HAST_THIS_KEY;
            }
            if(errors) {
                return;
            }
        #else
            assert(!cache.empty() && "cache us empty");
            assert(hash.find(key) != hash.end() && "hash has't this key");
        #endif

        auto& hash_counter = hash[key].counter;
        counter_list[hash_counter].erase(hash[key].counter_iter);
        hash_counter++;
        counter_list[hash_counter].push_front(key);
        hash[key].counter_iter = counter_list[hash_counter].begin();

        if(counter_list[min_counter].empty()) {
            min_counter++;
        }
    }

    #ifdef NO_OPTIMIZATION
        int chech_errors() {
            if(max_size < 0) {
                errors |= NEGATIVE_CURR_SIZE;
            }
            if(curr_size < 0) {
                errors |= NEGATIVE_MAX_SIZE;
            }
            dump<T>(log, errors, cache, curr_size, &number_of_call);
            return errors;
        }
    #endif

public:
    int lookup_update(T list_elem, std::function<T(KeyT)> slow_get_page) {
        #ifdef NO_OPTIMIZATION
            if(chech_errors()) {
                return errors;
            }
        #else
            assert(max_size >= 0 && "max_size is neg");
            assert(curr_size >= 0 && "curr_size is neg");
        #endif

        KeyT key = list_elem; //in this hash: key = value
        auto hit = hash.find(key);
        if(hit == hash.end()) {
            if(is_cache_full()) {
                KeyT erase_key = counter_list[min_counter].back();
                cache.erase(hash[erase_key].cache_iter);
                hash.erase(erase_key);
                counter_list[min_counter].pop_back();
            }
            else {
                curr_size++;
            }

            min_counter = 1;
            counter_list[min_counter].push_front(key);
            cache.push_front(slow_get_page(key));
            hash_elem_t hash_elem(cache.begin(), counter_list[min_counter].begin());
            hash[key] = hash_elem;
        }
        else {
            update_elem_place(key);
            return 1;
        }
        
        #ifdef NO_OPTIMIZATION
            return chech_errors();
        #else
            assert(max_size >= 0 && "max_size is neg");
            assert(curr_size >= 0 && "curr_size is neg");
        #endif
        return 0;
    }

};

#endif // #define LFU_CACHES_H_