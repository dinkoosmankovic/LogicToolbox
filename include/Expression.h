//
// Created by infloop on 7/16/17.
//

#ifndef LOGICTOOLBOX_EXPRESSION_H
#define LOGICTOOLBOX_EXPRESSION_H


#include <stddef.h>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include "Token.h"

using namespace std;

class Expression {
    vector<Token> tokens;
public:
    Expression(string str_expr);
    void transformToPolishNotation();
    vector<Token> getTokens() const;
};




#endif //LOGICTOOLBOX_EXPRESSION_H
