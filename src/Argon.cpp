#include "Argon.h"
using namespace std;

//givie random sign (-1,1)
int rSign(){
    if (rand()%2) return -1;
    else return 1;
}

Argon::Argon(int k){


    n = k;
    N = pow(k,3);
    x = (double *) calloc(N, sizeof(double));
    y = (double *) calloc(N, sizeof(double));
    z = (double *) calloc(N, sizeof(double));
    px = (double *) calloc(N, sizeof(double));
    py = (double *) calloc(N, sizeof(double));
    pz = (double *) calloc(N, sizeof(double));
    fx = (double *) calloc(N, sizeof(double));
    fy = (double *) calloc(N, sizeof(double));
    fz = (double *) calloc(N, sizeof(double));

}

void Argon::makeCristal(double a){
    double h = (n-1)/2; //help variable

    double bx [] = {a, a/2, a/2};
    double by [] = {0, a * sqrt(3)/2, a * sqrt(3)/6};
    double bz [] = {0, 0 , a* sqrt(2.0/3)};

    int i;
    for(int i0 = 0 ; i0 < n ; i0++){
        for(int i1 = 0 ; i1 < n ; i1++){
            for(int i2 = 0 ; i2 < n ; i2++){
                i = i0*pow(n,2) + i1*n + i2; 
                x[i] = bx[0]*(i0 - h) + bx[1]*(i1 - h) + bx[2]*(i2 - h);
                y[i] = by[0]*(i0 - h) + by[1]*(i1 - h) + by[2]*(i2 - h);
                z[i] = bz[0]*(i0 - h) + bz[1]*(i1 - h) + bz[2]*(i2 - h);
    }}}
}

void Argon::makeFile(bool app){
    fstream xyz;
    if (app) xyz = fstream("out.xyz", ios_base::app);
    else xyz = fstream("out.xyz", ofstream::out | ofstream::trunc);
    xyz << N <<endl << " " << endl;
    for (int i = 0 ; i < N ; i++){
        xyz << "Ar " << x[i] << " " << y[i] << " " << z[i] << endl;
    }
    xyz.close();
}

void Argon::makeStartMomentum(double T0){
    srand(time(NULL));
    double E_sum = 0;
    for (int i = 0 ; i < N ; i++){
        px[i] = log((double)rand()/(double)RAND_MAX);
        py[i] = log((double)rand()/(double)RAND_MAX);
        pz[i] = log((double)rand()/(double)RAND_MAX); 
        E_sum += px[i] + py[i] + pz[i];
    }
    double norm_factor = (1.5 * kB * T0 * N)/E_sum;
    double sum_px = 0, sum_py = 0, sum_pz = 0;
    for (int i = 0 ; i < N ; i++){
        sum_px += px[i] = rSign()*sqrt(2 * m * px[i] * norm_factor);
        sum_py += py[i] = rSign()*sqrt(2 * m * py[i] * norm_factor);
        sum_pz += pz[i] = rSign()*sqrt(2 * m * pz[i] * norm_factor);    
    }
    //remove movement of cristal
    for (int i = 0 ; i < N ; i++){
        px[i] =- sum_px/N;
        py[i] =- sum_py/N;
        pz[i] =- sum_pz/N;
    }
}