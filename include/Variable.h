#ifndef LOGICTOOLBOX_VARIABLE_H
#define LOGICTOOLBOX_VARIABLE_H

#include <string>

using namespace std;

class Variable {
    string name;
    bool value;
public:
    Variable(){};
    Variable(string _name);
    Variable(const Variable &v);
    Variable &operator=(const Variable &v);
    string getName() const;
    void setName(string _name);
    bool getValue() const;
    void setValue(bool _value);
};
#endif //LOGICTOOLBOX_VARIABLE_H
