//
// Created by infloop on 8/17/17.
//

#include "ExpressionTree.h"

ExpressionTree::ExpressionTree(Expression e) {

    vector<Token> token_vector = e.getTokens();
    stack<node*> stack_of_nodes;

    for(auto i = token_vector.begin(); i != token_vector.end(); i++){
        switch(i->type){
            case TokenType::LITERAL :
                node* newnode = new node;
                newnode->token = *i;
                stack_of_nodes.push(newnode);
                break;
            case TokenType::BINARY_OP:
                newnode = new node;
                newnode->token = *i;
                newnode->left = stack_of_nodes.top();
                stack_of_nodes.pop();
                newnode->right = stack_of_nodes.top();
                stack_of_nodes.pop();
                stack_of_nodes.push(newnode);
                break;
            case TokenType::UNARY_OP:
                newnode = new node;
                newnode->token = *i;
                newnode->left = stack_of_nodes.top();
                stack_of_nodes.pop();
                stack_of_nodes.push(newnode);
                break;
            default:
                break;
        }
    }

    if(!stack_of_nodes.empty()) root = stack_of_nodes.top();
    else throw logic_error("Stack of nodes is empty!");
}