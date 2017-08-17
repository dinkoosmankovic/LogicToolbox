//
// Created by infloop on 7/16/17.
//

#ifndef LOGICTOOLBOX_OPERATORS_H
#define LOGICTOOLBOX_OPERATORS_H


bool And(const bool x, const bool y){
    return x&&y;
}

bool Or(const bool x, const bool y){
    return x||y;
}

bool Not(const bool y){
    return  !y;
}

bool Xor(const bool x, const bool y){
    return (x||y) && !(x||y);
}

bool Nand(const bool x, const bool y){
    return !(x&&y);
}

bool Nor(const bool x, const bool y){
    return !(x||y);
}

bool Impl(const bool x, const bool y){
    return !x || y;
}

bool Equ(const bool x, const bool y){
    return !(Xor(x,y));
}

#endif //LOGICTOOLBOX_OPERATORS_H
