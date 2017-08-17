//
// Created by infloop on 8/17/17.
//

#ifndef LOGICTOOLBOX_EXPRESSIONTREE_H
#define LOGICTOOLBOX_EXPRESSIONTREE_H

#include "Token.h"
#include "Expression.h"
#include <stack>

using namespace std;

struct node{
    Token token;
    node* left = nullptr;
    node* right = nullptr;
};

class ExpressionTree {
    node* root;
public:
    ExpressionTree(Expression e);
    ~ExpressionTree();
};



#endif //LOGICTOOLBOX_EXPRESSIONTREE_H
