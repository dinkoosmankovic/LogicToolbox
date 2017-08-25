//
// Created by infloop on 7/16/17.
//

#include "Operators.h"

bool Ness(World* starting_world, map<World*,bool> results){

    queue<World*> Q;
    vector<World*> children;
    map<World*, bool> visited;

    for(auto i: starting_world->getAdjacentList()) Q.push(i);


    while(!Q.empty()){

        World* t = Q.front();
        Q.pop();

        if(visited.find(t) == visited.end()) continue;
        else visited[t] = true;

        if(!results[t]) return false;

        children = t->getAdjacentList();

        for(auto i : children) Q.push(i);
    }

    return true;
}

bool Poss(World* starting_world, map<World*,bool> results){

    queue<World*> Q;
    vector<World*> children;
    map<World*, bool> visited;

    for(auto i: starting_world->getAdjacentList()) Q.push(i);


    while(!Q.empty()){

        World* t = Q.front();
        Q.pop();

        if(visited.find(t) == visited.end()) continue;
        else visited[t] = true;

        if(!results[t]) return true;

        children = t->getAdjacentList();

        for(auto i : children) Q.push(i);
    }

    return false;
}

bool Operator(Token op, bool x, bool y) {
    if (op.type != TokenType::BINARY_OP) throw logic_error("Passed token is not binary operator!");
    if (op.value == "AND") return And(x,y);
    if (op.value == "OR") return Or(x,y);
    if (op.value == "NAND") return Nand(x,y);
    if (op.value == "NOR") return Nor(x,y);
    if (op.value == "XOR") return Xor(x,y);
    if (op.value == "IMPL") return Impl(x,y);
    if (op.value == "EQU") return Equ(x,y);
    throw logic_error("Something unexpected happened!");
}

bool Operator(Token op, World* world, map<World*,bool> resutls){
    if(op.type != TokenType::UNARY_OP || op.value != "NOT")throw logic_error("Passed token is not Ness or Poss!");
    if(op.value == "POSS") return Poss(world,resutls);
    if(op.value == "NESS") return Ness(world, resutls);
    throw logic_error("Something unexpected happened!");
}