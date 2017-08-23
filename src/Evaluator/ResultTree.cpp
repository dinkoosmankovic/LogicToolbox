//
// Created by infloop on 8/22/17.
//

#include "ResultTree.h"

ResultTree::ResultTree(Universe universe, Expression e){

    vector<Token> token_vector = e.getTokens();
    stack<node*> stack_of_nodes;

    for(auto i = token_vector.begin(); i != token_vector.end(); i++){
        switch(i->type){
            case TokenType::LITERAL :
            {
                //Check if variable exists in universe
                for(string name : universe.getVariableNames()){
                    if(name == i->value) break;
                    throw logic_error("Variable with given name doesn't exist in this universe!");
                }

                node* newnode = new node;

                //Create resutls for node
                map<World*, bool> newMap;
                for(World* world : universe.getWorlds()){
                    newMap[world] = world->getVariableValueByName(i->value);
                }

                newnode->results = newMap;

                stack_of_nodes.push(newnode);
                break;
            }
            case TokenType::BINARY_OP :
            {

                node* newnode = new node;

                newnode->left = stack_of_nodes.top();
                stack_of_nodes.pop();
                newnode->right = stack_of_nodes.top();
                stack_of_nodes.pop();
                stack_of_nodes.push(newnode);
                break;
            }
            case TokenType::UNARY_OP:
            {

                node* newnode = new node;

                newnode->left = stack_of_nodes.top();
                stack_of_nodes.pop();
                stack_of_nodes.push(newnode);
                break;
            }
            default:
                {break;}
        }
    }

    if(!stack_of_nodes.empty()) root = stack_of_nodes.top();
    else throw logic_error("Stack of nodes is empty!");
}