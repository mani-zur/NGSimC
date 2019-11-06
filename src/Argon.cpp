#include "Argon.h"
using namespace std;


Argon::Argon(char * cFile){
    cfg = Config(cFile);

    n = cfg.GetValue((char *)"n");
    N = pow(n,3);
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

void Argon::makeCristal(){
    double a = cfg.GetValue((char*)"a");
    double L = cfg.GetValue((char*)"L");
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
    double r = sqrt(x[i]*x[i]+y[i]*y[i]+z[i]*z[i]); 
    if (r > L) cerr << "The cristal structure is larger than vessel!" <<endl;
}

void Argon::makeFile(bool app){
    fstream xyz;
    if (app) xyz = fstream("out/out.xyz", ios_base::app);
    else xyz = fstream("out/out.xyz", ofstream::out | ofstream::trunc);
    xyz << N <<endl << " " << endl;
    for (int i = 0 ; i < N ; i++){
        xyz << "Ar " << x[i] << " " << y[i] << " " << z[i] << endl;
    }
    xyz.close();
}

void Argon::makeStartMomentum(){
    double T0 = cfg.GetValue((char *)"T0");
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
        px[i] -= sum_px/N;
        py[i] -= sum_py/N;
        pz[i] -= sum_pz/N;
    }
}

void Argon::makeFoces(){
    for (int i = 0 ; i < N ; i++) fx[i] = fy[i] = fz[i] = 0; //delete old foces
    double e = 12*cfg.GetValue((char *)"e");
    double R = cfg.GetValue((char *)"R");
    double L = cfg.GetValue((char *)"L");
    double f = cfg.GetValue((char *)"f");
    double rij, rij_x, rij_y, rij_z, h;
    for (int i = 0 ; i < N ; i++){
        for(int j = i+1 ; j < N ; j++){
            rij_x = x[i]-x[j];
            rij_y = y[i]-y[j];
            rij_z = z[i]-z[j];
            rij = rij_x * rij_x + rij_y * rij_y + rij_z * rij_z;
            h = (R*R*R*R*R*R)/(rij*rij*rij);
            h = e*h*(h-1)/(rij);
            fx[i] += h*rij_x;
            fy[i] += h*rij_y;
            fz[i] += h*rij_z;
            fx[j] -= h*rij_x;
            fy[j] -= h*rij_y;
            fz[j] -= h*rij_z;
        }
        //virtual vessel
        double r = sqrt(x[i]*x[i]+y[i]*y[i]+z[i]*z[i]); 
        if (r > L){
            fx[i] += f*(L-r)*x[i]/r;
            fy[i] += f*(L-r)*y[i]/r;
            fz[i] += f*(L-r)*z[i]/r;
        }
    }
}

void Argon::Simulate(){
    fstream tFile("out/data.csv", ofstream::out | ofstream::trunc);
    int S_o = cfg.GetValue((char *)"S_o");
    int S_d = cfg.GetValue((char *)"S_d");
    int S_xyz = cfg.GetValue((char *)"S_xyz");
    int S_out = cfg.GetValue((char *)"S_out");
    double tau = cfg.GetValue((char *)"tau");
    double m = cfg.GetValue((char *)"m");
    for(int i = 0 ; i < S_o + S_d ; i++){
        for (int i = 0; i < N ; i++){
            px[i] += 0.5*fx[i]*tau;
            py[i] += 0.5*fy[i]*tau;
            pz[i] += 0.5*fz[i]*tau;
            x[i]  += px[i]*tau/m;
            y[i]  += py[i]*tau/m;
            z[i]  += pz[i]*tau/m;   
        }
        makeFoces();
        for (int i = 0; i < N ; i++){
            px[i] += 0.5*fx[i]*tau;
            py[i] += 0.5*fy[i]*tau;
            pz[i] += 0.5*fz[i]*tau;
        }
        if ( i >= S_o && !(i % S_xyz)) makeFile(true);  //save positions to file
        if ( !(i % S_out)) tFile <<getTemperature()<<","<<getPressure()<<endl; //save param to file
    }
    tFile.close();
}

double Argon::getPressure(){
    double L = cfg.GetValue((char *)"L");
    double f = cfg.GetValue((char *)"f");
    double p = 0;
    for (int i = 0 ; i < N ; i++){
        double r = sqrt(x[i]*x[i]+y[i]*y[i]+z[i]*z[i]); 
        if (r > L) p += sqrt(f*(r-L)/r*(x[i]*x[i]+ y[i]*y[i] + z[i]*z[i]));
    }
    p = p / (4*3.1415*L*L);
    return p;
}

double Argon::getTemperature(){
    double m = cfg.GetValue((char *)"m");
    double T = 0;
    for (int i = 0 ; i < N ; i++){
        T += px[i]*px[i]+py[i]*py[i]+pz[i]*pz[i];
    }
    T = T/(3*N*kB*m);
    return T;
}