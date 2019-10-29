#include "Argon.h"
using namespace std;

Argon::Argon(int k){
    int N = k^3;
    x = (double *) calloc(N, sizeof(double));
    y = (double *) calloc(N, sizeof(double));
    z = (double *) calloc(N, sizeof(double));
}

void Argon::makeCristal(double a){
    double h = (N-1)/2; //help variable
    double b [3][3] = {{a,0,0},{a/2,1,1},{1,1,1}}; //shemem of particle positions

}




void lol(void){
    cout << "lol" << endl;
}