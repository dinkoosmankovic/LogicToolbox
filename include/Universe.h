//
// Created by root on 7/14/17.
//

#ifndef LOGICTOOLBOX_UNIVERSE_H
#define LOGICTOOLBOX_UNIVERSE_H


#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "World.h"

using namespace std;

class Universe {
    string name;
    string modalLogic = "K";
    vector<string> variableNames;
    vector<World*> worlds;
public:
    Universe(string _name);

    Universe();

    ~Universe();
    string getName() const;
    void setName(string _name);
    vector<string> getVariableNames() const;
    void setWorlds(vector<World*> _worlds);
    void setVariableNames(vector<string> _variableNames);
    void addVariable(string _name);
    vector<World*> getWorlds() const;
    void addWorld(World world);
    inline void setLogic(string logic){modalLogic = logic;}
    inline string getLogic(){ return modalLogic;}
};


#endif //LOGICTOOLBOX_UNIVERSE_H
