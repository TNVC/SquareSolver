#include <stdio.h>
#include "square.h"
#include "squareio.h"
#include "solver.h"
#include "unittest.h"

int main()
{
    #ifdef DEBUG_MODE_

    test_solveSquare();

    #else

    printf("# Square Solver\n");

    Square square = {};

    if (scanSquare(&square))
    {
        solveSquare(&square);

        printSquare(&square);
    }

    puts("# Goodbye");

    #endif

    return 0;
}
