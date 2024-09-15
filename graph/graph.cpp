#include "graph.h"

Graph::Graph() {
    lfu.open("graph/lfu_hits_array.txt");
    pca.open("graph/pca_hits_array.txt");
}

void Graph::add_hits(size_t lfu_hits, size_t pca_hits) {
    assert(lfu || pca);

    lfu << lfu_hits << " ";
    pca << pca_hits << " ";
}

void Graph::print_graph() {
    lfu.close();
    pca.close();

    system("python3.8 graph/graph_maker.py graph/lfu_hits_array.txt graph/pca_hits_array.txt");
}

