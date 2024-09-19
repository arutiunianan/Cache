#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <fstream>
#include <cassert>

class Graph {
public:
    std::ofstream lfu;
    std::ofstream pca;

    Graph();
    void add_hits(size_t lfu_hits, size_t pca_hits);
    void print_graph();
};

#endif // #define GRAPH_H_