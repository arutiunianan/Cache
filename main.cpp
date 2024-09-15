#include "cache/lfu_cache.h"
#include "cache/pca_cache.h"
#include "graph/graph.h"

int MAX_SIZE = 10;

int main() {
    int max_size;
    int num_of_num;
    
    std::cin >> max_size >> num_of_num;
    int num[num_of_num];
    
    for(int i = 0; i < num_of_num; i++) {
        std::cin >> num[i];
    }

    LFU_cache_t<int> lfu(max_size, num_of_num, num);
    PCA_cache_t<int> pca(max_size, num_of_num, num);
    Graph graph;

    for(size_t i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num, i);

        graph.add_hits(lfu.hits_counter, pca.hits_counter);
    }

    std::cout << "\nlfu: " << lfu.hits_counter << "\n";
    std::cout << "pca: " << pca.hits_counter << "\n";
    graph.print_graph();
}
