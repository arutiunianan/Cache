#ifndef CACHES_H_
#define CACHES_H_

#include <iostream>
#include <list>
#include <fstream>
#include <assert.h>
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
void dump(FILE* log, int errors, std::list<T> cache, size_t curr_size, size_t* number_of_call) {
	    fprintf(log, "=======================================\n");
        fprintf(log, "DUMP CALL #%d.%d\n", (*number_of_call + 1) / 2 , 
                                           (*number_of_call + 1) % 2 + 1);
        if(errors)
	    {
		    fprintf(log, "-------------ERRORS------------\n");
            if(errors & CACHE_IS_EMPTY)         fprintf(log, "CACHE IS EMPTY\n");
		    if(errors & HASH_HAST_THIS_KEY)     fprintf(log, "HASH HAS'T ELEMENT WITH THIS KEY\n");
		    if(errors & NEGATIVE_CURR_SIZE)     fprintf(log, "NEGATIVE CURRENT CACHE SIZE\n");
	        if(errors & NEGATIVE_MAX_SIZE)      fprintf(log, "NEGATIVE MAXIMUM CACHE SIZE\n");
	        if(errors & NEGATIVE_HITS_COUNTER)  fprintf(log, "NEGATIVE HITS COUNTER \n");
            if(errors & NEGATIVE_ELEM_COUNTER)  fprintf(log, "NEGATIVE ELEMENT COUNTER \n");
            if(errors & NEGATIVE_INDEX_OF_DATA) fprintf(log, "NEGATIVE INDEX OF DATA\n");
	        if(errors & NEGATIVE_DATA_SIZE)     fprintf(log, "NEGATIVE DATA SIZE \n");
            if(errors & NEGATIVE_ELEM_COUNTER)  fprintf(log, "DATA IS NULLPTR \n");

		    fprintf(log, "----------END_OF_ERRORS--------\n");
	    }
	    else
        {
		    fprintf(log, "------------NO_ERRORS----------\n");
            fprintf(log, "Current Cache\n");

            std::list<int>::iterator it = cache.begin();
            for(size_t i = 0; i < curr_size; i++) {
                fprintf(log, "%d ", *(it++));
            }
            fprintf(log, "\n");

        }
	    fprintf(log, "=======================================\n\n");
	    (*number_of_call)++;
    }

#endif // #define CACHES_H_