//
// Created by infloop on 7/16/17.
//

#include "../../include/Expression.h"

Expression::Expression(string str_expr) {
    for(int i = 0; i <= str_expr.size(); i++){
        Token t = Token(str_expr[i]);
        if(t.type != TokenType::EXPR_END) tokens.push_back(t);
    }
    transformToPolishNotation();
}

vector<Token> Expression::getTokens() const { return tokens; }

void Expression::transformToPolishNotation() {
    queue<Token> output;
    stack<Token> token_stack;

    for(auto i = tokens.begin(); i != tokens.end(); ++i){
        switch(i->type){
            case TokenType::LITERAL : output.push(*i);
                break;
            case TokenType::BINARY_OP:
            case TokenType::UNARY_OP:
            case TokenType::OPEN_PARENT:
                token_stack.push(*i);
                break;
            case TokenType::CLOSE_PARENT :
                while(token_stack.top().type != TokenType::OPEN_PARENT){
                    output.push((token_stack.top()));
                    token_stack.pop();
                }
                token_stack.pop();
                if(token_stack.size()>0 && token_stack.top().type == TokenType::UNARY_OP){
                    output.push((token_stack.top()));
                    token_stack.pop();
                }
                break;
            default:
                break;
        }
    }

    while(!token_stack.empty()) {
        output.push((token_stack.top()));
        token_stack.pop();
    }

    vector<Token> new_vec;
    while(!output.empty()){
        new_vec.push_back((output.front()));
        output.pop();
    }

    tokens = new_vec;
}