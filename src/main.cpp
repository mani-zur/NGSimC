#include <iostream>
#include <time.h>
#include "Argon.h"

using namespace std;

int main(int argc, char ** argv) {
    clock_t start = clock();    //start time counting

    if (argc > 1) {
        Argon argon(argv[1]);
        argon.makeCristal();
        argon.makeFile(false);
        argon.makeStartMomentum();
        argon.Simulate();
    }
    else cerr << "Wrong count of aguments"<< endl;

    printf("Total simulation time: %.2fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);    //calculate procesinng time
    return 0;

}