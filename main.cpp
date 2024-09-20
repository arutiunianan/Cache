#include "cache/lfu_cache.h"
#include "cache/pca_cache.h"
#include "graph/graph.h"

int main(int argc, const char* argv[]) {
    int max_size;
    int num_of_num;

    std::ifstream test_file;
    if(argc == 2) {
        std::cin >> max_size >> num_of_num;
    }
    else if(argc == 3){
        test_file.open(argv[2]);
        test_file >> max_size >> num_of_num;
    }
    else {
        std::cout << "Invalid number of args to program!\n";
        return 1;
    }
    
    int num[num_of_num];

    if(argc == 2) {
        for(int i = 0; i < num_of_num; i++) {
            std::cin >> num[i];
        }
    }
    else {
        for(int i = 0; i < num_of_num; i++) {
            test_file >> num[i];
        }
    }

    //Graph graph;
    if(atoi(argv[1]) & 1) {
        LFU_cache_t<int> lfu(max_size, num_of_num, num);
        for(size_t i = 0; i < num_of_num; i++) {
            lfu.lookup_update(num[i]);
        }
        std::cout << "\nlfu: " << lfu.hits_counter << "\n";
    }
    if(atoi(argv[1]) & 2) {
        PCA_cache_t<int> pca(max_size, num_of_num, num);
        for(size_t i = 0; i < num_of_num; i++) {
            pca.lookup_update(num, i);
            //graph.add_hits(lfu.hits_counter, pca.hits_counter);
        }
        std::cout << "\npca: " << pca.hits_counter << "\n\n";
        //graph.print_graph();
    }

    return 0;
}
