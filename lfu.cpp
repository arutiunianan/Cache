#include "cache/lfu_cache.h"
#ifdef NO_OPTIMIZATION
    #include "graph/graph.h"
#endif

int main() {
    int max_size;
    int num_of_num;
    int hits_counter = 0;
  
    if(!(std::cin >> max_size >> num_of_num)) {
        std::cerr << "Incorrect input" << std::endl;
        return 1;
    }
    std::vector<int> num(num_of_num);

    for(int i = 0; i < num_of_num; i++) {
        if(!(std::cin >> num[i])) {
            std::cerr << "Incorrect input" << std::endl;
            return 1;
        }
    }
        
    #ifdef NO_OPTIMIZATION
        LFU_cache_t<int> lfu(max_size, num_of_num, num);
    #else
        LFU_cache_t<int> lfu(max_size);
    #endif
    for(int i = 0; i < num_of_num; i++) {
        hits_counter += lfu.lookup_update(num[i], slow_get_page);
    }

    std::cout << "\n" << hits_counter << "\n";
    return 0;
}