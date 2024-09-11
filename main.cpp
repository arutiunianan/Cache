#include "inc/caches.h"

int MAX_SIZE = 10;

int main() {
    LFU_cache_t<int> lfu(MAX_SIZE);
    int num;
    
    for(int i = 0; i < 11; i++) {
        //std::cout << "Введи " << i << "ое число: ";
        //std::cin  >> num;
        num = i;
        lfu.lookup_update(num, num);
    }
    lfu.lookup_update(2, 2);
    lfu.lookup_update(3, 3);
    std::list<int>::iterator it = lfu.cache.begin();
    
    
    std::cout << "\n";
    for(int i = 10; i > 0; i--) {
        std::cout << i << "ое " << *(lfu.hash[i].iter) << " " << lfu.hash[i].counter << "\n";
    }

    std::cout << "\n";
    for(int i = 0; i < lfu.curr_size; i++) {
        std::cout << *(it) << " ";
        it++;
    }
    std::cout << "\n";
}