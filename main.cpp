#include "cache/lfu_cache.h"
#include "cache/pca_cache.h"
#ifndef OPTIMIZATION
    #include "graph/graph.h"
#endif

int main() {
    int max_size;
    int num_of_num;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    #ifdef TEST
        std::ifstream test_file;
        test_file.open("../test/test.txt");
        test_file >> max_size >> num_of_num;
        std::vector<int> num(num_of_num);

        for(int i = 0; i < num_of_num; i++) {
            test_file >> num[i];
            hash_entry_elem[num[i]].push(i);
        }
    #else
        std::cin >> max_size >> num_of_num;
        std::vector<int> num(num_of_num);

        for(int i = 0; i < num_of_num; i++) {
            std::cin >> num[i];
            hash_entry_elem[num[i]].push(i);
        }
    #endif

    #ifndef OPTIMIZATION
        Graph graph;
    #endif
    LFU_cache_t<int> lfu(max_size, num_of_num, num);
    PCA_cache_t<int> pca(max_size, num_of_num, num);
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num[i], hash_entry_elem, i);

        #ifndef OPTIMIZATION
            graph.add_hits(lfu.hits_counter, pca.hits_counter);
        #endif
    }

    std::cout << "\n" << lfu.hits_counter << "\n";     
    std::cout << "\n" << pca.hits_counter << "\n";
    #ifndef OPTIMIZATION
        graph.print_graph();
    #endif

    return 0;
}
