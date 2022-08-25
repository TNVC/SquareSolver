#include <stdio.h>
#include <cmath>
#include "square.h"
#include "solver.h"
#include "isequals.h"
#include "unittest.h"
#include "newassert.h"


static int  test(int   realRoots, double   realX1, double   realX2,
                 int expectRoots, double expectX1, double expectX2);

/// Array of Square for "test_solveSquare()"
static const Square TESTS[] = {
    {0,  0,  0, INF_ROOTS,    0,    0},
    {1,  0,  0,         2,    0,    0},
    {0,  1,  0,         1,    0,    0},
    {0,  0,  1,         0,    0,    0},
    {0,  1,  1,         1,   -1,   -1},
    {1,  0,  1,         0,    0,    0},
    {1,  0, -1,         2,   -1,    1},
    {1,  1,  0,         2,   -1,    0},
    {1,  2,  1,         2,   -1,   -1},
    {1,  4,  4,         2,   -2,   -2},
    {1,  6,  9,         2,   -3,   -3},
    {1, -2,  1,         2,    1,    1},
    {1, -4,  4,         2,    2,    2},
    {1, -6,  9,         2,    3,    3},
    {0,  2,  1,         1, -0.5, -0.5},
    {0, -1,  5,         1,    5,    5},
    {0,  4, -9,         1, 2.25, 2.25},
    {4,  0, -1,         2, -0.5,  0.5},
    {9,  0, -9,         2,   -1,    1},
    {2,  0,  1,         0,    0,    0},
    {1,  2,  2,         0,    0,    0},
    {1, -1, -6,         2,   -2,    3},
    {1, -8, 15,         2,    3,    5},
    {1,  9, 14,         2,   -7, -  2}
};

/// Count of tests in "test_solveSquare()"
const int N_TESTS = sizeof(TESTS) / sizeof(TESTS[0]);


/// Testing function "solveSquare()"
/// @details If test is failed show it\n
///          In end show count succesful and failed tests
///
/// @note Has 24 tests
void test_solveSquare()
{
    int succesful = 0;

    Square square = {};

    for (int i = 0; i < N_TESTS; ++i)
    {
        square = TESTS[i];

        solveSquare(&square);

        if (test(  square.nRoots,   square.x1,   square.x2,
                 TESTS[i].nRoots, TESTS[i].x1, TESTS[i].x2))
            ++succesful;
    }

    printf("---------------------------------------------------\n");
    printf("# Total succesful: %2d\n# Total failed   : %2d\n", succesful, N_TESTS - succesful);
    printf("---------------------------------------------------\n");
}

/// Test one square
/// @details Show if test is failed\n
///          Don`t show if test is succesful
///
/// @param [in] realRoots Count of real roots
/// @param [in] realX1 Real value of x1
/// @param [in] realX2 Real value of x2
/// @param [in] expectRoots Count of expect roots
/// @param [in] expectX1 Expect value of x1
/// @param [in] expectX2 Expect value of x2
/// @return 1 if test is succesful or 0 if test is failed
static int test(int   realRoots, double   realX1, double   realX2,
                int expectRoots, double expectX1, double expectX2)
{
    newAssert(std::isfinite  (realX1));
    newAssert(std::isfinite  (realX2));
    newAssert(std::isfinite(expectX1));
    newAssert(std::isfinite(expectX2));

    if (realRoots != expectRoots ||
       !isequals(realX1, expectX1) ||
       !isequals(realX2, expectX2))
    {
        printf("---------------------------------------------------\n");
        printf("# Failed:\n"
               "# Expect: nRoots = %2d, x1 = %4lg, x2 = %4lg\n"
               "# Real  : nRoots = %2d, x1 = %4lg, x2 = %4lg\n",
               expectRoots, expectX1, expectX2,
                 realRoots,   realX1,   realX2);
        printf("---------------------------------------------------\n");

        return 0;
    }

    return 1;
}
