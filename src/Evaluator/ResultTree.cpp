//
// Created by infloop on 8/22/17.
//

#include <search.h>
#include "../../include/ResultTree.h"

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
                    else {
                        newMap[world] = Operator(world, newnode->left->results, *i, universe->getLogic());
                    }

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

    created = true;
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
}

ResultTree::ResultTree() {
    created = false;
}

void ResultTree::Visualise(string world, const char* FILE_PATH) {

    World* selected_world = nullptr;

    for(auto i : root->results){
        if(i.first->getName() == world) {
            selected_world = i.first;
        }
    }

    if(selected_world == nullptr) throw logic_error("World with that name does not exist!");

    GVC_t* gvc = gvContext();
    Agraph_t* agraph = agopen("Graph", Agdirected, 0);
    agattr(agraph,AGNODE,"color","black");
    agattr(agraph, AGNODE, "label", "LABEL");
    int counter = 0;
    Traverse_V(selected_world,agraph, nullptr,root,&counter);

    string gname;
    if(strcmp(FILE_PATH,"") == 0)
    gname ="-oRESULT_"+selected_world->getName()+".png";
    else gname = FILE_PATH;

    char* args[] = {const_cast<char*>("dot"), const_cast<char*>("-Tpng"),
                    const_cast<char*>(gname.c_str())};

    cout << args << endl << gname;

    gvParseArgs (gvc, sizeof(args)/sizeof(char*), args);

    gvLayoutJobs(gvc, agraph);
    gvRenderJobs(gvc, agraph);

}

void ResultTree::Traverse_V(World* world, Agraph_t *agraph, Agnode_t *prev, node *curr, int* counter) {

    if(curr != nullptr){
        Agnode_t* new_node = agnode(agraph, const_cast<char*>(to_string(*counter).c_str()), 1);
        agset(new_node,"label", const_cast<char*>(curr->value.c_str()));
        char* color = (curr->results[world]? const_cast<char*>("green"): const_cast<char*>("red"));
        agset(new_node,"color",color);
        if(prev != nullptr) agedge(agraph,prev,new_node,"",1);
        (*counter)++;
        Traverse_V(world,agraph,new_node,curr->left,counter);
        (*counter)++;
        Traverse_V(world,agraph,new_node,curr->right,counter);
    }

}
