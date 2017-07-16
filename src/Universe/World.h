//
// Created by root on 7/14/17.
//

#ifndef LOGICTOOLBOX_WORLD_H
#define LOGICTOOLBOX_WORLD_H

#include <string>
#include <vector>
#include <stdexcept>
#include "Variable.h"

using namespace std;

class World {
    string name;
    vector<Variable> variables = nullptr;
    vector<&World> adjacentList = nullptr;
public:
    World(string _name);
    World(const World &w);
    ~World();
    string getName() const;
    vector<&Varible> getVariables() const;
    void setName(string _name);
    void setVariables(vector<Variable> _variables);
    void setAdjacentList(vector<&World> _adjacentList);
    vector<&World> getAdjacentList() const;
    void addAdjacent(const World& adj);
    bool removeAdjacentByName(string adjName);
};


#endif //LOGICTOOLBOX_WORLD_H
