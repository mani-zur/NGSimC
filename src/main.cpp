#include <iostream>
#include <time.h>
#include "Argon.h"

using namespace std;

int main() {
    clock_t start = clock();    //start time counting

    int u = 5;
    int a = 1;

    Argon argon(u);
    argon.makeCristal(a);
    printf("Time taken: %.2fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);    //calculate procesinng time

}