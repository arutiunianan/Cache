#include <gtest/gtest.h>
#include "../cache/lfu_cache.h"
#include "../cache/pca_cache.h"

TEST(Test, Subtestv) {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    int num_of_tests = 15;
    for(int i = 1; i <= num_of_tests; ++i) {
        std::string file_path  = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/test/unit_tests/test" + 
                                 std::to_string(i) + ".txt";
        std::ifstream test_file;
        test_file.open(file_path);
        assert(test_file);

        if(!(test_file >> max_size >> num_of_num)) {
            continue;
        }
        std::vector<int> num(num_of_num);

        LFU_cache_t<int> lfu(max_size);
        PCA_cache_t<int> pca(max_size, num_of_num);
    
        bool flag = true;
        for(int j = 0; j < num_of_num; j++) {
            if(!(test_file >> num[j])) {
                flag = false;
                break;
            }
            pca.push_hash_entry_elem(num[j], j);
        }
        if(!flag) {
            continue;
        }

        

        int lfu_hits_counter = 0;
        int pca_hits_counter = 0;
        for(int j = 0; j < num_of_num; j++) {
            lfu_hits_counter += lfu.lookup_update(num[j], slow_get_page);
            pca_hits_counter += pca.lookup_update(num[j], slow_get_page);
        }
        test_file >> answer;
        ASSERT_TRUE(lfu_hits_counter == answer);
        test_file >> answer;
        ASSERT_TRUE(pca_hits_counter == answer);
        test_file.close();
    }
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}