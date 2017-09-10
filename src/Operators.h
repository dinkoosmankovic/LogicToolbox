//
// Created by infloop on 7/16/17.
//

#ifndef LOGICTOOLBOX_OPERATORS_H
#define LOGICTOOLBOX_OPERATORS_H

#include "Universe/World.h"
#include <utility>
#include <vector>
#include <map>
#include <queue>
#include <stdexcept>
#include "Parser/Token.h"


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

bool Ness(World* starting_world, map<World*,bool> results);
bool Poss(World* starting_world, map<World*,bool> results);

bool Operator(World* world, map<World*,bool> results,Token op);
bool Operator(Token op, bool x, bool y);


#endif //LOGICTOOLBOX_OPERATORS_H
