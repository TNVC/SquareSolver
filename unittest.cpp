#include <stdio.h>
#include <cmath>
#include "square.h"
#include "solver.h"
#include "isequals.h"
#include "unittest.h"
#include "newassert.h"


static Square nextTest(FILE *fileptr, int *next);
static int fscanSquare(Square *square, FILE *fileptr);
static int test(int   realRoots, double   realX1, double   realX2,
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
    {1,  9, 14,         2,   -7,   -2}
};

/// Count of tests in "test_solveSquare()"
static const int N_TESTS = sizeof(TESTS) / sizeof(TESTS[0]);


/// Testing function "solveSquare()"
/// @details If test is failed show it\n
///          In end show count succesful and failed tests
///
/// @param [in] fileptr FILE* with tests
/// @note Has 24 tests
/// @note If fileptr == NULL then function use its tests
void test_solveSquare(FILE *fileptr)
{
    int contin = 0;

    int succesful = 0;
    int failed    = 0;

    Square square       = {},
           testSquare   = {};

    for (testSquare = nextTest(fileptr, &contin); contin; testSquare = nextTest(fileptr, &contin))
    {
        square = testSquare;

        square.nRoots = 0;
        square.x1 = square.x2 = NAN;

        solveSquare(&square);

        if (test(square.nRoots,     square.x1,     square.x2,
             testSquare.nRoots, testSquare.x1, testSquare.x2))
            ++succesful;
        else
            ++failed;
    }

    printf("---------------------------------------------------\n");
    printf("# Total succesful: %2d\n# Total failed   : %2d\n", succesful, failed);
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

/// Get next test struct
/// @param [in] fileptr FILE* with tests
/// @param [out] next Marker then need continue
/// @return Struct for test
/// @note If fileptr == NULL return its test
static Square nextTest(FILE *fileptr, int *next)
{
    Square square = {};

    static int lastTest = 0;

    if (fileptr == nullptr && lastTest == N_TESTS)
    {
        *next = 0;

        return square;
    }

    if (fileptr == nullptr)
    {
        *next = 1;

        return TESTS[lastTest++];
    }

    *next = fscanSquare(&square, fileptr);

    return square;
}


/// Scan one Square from file
/// @param [out] square Square for test
/// @param [in] fileptr File with tests
/// @return 1 if Square was read and 0 if Square wasn`t read
static int fscanSquare(Square *square, FILE *fileptr)
{
    newAssert(square  != nullptr);
    newAssert(fileptr != nullptr);

    if (fscanf(fileptr, "%lg, %lg, %lg, %d, %lg, %lg",
        &square->a, &square->b, &square->c,
        &square->nRoots, &square->x1, &square->x2) != 6)
        return 0;

    return 1;
}
