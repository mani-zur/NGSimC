#include<iostream>
#include<cmath>
#include<fstream>
#include<random>
#include<ctime>
#include"Addons.h"

class Argon{
    const double kB = 8.31E-3; 
    const double m = 39.59;

    Config cfg;

    double * x, * y , * z;
    double * px,* py, *pz;
    double * fx,* fy, *fz;

    int n; //side length
    int N; //count of particles
    
public:
    Argon(char *);
    void makeCristal();
    void makeFile(bool);
    void makeStartMomentum();
    void makeFoces();
    void Simulate();
};