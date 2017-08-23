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