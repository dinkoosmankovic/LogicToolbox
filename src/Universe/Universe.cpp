//
// Created by root on 7/14/17.
//

#include "Universe.h"

//Constructors and destructor
Universe::Universe(string _name) : name(_name){
    variableNames = vector<string>();
    worlds = vector<World*>();
}
Universe::~Universe(){
    for(auto i: worlds) free(i);
}

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

vector<World*> Universe::getWorlds() const { return worlds; }

void Universe::addWorld(World world) {
    if(worlds.size() >= pow(2,variableNames.size())) throw domain_error("There can not be more worlds!");
    else worlds.push_back(&world);
}

void Universe::setVariableNames(vector<string> _variableNames) {
    variableNames = _variableNames;
}

void Universe::setWorlds(vector<World *> _worlds) {
    worlds = _worlds;
}

Universe::Universe() {}
