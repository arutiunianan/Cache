#include "cache/lfu_cache.h"
#include "cache/pca_cache.h"
#ifndef OPTIMIZATION
    #include "graph/graph.h"
#endif

int main() {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    #ifdef TEST
        std::string path = "../test/unit_tests";
        for(const auto& file: std::filesystem::directory_iterator(path)) {
            std::ifstream test_file;
            test_file.open(file.path());
            test_file >> max_size >> num_of_num;
            std::vector<int> num(num_of_num);

            for(int i = 0; i < num_of_num; i++) {
                test_file >> num[i];
                hash_entry_elem[num[i]].push(i);
            }

            LFU_cache_t<int> lfu(max_size, num_of_num, num);
            PCA_cache_t<int> pca(max_size, num_of_num, num);
            for(int i = 0; i < num_of_num; i++) {
                lfu.lookup_update(num[i]);
                pca.lookup_update(num[i], hash_entry_elem, i);
            }

            test_file >> answer;
            if(lfu.hits_counter == answer) {
                std::cout << "Successful lfu test - " << file.path() << "\n";
            }
            else {
                std::cout << "Failed lfu test - " << file.path() << "\n";
                std::cout << answer << " " << lfu.hits_counter << "\n";
            }

            test_file >> answer;
            if(pca.hits_counter == answer) {
                std::cout << "Successful pca test - " << file.path() << "\n";
            }
            else {
                std::cout << "Failed pca test - " << file.path() << "\n";
                std::cout << answer << " " << pca.hits_counter << "\n";
            }
        }
    #else
        std::cin >> max_size >> num_of_num;
        std::vector<int> num(num_of_num);

        for(int i = 0; i < num_of_num; i++) {
            std::cin >> num[i];
            hash_entry_elem[num[i]].push(i);
        }

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
    #endif

    return 0;
}
