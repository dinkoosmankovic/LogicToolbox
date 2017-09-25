//
// Created by infloop on 7/16/17.
//

#ifndef LOGICTOOLBOX_OPERATORS_H
#define LOGICTOOLBOX_OPERATORS_H

#include "World.h"
#include "Variable.h"
#include <utility>
#include <vector>
#include <map>
#include <queue>
#include <stdexcept>
#include "Token.h"

//Bool operators

inline bool And(const bool x, const bool y){
    return x&&y;
}

inline bool Or(const bool x, const bool y){
    return x||y;
}

inline bool Not(const bool y){
    return  !y;
}

inline bool Xor(const bool x, const bool y){
    return (x||y) && !(x||y);
}

inline bool Nand(const bool x, const bool y){
    return !(x&&y);
}

inline bool Nor(const bool x, const bool y){
    return !(x||y);
}

inline bool Impl(const bool x, const bool y){
    return !x || y;
}

inline bool Equ(const bool x, const bool y){
    return !(Xor(x,y));
}

bool Ness(World* starting_world, map<World*,bool> results, string m_logic = "K");
bool Poss(World* starting_world, map<World*,bool> results, string m_logic = "K");

bool Operator(World* world, map<World*,bool> results,Token op,string m_logic = "K");
bool Operator(Token op, bool x, bool y);

//Variable operators
inline bool And(const Variable& x, const Variable& y){
    return x.getValue()&&y.getValue();
}

inline bool Or(const Variable& x, const Variable& y){
    return x.getValue()||y.getValue();
}

inline bool Not(const Variable& y){
    return  !y.getValue();
}

inline bool Xor(const Variable& x, const Variable& y){
    return (x.getValue()||y.getValue()) && !(x.getValue()||y.getValue());
}

inline bool Nand(const Variable& x, const Variable& y){
    return !(x.getValue()&&y.getValue());
}

inline bool Nor(const Variable& x, const Variable& y){
    return !(x.getValue()||y.getValue());
}

inline bool Impl(const Variable& x, const Variable& y){
    return !x.getValue() || y.getValue();
}

inline bool Equ(const Variable& x, const Variable& y){
    return !(Xor(x.getValue(),y.getValue()));
}

#endif //LOGICTOOLBOX_OPERATORS_H
