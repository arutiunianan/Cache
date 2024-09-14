#ifndef CACHES_H_
#define CACHES_H_

#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>

enum Errors
{
    NO_ERRORS               = 0,
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

#endif // #define CACHES_H_