//
// Created by infloop on 8/22/17.
//

#include <search.h>
#include "ResultTree.h"

ResultTree::ResultTree(Universe *universe, Expression e){

    vector<Token> token_vector = e.getTokens();
    stack<node*> stack_of_nodes;

    for(auto i = token_vector.begin(); i != token_vector.end(); i++){
        switch(i->type){
            case TokenType::LITERAL :
            {
                //Check if variable exists in universe
                bool exists = false;
                for(string name : universe->getVariableNames()){
                    if(name == i->value) {exists = true; break;}
                }

                if(!exists) throw logic_error("Variable with given name doesn't exist in this universe!");

                node* newnode = new node;

                //Create resutls for node
                map<World*, bool> newMap ;
                for(World* world : universe->getWorlds()){
                    newMap[world] = world->getVariableValueByName(i->value);
                }

                newnode->results = newMap;
                newnode->value = i->value;

                stack_of_nodes.push(newnode);
                break;
            }
            case TokenType::BINARY_OP :
            {

                node* newnode = new node;

                newnode->right = stack_of_nodes.top();
                stack_of_nodes.pop();
                newnode->left = stack_of_nodes.top();
                stack_of_nodes.pop();

                map<World*,bool> newMap;
                for(World* world : universe->getWorlds()){
                    bool x = newnode->left->results[world];
                    bool y = newnode->right->results[world];
                    newMap[world] = Operator(*i,x,y);
                }

                newnode->results = newMap;
                newnode->value = i->value;

                stack_of_nodes.push(newnode);
                break;
            }
            case TokenType::UNARY_OP:
            {

                node* newnode = new node;

                newnode->left = stack_of_nodes.top();
                stack_of_nodes.pop();

                map<World*,bool> newMap;
                for(World* world: universe->getWorlds()){

                    if(i->value == "NOT") newMap[world] = Not(newnode->left->results[world]);
                    else newMap[world] = Operator(world, newnode->left->results,*i);

                }

                newnode->results = newMap;
                newnode->value = i->value;

                stack_of_nodes.push(newnode);
                break;
            }
            default:
                {break;}
        }
    }

    if(!stack_of_nodes.empty()) {root = stack_of_nodes.top(); stack_of_nodes.pop();}
    else throw logic_error("Stack of nodes is empty!");
}

/*ResultTree::~ResultTree(){
    DeleteNode(root);
}*/

void ResultTree::DeleteNode(node* leaf){
    if(leaf != nullptr){
        DeleteNode(leaf->left);
        DeleteNode(leaf->right);
        delete leaf;
    }
}

string ResultTree::toString() {
    string output = "";
    for(auto i = root->results.begin(); i != root->results.end(); i++ ){
        output += i->first->getName() + ": " + (i->second?"TRUE":"FALSE") + "\n";
    }
    return output;
}

void ResultTree::test(){
    cout << root->results.begin()->first->getName();
};