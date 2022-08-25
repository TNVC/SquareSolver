#include <stdio.h>
#include <cmath>
#include "square.h"
#include "solver.h"
#include "isequals.h"
#include "unittest.h"
#include "newassert.h"

static void init(int a, int b, int c, Square *square);
static int  test(int   realRoots, double   realX1, double   realX2,
                 int expectRoots, double expectX1, double expectX2);


/// Testing function "solveSquare()"
/// @details If test is failed show it\n
///          In end show count succesful and failed tests
///
/// @note Has 8 tests
void test_solveSquare()
{
    int succesful = 0, failed = 0;

    Square square = {};

    init(0, 0, 0, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, INF_ROOTS, 0, 0))
        ++succesful;
    else
        ++failed;

    init(1, 0, 0, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, 0, 0))
        ++succesful;
    else
        ++failed;

    init(0, 1, 0, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 1, 0, 0))
        ++succesful;
    else
        ++failed;

    init(0, 0, 1, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 0, 0, 0))
        ++succesful;
    else
        ++failed;

    init(0, 1, 1, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 1, -1, -1))
        ++succesful;
    else
        ++failed;

    init(1, 0, 1, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 0, 0, 0))
        ++succesful;
    else
        ++failed;

    init(1, 0, -1, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, -1, 1))
        ++succesful;
    else
        ++failed;

    init(1, 1, 0, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, -1, 0))
        ++succesful;
    else
        ++failed;

    init(1, 2, 1, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, -1, -1))
        ++succesful;
    else
        ++failed;

    init(1, 4, 4, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, -2, -2))
        ++succesful;
    else
        ++failed;

    init(1, 6, 9, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, -3, -3))
        ++succesful;
    else
        ++failed;

    init(1, -2, 1, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, 1, 1))
        ++succesful;
    else
        ++failed;

    init(1, -4, 4, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, 2, 2))
        ++succesful;
    else
        ++failed;

    init(1, -6, 9, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, 3, 3))
        ++succesful;
    else
        ++failed;

    init(0, 2, 1, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 1, -0.5, -0.5))
        ++succesful;
    else
        ++failed;

    init(0, -1, 5, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 1, 5, 5))
        ++succesful;
    else
        ++failed;

    init(0, 4, -9, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 1, 2.25, 2.25))
        ++succesful;
    else
        ++failed;

    init(4, 0, -1, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, -0.5, 0.5))
        ++succesful;
    else
        ++failed;

    init(9, 0, -9, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, -1, 1))
        ++succesful;
    else
        ++failed;

    init(2, 0, 1, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 0, 0, 0))
        ++succesful;
    else
        ++failed;

    init(1, 2, 2, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 0, 0, 0))
        ++succesful;
    else
        ++failed;

    init(1, -1, -6, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, -2, 3))
        ++succesful;
    else
        ++failed;

    init(1, -8, 15, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, 3, 5))
        ++succesful;
    else
        ++failed;

    init(1, 9, 14, &square);
    solveSquare(&square);

    if (test(square.nRoots, square.x1, square.x2, 2, -7, -2))
        ++succesful;
    else
        ++failed;

    printf("---------------------------------------------------\n");
    printf("# Total succesful: %2d\n# Total failed   : %2d\n", succesful, failed);
    printf("---------------------------------------------------\n");
}

/// Init square for test
/// @param [in] a a-coeff
/// @param [in] b b-coeff
/// @param [in] c c-coeff
/// @param [out] square Target square for test
static void init(int a, int b, int c, Square *square)
{
    newAssert(square != nullptr);

    square->a = a;
    square->b = b;
    square->c = c;
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
