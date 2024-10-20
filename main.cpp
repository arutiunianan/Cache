#include "cache/lfu_cache.h"
#include "cache/pca_cache.h"
#ifdef NO_OPTIMIZATION
    #include "graph/graph.h"
#endif

int main() {
    int max_size;
    int num_of_num;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    #ifdef TEST
        int answer;
        std::string path = "../test/unit_tests/test";
        std::vector<int> test_num = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        for(const auto& test: test_num) {
            std::ifstream test_file;
            test_file.open(path + std::to_string(test) + ".txt");
            test_file >> max_size >> num_of_num;
            std::vector<int> num(num_of_num);

            for(int i = 0; i < num_of_num; i++) {
                test_file >> num[i];
                hash_entry_elem[num[i]].push(i);
            }

            LFU_cache_t<int> lfu(max_size);
            PCA_cache_t<int> pca(max_size, num_of_num);
            for(int i = 0; i < num_of_num; i++) {
                lfu.lookup_update(num[i]);
                pca.lookup_update(num[i], hash_entry_elem);
            }

            test_file >> answer;
            if(lfu.hits_counter == answer) {
                std::cout << "Successful lfu test - " << path + std::to_string(test) + ".txt" << "\n";
            }
            else {
                std::cout << "Failed lfu test - " << path + std::to_string(test) + ".txt" << "\n";
                std::cout << answer << " " << lfu.hits_counter << "\n";
            }

            test_file >> answer;
            if(pca.hits_counter == answer) {
                std::cout << "Successful pca test - " << path + std::to_string(test) + ".txt" << "\n";
            }
            else {
                std::cout << "Failed pca test - " << path + std::to_string(test) + ".txt" << "\n";
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

        #ifdef NO_OPTIMIZATION
            Graph graph;
        #endif
        LFU_cache_t<int> lfu(max_size 
                            #ifdef NO_OPTIMIZATION
                                ,num_of_num, num
                            #endif
                            );
        PCA_cache_t<int> pca(max_size, num_of_num
                            #ifdef NO_OPTIMIZATION
                                , num
                            #endif
                            );
        for(int i = 0; i < num_of_num; i++) {
            lfu.lookup_update(num[i]);
            pca.lookup_update(num[i], hash_entry_elem);

            #ifdef NO_OPTIMIZATION
                graph.add_hits(lfu.hits_counter, pca.hits_counter);
            #endif
        }

        std::cout << "\n" << lfu.hits_counter << "\n";     
        std::cout << "\n" << pca.hits_counter << "\n";
        #ifdef NO_OPTIMIZATION
            graph.print_graph();
        #endif
    #endif

    return 0;
}
