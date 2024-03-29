#ifndef _addons_h_
#define _addons_h_

#include <random>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string.h>

typedef struct measure{
    double T , p, Terr, perr;
}measure;

int rSign();

//return mean simulation parameters
measure getMeanParams();

class Config {
    std::string param [20];
    double value [20];
    int nParams = 0;
public:
    Config(){};
    Config(char *);
    double GetValue(char *);
};

#endif