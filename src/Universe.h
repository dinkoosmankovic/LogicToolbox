//
// Created by root on 7/14/17.
//

#ifndef LOGICTOOLBOX_UNIVERSE_H
#define LOGICTOOLBOX_UNIVERSE_H

#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

class Universe {
    string name;
    vector<string> variableNames = nullptr;
    vector<&World> worlds = nullptr;
public:
    Universe(string _name);
    ~Universe();
    string getName() const;
    void setName(string _name);
    vector<string> getVariableNames() const;
    void addVariable(string _name);
    vector<&World> getWorlds() const;
    void addWorld(const World& world);
};


#endif //LOGICTOOLBOX_UNIVERSE_H
