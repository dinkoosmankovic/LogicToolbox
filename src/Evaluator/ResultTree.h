//
// Created by infloop on 8/22/17.
//

#ifndef LOGICTOOLBOX_RESULTTREE_H
#define LOGICTOOLBOX_RESULTTREE_H

#include "../Parser/Expression.h"
#include "../Universe/Universe.h"
#include <stack>

using namespace std;

struct node{
    map<World*,bool> results;
    node* left = nullptr;
    node* right = nullptr;
};

class ResultTree {
    node* root;
public:
    ResultTree(Universe universe, Expression e);
    ~ResultTree();
};


#endif //LOGICTOOLBOX_RESULTTREE_H
