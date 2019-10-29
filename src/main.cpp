#include <iostream>
#include <time.h>
#include "Argon.h"

using namespace std;

int main(int argc, char ** argv) {
    clock_t start = clock();    //start time counting
    int u = 3;
    int a = 1;

    Argon argon(u);
    argon.makeCristal(a);
    argon.makeFile(false);
    argon.makeStartMomentum(1000);
    printf("Time taken: %.2fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);    //calculate procesinng time

}