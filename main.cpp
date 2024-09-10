#include "inc/caches.h"

int MAX_SIZE = 10;

int main() {
    LFU_cache_t<int> lfu(MAX_SIZE);
    int num;
    
    for(int i = 0; i < 11; i++) {
        //std::cout << "Введи " << i << "ое число: ";
        //std::cin  >> num;
        num = i;
        lfu.lookup_update(num,num);
    }
    //std::list<int>::iterator it = lfu.cache.begin();
    
    /*std::cout << "\n";
    for(int i = 0; i < lfu.curr_size; i++) {
        std::cout << i << "ое " << *(it) << " " << lfu.curr_size << "\n";
        it++;
    }*/
    /*std::cout << "\n";
    for(int i = 10; i > -1; i--) {
        std::cout << i << "ое " << *(lfu.hash[i].iter) << " " << lfu.curr_size << "\n";
        it++;
    }*/
    /*if(lfu.cache.begin() == lfu.hash[10].iter) {
        std::cout << "дааа";
    }*/
    
}