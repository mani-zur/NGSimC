#include<iostream>
#include<cmath>
#include<fstream>
#include<random>
#include<ctime>

class Argon{
    const double kB = 8.31E-3; 
    const double m = 39.59;

    double * x, * y , * z;
    double * px,* py, *pz;
    double * fx,* fy, *fz;

    int n; //side length
    int N; //count of particles
    
public:
    Argon(int);
    void makeCristal(double);
    void makeFile(bool);
    void makeStartMomentum(double);
    void makeFoces();
};