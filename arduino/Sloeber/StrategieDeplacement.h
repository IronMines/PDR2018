/*
 * StrategieDeplacement.h
 *
 *  Created on: 14 mai 2018
 *      Author: william
 */

#ifndef STRATEGIEDEPLACEMENT_H_
#define STRATEGIEDEPLACEMENT_H_

#include "string.h"


class StrategieDeplacement {
    public:
        StrategieDeplacement();
        
        char* getAction();
        void nextAction();
        
    private:
        unsigned char index;
        
};

#endif /* STRATEGIEDEPLACEMENT_H_ */
