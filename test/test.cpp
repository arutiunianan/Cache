#include <gtest/gtest.h>
#include "../cache/lfu_cache.h"
#include "../cache/pca_cache.h"

TEST(Test, Subtestv) {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    int num_of_tests = 13;
    for(int i = 1; i <= num_of_tests; ++i) {
        std::string file_path  = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/test/unit_tests/test" + 
                                 std::to_string(i) + ".txt";
        std::ifstream test_file;
        test_file.open(file_path);

        test_file >> max_size >> num_of_num;
        std::vector<int> num(num_of_num);
    
        for(int i = 0; i < num_of_num; i++) {
            test_file >> num[i];
            hash_entry_elem[num[i]].push(i);
        }

        LFU_cache_t<int> lfu(max_size);
        PCA_cache_t<int> pca(max_size, num_of_num);

        int lfu_hits_counter = 0;
        int pca_hits_counter = 0;
        for(int i = 0; i < num_of_num; i++) {
            lfu_hits_counter += lfu.lookup_update(num[i]);
            pca_hits_counter += pca.lookup_update(num[i], hash_entry_elem);
        }

        test_file >> answer;
        ASSERT_TRUE(lfu_hits_counter == answer && i);
        test_file >> answer;
        ASSERT_TRUE(pca_hits_counter == answer && i);
        test_file.close();
    }
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}