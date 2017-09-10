//
// Created by infloop on 8/22/17.
//

#ifndef LOGICTOOLBOX_RESULTTREE_H
#define LOGICTOOLBOX_RESULTTREE_H

#include "../Parser/Expression.h"
#include "../Universe/Universe.h"
#include "../Operators.h"
#include <stack>
#include <iostream>

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
public:
    ResultTree(Universe *universe, Expression e);
    //~ResultTree();
    string toString();
    void test();
};




#endif //LOGICTOOLBOX_RESULTTREE_H
