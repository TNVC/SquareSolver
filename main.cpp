#include <stdio.h>
#include "square.h"
#include "squareio.h"
#include "solver.h"
#include "unittest.h"

int main()
{
    //test_solveSquare();

    //return 0;


    //Square square = {};

    //for (square.a = -2; square.a <= 2; ++square.a)
    //    for (square.b = -2; square.b <= 2; ++square.b)
    //        for (square.c = -2; square.c <= 2; ++square.c)
    //        {
    //            showExpression(&square);
    //            putchar('\n');
    //        }

    //return 0;


    printf("# Square Solver\n");

    Square square = {};

    scanSquare(&square);

    solveSquare(&square);

    printSquare(&square);

    return 0;
}
