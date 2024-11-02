#include "cache/lfu_cache.h"
#include "cache/pca_cache.h"
#include <boost/program_options.hpp>
#ifdef NO_OPTIMIZATION
    #include "graph/graph.h"
#endif

void runLFU() {
    int max_size;
    int num_of_num;
    int hits_counter = 0;
  
    std::cin >> max_size >> num_of_num;
    std::vector<int> num(num_of_num);

    for(int i = 0; i < num_of_num; i++) {
        std::cin >> num[i];
    }
        
    #ifdef NO_OPTIMIZATION
        LFU_cache_t<int> lfu(max_size, num_of_num, num);
    #else
        LFU_cache_t<int> lfu(max_size);
    #endif
    for(int i = 0; i < num_of_num; i++) {
        hits_counter += lfu.lookup_update(num[i]);
    }

    std::cout << "\n" << hits_counter << "\n";
}

void runPCA() {
    int max_size;
    int num_of_num;
    int hits_counter = 0;
    std::unordered_map<int, std::queue<int>> hash_entry_elem;

    std::cin >> max_size >> num_of_num;
    std::vector<int> num(num_of_num);

    for(int i = 0; i < num_of_num; i++) {
        std::cin >> num[i];
        hash_entry_elem[num[i]].push(i);
    }

    
    #ifdef NO_OPTIMIZATION
        PCA_cache_t<int> pca(max_size, num_of_num, num);
    #else
        PCA_cache_t<int> pca(max_size, num_of_num);
    #endif
    for(int i = 0; i < num_of_num; i++) {
        hits_counter += pca.lookup_update(num[i], hash_entry_elem);
    }

    std::cout << "\n" << hits_counter << "\n";
}

int main(int argc, char* argv[]) {
    std::string algorithm;

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("algorithm,a", boost::program_options::value<std::string>(&algorithm)->required(), "algorithm to run (lfu or pca)");

    boost::program_options::variables_map vm;
    
    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);
    } catch (const boost::program_options::required_option& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << desc << std::endl;
        return 1;
    } catch (const boost::program_options::error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    if (algorithm == "lfu") {
        runLFU();
    } else if (algorithm == "pca") {
        runPCA();
    } else {
        std::cerr << "Unknown algorithm: " << algorithm << std::endl;
        return 1;
    }

    return 0;
}