//
// Created by infloop on 9/10/17.
//

#ifndef LOGICTOOLBOX_GRAPH_H
#define LOGICTOOLBOX_GRAPH_H

#include "graphviz/gvc.h"
#include "ResultTree.h"
#include "Universe.h"
#include <fstream>

class Graph {
    GVC_t* graphContext = nullptr;
    Agraph_t* agraph = nullptr;
    map<World*,Agnode_t*> nodes;
    vector<Agedge_t*> edges;
    bool created = false;
public:
    inline Graph() {}
    Graph(Universe* universe);
    Graph(ResultTree* resultTree);
    ~Graph();
    void AddResults(ResultTree resultTree);
    inline bool IsCreated() { return created;}
    //void Render();
    bool saveImage(const char* FILE_PATH = "");
};




#endif //LOGICTOOLBOX_GRAPH_H
