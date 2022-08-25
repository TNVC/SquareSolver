#include <cmath>
#include "square.h"
#include "solver.h"
#include "isequals.h"
#include "newassert.h"


static void solveLine        (Square *square);
static void solveWhereBIsZero(Square *square);
static void solveWhereCIsZero(Square *square);
static void solveFullSquare  (Square *square);


/// Solve square expression
/// @details Roots are increase sorted\n
///          If count of roots equals 1 then first root equals second root\n
///          If count of roots equals 0 or INF_ROOTS then first and second roots equals 0
///
/// @param [in/out] square Struct with a-, b-, c-coeffs, first, second roots and count of roots
/// @note Set count of roots to INF_ROOTS if any number is root
void solveSquare(Square *square)
{
    newAssert(square != nullptr);

    newAssert(std::isfinite(square->a));
    newAssert(std::isfinite(square->b));
    newAssert(std::isfinite(square->c));

    if      (isequals(square->a, 0))
        solveLine        (square);
    else if (isequals(square->b, 0))
        solveWhereBIsZero(square);
    else if (isequals(square->c, 0))
        solveWhereCIsZero(square);
    else
        solveFullSquare  (square);
}

/// Solve line expression
/// @param [in/out] expression Struct with coeffs and root
/// @note Set count of roots to INF_ROOTS if any number is root
static void solveLine(Square *expression)
{
    newAssert(expression != nullptr);

    if (isequals(expression->b, 0))
    {
        expression->x1 = expression->x2 = 0;

        expression->nRoots = isequals(expression->c, 0) ? INF_ROOTS : 0;
    }
    else
    {
        expression->x1 = expression->x2 = -expression->c / expression->b;

        expression->nRoots = 1;
    }
}

/// Solve square expression where b == 0
/// @param [in/out] square Struct with a-, b-, c-coeffs, first, second roots and count of roots
static void solveWhereBIsZero(Square *square)
{
    newAssert(square != nullptr);

    if (square->c < 0)
    {
        square->x1 = -sqrt(-square->c / square->a);
        square->x2 =  sqrt(-square->c / square->a);

        square->nRoots = 2;
    }
    else if (isequals(square->c, 0))
    {
        square->x1 = square->x2 = 0;

        square->nRoots = 2;
    }
    else if (square->c > 0)
    {
        square->x1 = square->x2 = 0;

        square->nRoots = 0;
    }
}

/// Solve square expression where c == 0
/// @param [in/out] square Struct with a-, b-, c-coeffs, first, second roots and count of roots
static void solveWhereCIsZero(Square *square)
{
    newAssert(square != nullptr);

    double temp = -square->b / square->a;

    square->x1 = fmin(temp, 0);
    square->x2 = fmax(temp, 0);

    square->nRoots = 2;
}

/// Solve full square expression
/// @param [in/out] square Struct with a-, b-, c-coeffs, first, second roots and count of roots
static void solveFullSquare(Square *square)
{
    newAssert(square != nullptr);

    double D = square->b*square->b - 4*square->a*square->c;

    if (D < 0)
    {
        square->x1 = square->x2 = 0;

        square->nRoots = 0;
    }
    else if (isequals(D, 0))
    {
        square->x1 = square->x2 = -square->b / (2*square->a);

        square->nRoots = 2;
    }
    else
    {
        double sqrtD = sqrt(D);

        double temp1 = (-square->b + sqrtD) / (2*square->a),
               temp2 = (-square->b - sqrtD) / (2*square->a);

        square->x1 = fmin(temp1, temp2);
        square->x2 = fmax(temp1, temp2);

        square->nRoots = 2;
    }
}
