//
// Created by infloop on 8/22/17.
//

#ifndef LOGICTOOLBOX_RESULTTREE_H
#define LOGICTOOLBOX_RESULTTREE_H

#include "Expression.h"
#include "Universe.h"
#include "Operators.h"
#include <stack>
#include <iostream>
#include "graphviz/gvc.h"

using namespace std;

struct node{
    string value;
    map<World*,bool> results;
    node* left = nullptr;
    node* right = nullptr;
    /*~node(){
        delete left;
        delete right;
    }*/
};

class ResultTree {
    node* root = nullptr;
    void DeleteNode(node* leaf);
    bool created = false;
    void Traverse_V(World* world, Agraph_t* agraph, Agnode_t* prev, node* curr, int* counter);
public:
    ResultTree();
    ResultTree(Universe *universe, Expression e);
    inline map<World*, bool> getFinalResult() { return root->results;};
    string toString();
    void test();
    inline node* getRoot(){ return  root;};
    void Visualise(string world);
};




#endif //LOGICTOOLBOX_RESULTTREE_H
