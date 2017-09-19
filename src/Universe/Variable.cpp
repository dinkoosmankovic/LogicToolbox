#include "../../include/Variable.h"
#include <string>

using namespace std;

Variable::Variable(string _name) : name(_name) {}

Variable::Variable(const Variable &v) : name(v.getName()), value(v.getValue()){}

Variable& Variable::operator=(const Variable &v){
    name = v.getName();
    value = v.getValue();
    return *this;
}

string Variable::getName() const { return name; }
bool Variable::getValue() const { return value; }
void Variable::setName(string _name) { name = _name; }
void Variable::setValue(bool _value) { value = _value; }
