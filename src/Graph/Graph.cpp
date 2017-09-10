//
// Created by infloop on 9/10/17.
//

#include "Graph.h"

Graph::Graph(Universe universe) {

    if(graphContext == nullptr) graphContext = gvContext();

    agraph = agopen("Graph", Agdirected, 0);
    for(auto i : universe.getWorlds()){
        char* name = (char *) i->getName().c_str();
        nodes[i] = agnode(agraph,name,0);
    }

    for(auto i: universe.getWorlds()){
        for(auto j: i->getAdjacentList())
            edges.push_back(agedge(agraph,nodes[i],nodes[j],"",0));
    }

    gvLayout(graphContext, agraph, "dot");
    gvRender(gvContext(), agraph, "dot", stdout);

}

Graph::~Graph() {
    gvFreeLayout(graphContext,agraph);
    agclose(agraph);
}