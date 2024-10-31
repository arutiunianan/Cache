#include "cache/lfu_cache.h"
#include "cache/pca_cache.h"
#include <boost/program_options.hpp>
#ifdef NO_OPTIMIZATION
    #include "graph/graph.h"
#endif

void runLFU() {
    int max_size;
    int num_of_num;
  
    std::cin >> max_size >> num_of_num;
    std::vector<int> num(num_of_num);

    for(int i = 0; i < num_of_num; i++) {
        std::cin >> num[i];
    }
        
    LFU_cache_t<int> lfu(max_size);
    for(int i = 0; i < num_of_num; i++) {
        lfu.lookup_update(num[i]);
    }

    std::cout << "\n" << lfu.hits_counter << "\n";
}

void runPCA() {
    int max_size;
    int num_of_num;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

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
}

int main(int argc, char* argv[]) {
    std::string algorithm;

    boost::program_options::options_description desc;
    desc.add_options()
        ("algorithm,a", boost::program_options::value<std::string>(&algorithm)->required());

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);    
    
    if(algorithm == "lfu") {
        runLFU();
    } else if(algorithm == "pca") {
        runPCA();
    } else {
        std::cerr << "Unknown algorithm" << std::endl;
        return 1;
    }

    return 0;
}