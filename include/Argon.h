#include<iostream>

class Argon{
    double * x, * y , * z;
    double * px,* py, *pz;
    double * fx,* fy, *fz;

    int N; //count of particles
    
public:
    Argon(int);
    void makeCristal(double);
};