#include <gtest/gtest.h>
#include "../cache/lfu_cache.h"
#include "../cache/pca_cache.h"

TEST(Test, Subtestv_1) {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    std::string file_path  = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/test/unit_tests/test1.txt";
    std::cerr << file_path << "\n\n";
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
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num[i], hash_entry_elem);
    }

    test_file >> answer;
    ASSERT_TRUE(lfu.hits_counter == answer);
    test_file >> answer;
    ASSERT_TRUE(pca.hits_counter == answer);
}

TEST(Test, Subtestv_2) {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    std::string file_path  = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/test/unit_tests/test2.txt";
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
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num[i], hash_entry_elem);
    }

    test_file >> answer;
    ASSERT_TRUE(lfu.hits_counter == answer);
    test_file >> answer;
    ASSERT_TRUE(pca.hits_counter == answer);
}

TEST(Test, Subtestv_3) {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    std::string file_path = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/test/unit_tests/test3.txt";
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
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num[i], hash_entry_elem);
    }

    test_file >> answer;
    ASSERT_TRUE(lfu.hits_counter == answer);
    test_file >> answer;
    ASSERT_TRUE(pca.hits_counter == answer);
}

TEST(Test, Subtestv_4) {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    std::string file_path = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/test/unit_tests/test4.txt";
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
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num[i], hash_entry_elem);
    }

    test_file >> answer;
    ASSERT_TRUE(lfu.hits_counter == answer);
    test_file >> answer;
    ASSERT_TRUE(pca.hits_counter == answer);
}

TEST(Test, Subtestv_5) {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    std::string file_path = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/test/unit_tests/test5.txt";
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
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num[i], hash_entry_elem);
    }

    test_file >> answer;
    ASSERT_TRUE(lfu.hits_counter == answer);
    test_file >> answer;
    ASSERT_TRUE(pca.hits_counter == answer);
}

TEST(Test, Subtestv_6) {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    std::string file_path = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/test/unit_tests/test6.txt";
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
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num[i], hash_entry_elem);
    }

    test_file >> answer;
    ASSERT_TRUE(lfu.hits_counter == answer);
    test_file >> answer;
    ASSERT_TRUE(pca.hits_counter == answer);
}

TEST(Test, Subtestv_7) {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    std::string file_path = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/test/unit_tests/test7.txt";
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
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num[i], hash_entry_elem);
    }

    test_file >> answer;
    ASSERT_TRUE(lfu.hits_counter == answer);
    test_file >> answer;
    ASSERT_TRUE(pca.hits_counter == answer);
}

TEST(Test, Subtestv_8) {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    std::string file_path = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/test/unit_tests/test8.txt";
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
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num[i], hash_entry_elem);
    }

    test_file >> answer;
    ASSERT_TRUE(lfu.hits_counter == answer);
    test_file >> answer;
    ASSERT_TRUE(pca.hits_counter == answer);
}

TEST(Test, Subtestv_9) {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    std::string file_path = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/test/unit_tests/test9.txt";
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
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num[i], hash_entry_elem);
    }

    test_file >> answer;
    ASSERT_TRUE(lfu.hits_counter == answer);
    test_file >> answer;
    ASSERT_TRUE(pca.hits_counter == answer);
}

TEST(Test, Subtestv_10) {
    int max_size;
    int num_of_num;
    int answer;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    std::string file_path = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/test/unit_tests/test10.txt";
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
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
        pca.lookup_update(num[i], hash_entry_elem);
    }

    test_file >> answer;
    ASSERT_TRUE(lfu.hits_counter == answer);
    test_file >> answer;
    ASSERT_TRUE(pca.hits_counter == answer);
}



int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}