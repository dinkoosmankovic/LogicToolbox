//
// Created by root on 7/14/17.
//

#include "World.h"

World::World(string _name) : name(_name) {}

World::World(const World &w) : name(w.getName()), variables(w.getVariables()){}

World::~World() {}

string World::getName() const { return  name; }
vector<&Variable> World::getVariables() const { return  variables; }
void World::setName(string _name) { name = _name; }
void World::setVariables(vector<&Variable> _variables) { variables = _variables; }