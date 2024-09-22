#include "cache/lfu_cache.h"
#include "cache/pca_cache.h"
#ifndef OPTIMIZATION
    #include "graph/graph.h"
#endif

int main() {
    int max_size;
    int num_of_num;

    #ifdef TEST
        std::ifstream test_file;
        test_file.open("test/test.txt");
        test_file >> max_size >> num_of_num;
        int num[num_of_num];

        for(int i = 0; i < num_of_num; i++) {
            test_file >> num[i];
        }
    #else
        std::cin >> max_size >> num_of_num;
        int num[num_of_num];

        for(int i = 0; i < num_of_num; i++) {
            std::cin >> num[i];
        }
    #endif

    #ifndef OPTIMIZATION
        Graph graph;
    #endif
    LFU_cache_t<int> lfu(max_size, num_of_num, num);
    PCA_cache_t<int> pca(max_size, num_of_num, num);
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num, i);

        #ifndef OPTIMIZATION
            graph.add_hits(lfu.hits_counter, pca.hits_counter);
        #endif
    }

    std::cout << "\nlfu: " << lfu.hits_counter << "\n";     
    std::cout << "\npca: " << pca.hits_counter << "\n\n";
    #ifndef OPTIMIZATION
        graph.print_graph();
    #endif

    return 0;
}
