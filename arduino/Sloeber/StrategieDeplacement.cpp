/*
 * StrategieDeplacement.cpp
 *
 *  Created on: 14 mai 2018
 *      Author: william
 */

#include "StrategieDeplacement.h"

StrategieDeplacement::StrategieDeplacement() : index(0){
    
}

char* StrategieDeplacement::getAction()
{
    switch(this->index)
    {
    case 0:
        return "DELA;500";
    case 1:
        return "MVTN;3";
    case 2:
        return "DELA;800";
    case 3:
        return "MVTC;4000";
    case 4:
        return "DELA;500";
    case 5:
        return "ROTA;-180";
    case 6:
        return "DELA;900";
    case 7:
        return "ROTA;360";
    case 8:
        return "DELA;900";
    case 9:
        return "ROTA;180";
    case 10:
        return "CHAN;STP";
        
    default:
        return "";
    }
}

void StrategieDeplacement::nextAction()
{
    index ++;
}
