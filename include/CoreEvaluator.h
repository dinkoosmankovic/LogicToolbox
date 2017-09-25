//
// Created by infloop on 8/17/17.
//

#ifndef LOGICTOOLBOX_COREEVALUATOR_H
#define LOGICTOOLBOX_COREEVALUATOR_H

#include "Expression.h"
#include "Universe.h"
#include "rapidjson/document.h"
#include "ResultTree.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <iostream>
#include "Graph.h"

using namespace rapidjson;

class CoreEvaluator {
    Universe universe;
    Graph graph;
    ResultTree resultTree;
public:
    CoreEvaluator(const char* PATH = "UniverseConfig.json");
    //~CoreEvaluator();
    ResultTree returnResultTree(string expression_string);
    void ToString();
    void RenderUniverse(string PATH = "");
    void CreateGraph();
    bool CreateResultTreeGraph(string world, const char* DOT_FILE= "result_tree.dot");
};


#endif //LOGICTOOLBOX_COREEVALUATOR_H
