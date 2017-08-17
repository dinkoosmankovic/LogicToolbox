//
// Created by root on 7/14/17.
//

#include "Universe.h"
//Constructors and destructor
Universe::Universe(string _name) : name(_name){
    variableNames = new vector<string>();
    worlds = new vector<&Worlds>();
}
Universe::~Universe(){}

//Getters setters and others
string Universe::getName() const { return name; }

void Universe::setName(string _name) { name = _name; }

vector<string> Universe::getVariableNames() const { return variableNames;}

void Universe::addVariable(string _name) {
    for(auto i = variableNames.begin(); i != variableNames.end(); i++){
        if(*i == _name) throw logic_error("Variable with same name already exists!");
    }
    variableNames.push_back(_name);
}

vector<&World> Universe::getWorlds() const { return worlds; }

void Universe::addWorld(const World &world) {
    if(world.size() >= pow(2,variableNames.size())) throw domain_error("There can not be more worlds!");
    else worlds.push_back(world);
}
