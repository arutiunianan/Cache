#ifndef CACHES_H_
#define CACHES_H_

#include <iostream>
#include <list>
#include <fstream>
#include <cassert>
#include <unordered_map>

enum Errors
{
    NO_ERRORS              = 0,
    CACHE_IS_EMPTY         = 1 << 0,
    HASH_HAST_THIS_KEY     = 1 << 1,
    NEGATIVE_CURR_SIZE     = 1 << 2,
    NEGATIVE_MAX_SIZE      = 1 << 3,
    NEGATIVE_HITS_COUNTER  = 1 << 4,
    NEGATIVE_ELEM_COUNTER  = 1 << 5,
    NEGATIVE_INDEX_OF_DATA = 1 << 6,
    NEGATIVE_DATA_SIZE     = 1 << 7,
    DATA_IS_NULLPTR        = 1 << 8
};

template <typename T>
void dump(std::ofstream& log, int errors, std::list<T> cache, size_t curr_size, size_t* number_of_call) {
	    log << "=======================================\n";
        log  << "DUMP CALL #" << (*number_of_call + 1) / 2 << "." 
                             << (*number_of_call + 1) % 2 + 1 << "\n";
        if(errors)
	    {
		    log  << "-------------ERRORS------------\n";
            if(errors & CACHE_IS_EMPTY)         log  << "CACHE IS EMPTY\n";
		    if(errors & HASH_HAST_THIS_KEY)     log  << "HASH HAS'T ELEMENT WITH THIS KEY\n";
		    if(errors & NEGATIVE_CURR_SIZE)     log  << "NEGATIVE CURRENT CACHE SIZE\n";
	        if(errors & NEGATIVE_MAX_SIZE)      log  << "NEGATIVE MAXIMUM CACHE SIZE\n";
	        if(errors & NEGATIVE_HITS_COUNTER)  log  << "NEGATIVE HITS COUNTER \n";
            if(errors & NEGATIVE_ELEM_COUNTER)  log  << "NEGATIVE ELEMENT COUNTER \n";
            if(errors & NEGATIVE_INDEX_OF_DATA) log  << "NEGATIVE INDEX OF DATA\n";
	        if(errors & NEGATIVE_DATA_SIZE)     log  << "NEGATIVE DATA SIZE \n";
            if(errors & NEGATIVE_ELEM_COUNTER)  log  << "DATA IS NULLPTR \n";

		    log  << "----------END_OF_ERRORS--------\n";
	    }
	    else
        {
		    log  << "------------NO_ERRORS----------\n";
            log  << "Current Cache\n";

            std::list<int>::iterator it = cache.begin();
            for(size_t i = 0; i < curr_size; i++) {
                log  << *(it++) << " ";
            }
            log  << "\n";

        }
	    log  << "=======================================\n\n";
	    (*number_of_call)++;
    }

#endif // #define CACHES_H_