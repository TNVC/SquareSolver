#include <stdio.h>
#include "square.h"
#include "squareio.h"
#include "solver.h"
#include "unittest.h"

#define DEBUG_MODE
int main()
{
    #ifdef DEBUG_MODE

    test_solveSquare();

    #endif

    #ifndef DEBUG_MODE

    printf("# Square Solver\n");

    Square square = {};

    scanSquare(&square);

    solveSquare(&square);

    printSquare(&square);

    #endif

    return 0;
}
