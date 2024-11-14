#include "cache/pca_cache.h"
#ifdef NO_OPTIMIZATION
    #include "graph/graph.h"
#endif

int main() {
    int max_size;
    int num_of_num;
    int hits_counter = 0;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

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
        hash_entry_elem[num[i]].push(i);
    }

    
    #ifdef NO_OPTIMIZATION
        PCA_cache_t<int> pca(max_size, num_of_num, num);
    #else
        PCA_cache_t<int> pca(max_size, num_of_num);
    #endif
    for(int i = 0; i < num_of_num; i++) {
        hits_counter += pca.lookup_update(num[i], hash_entry_elem, slow_get_page);
    }

    std::cout << "\n" << hits_counter << "\n";
    return 0;
}