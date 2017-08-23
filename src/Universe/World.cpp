//
// Created by root on 7/14/17.
//

#include "World.h"

//Constructors and destructor
World::World(string _name) : name(_name) {}
World::World(const World &w) : name(w.getName()), variables(w.getVariables()), adjacentList(w.getAdjacentList()) {}
World::~World() {}

//Getters and setters
string World::getName() const { return  name; }
vector<Variable> World::getVariables() const { return  variables; }
void World::setName(string _name) { name = _name; }
void World::setVariables(vector<Variable> _variables) { variables = _variables; }
vector<World*> World::getAdjacentList() const { return adjacentList; }
void World::setAdjacentList(vector<World*> _adjacentList) { adjacentList = _adjacentList; }

//Adjacent operations
void World::addAdjacent(World adj) {
    for(auto i : adjacentList){
        if(i->name == adj.getName()) throw logic_error("World is already adjacent!");
    }
    adjacentList.push_back(&adj);
}

bool World::removeAdjacentByName(string adjName) {
    //TO BE DONE
}

bool World::getVariableValueByName(string name) {

    for(auto variable : variables){

        if(variable.getName() == name) return variable.getValue();

    }
}