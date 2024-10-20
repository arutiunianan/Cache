#include "cache/lfu_cache.h"
#include "cache/pca_cache.h"
#include "graph/graph.h"


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

            PCA_cache_t<int> pca(max_size, num_of_num);
            for(int i = 0; i < num_of_num; i++) {
                pca.lookup_update(num[i], hash_entry_elem);
            }

            test_file >> answer >> answer;
            if(pca.hits_counter == answer) {
                std::cout << "Successful test - " << path + std::to_string(test) + ".txt" << "\n";
            }
            else {
                std::cout << "Failed test - " << path + std::to_string(test) + ".txt" << "\n";
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

        PCA_cache_t<int> pca(max_size, num_of_num);
        for(int i = 0; i < num_of_num; i++) {
            pca.lookup_update(num[i], hash_entry_elem);
        }

        std::cout << "\n" << pca.hits_counter << "\n\n";
    #endif

    return 0;
}