#include <stdio.h>
#include "square.h"
#include "squareio.h"
#include "solver.h"
#include "unittest.h"

#define DEBUG_MODE_
int main()
{
    #ifdef DEBUG_MODE_

    test_solveSquare();

    #else

    printf("# Square Solver\n");

    Square square = {};

    scanSquare(&square);

    solveSquare(&square);

    printSquare(&square);

    #endif

    return 0;
}
