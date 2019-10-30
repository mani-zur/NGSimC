#include <random>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string.h>

int rSign();
void readConfig( char * );

class Config {
    std::string param [20];
    double value [20];
    int nParams = 0;
public:
    Config(){};
    Config(char *);
    double GetValue(char *);
};