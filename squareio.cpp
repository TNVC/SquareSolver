#include <stdio.h>
#include <math.h>
#include <string.h>
#include "square.h"
#include "squareio.h"
#include "isequals.h"
#include "newassert.h"


static double scanDouble(void);

static void printNumberSplit   (double n, const char *str);
static void printNumberSeparate(double n, const char *str);


/// Scan coeffs for square
/// @param [out] square Contains a-, b- and c-coeffs
/// @return 1 if square was scan or 0 if square wasn`t scan
int scanSquare(Square *square)
{
    newAssert(square != nullptr);

    printf("# Input a-coeff (input EOF to quit): ");
    if    (isnan(square->a = scanDouble()))
        return 0;

    printf("# Input b-coeff (input EOF to quit): ");
    if    (isnan(square->b = scanDouble()))
        return 0;

    printf("# Input c-coeff (input EOF to quit): ");
    if    (isnan(square->c = scanDouble()))
        return 0;

    return 1;
}

/// Show square roots
/// @param [in] square Contains count of roots, first root and second root
void printSquare(const Square *square)
{
    newAssert(square != nullptr);

    showExpression(square);
    printf(" has ");

    switch (square->nRoots)
    {
        case 0:
            puts("no roots");
            break;

        case 1:
            printf("one root: x = %lg\n", square->x1);
            break;

        case 2:
            if(isequals(square->x1, square->x2))
                printf("two equals roots: x1 = x2 = %lg\n", square->x1);
            else
                printf("two roots: x1 = %lg, x2 = %lg\n", square->x1, square->x2);
            break;

        case INF_ROOTS:
            puts("infinity roots");
            break;

        default:
            printf("Error!!\nsquare->nRoots = %d\n", square->nRoots);
    }
}

/// Show square expression
/// @param [in] square Struct with all needed info about expression
/// @note Don`t add '\\n' in end
void showExpression(const Square *square)
{
    newAssert(square != nullptr);

    if (!isequals(square->a, 0))
        printNumberSplit(square->a, "x2");

    if (!isequals(square->b, 0))
    {
        if (!isequals(square->a, 0))
            printNumberSeparate(square->b, "x");
        else
            printNumberSplit(square->b, "x");
    }

    if (!isequals(square->c, 0))
    {
        if (isequals(square->a, 0) && isequals(square->b, 0))
            printNumberSplit(square->c, "");
        else
            printNumberSeparate(square->c, "");
    }

    if (isequals(square->a, 0) &&
        isequals(square->b, 0) &&
        isequals(square->c, 0))
        printf("0 ");

    printf("= 0");
}

/// Read one double
/// @details Read while input is incorrect or read EOF
///
/// @return One double value from input or NAN if read EOF
/// @note If incorrect input scan again
static double scanDouble()
{
    double n = 0;

    int res = 0;

    while ((res = scanf("%lg", &n)) != 1 && res != EOF)
    {
        printf("Incorrect input!! Try again: ");

        while (getchar() != '\n')
            continue;
    }

    if (res == EOF)
        return NAN;

    while (getchar() != '\n')
        continue;

    return n;
}


///Print number and sign split
/// @details If sign is plus it don`t print, if sign is minus it print
///
/// @param [in] n Number to print
/// @param [in] str String which concatenation to number
/// @note If str != "" and (n == 1 or n == -1) then n not print
static void printNumberSplit(double n, const char *str)
{
    newAssert(str != nullptr);

    if (strlen(str) == 0)
        printf("%lg ", n);
    else if (isequals(n,  1) ||
             isequals(n, -1))
        printf("%s%s ", n > 0 ? "" : " ", str);
    else
        printf("%lg%s ", n, str);
}

///Print number and sign separate
/// @details Print sign always
///
/// @param [in] n Number to print
/// @param [in] str String which concatenation to number
/// @note If str != "" and (n == 1 or n == -1) n not print
static void printNumberSeparate(double n, const char *str)
{
    newAssert(str != nullptr);

    if (strlen(str) == 0)
        printf("%c %lg "  , n > 0 ? '+' : '-', fabs(n));
    else if (isequals(n,  1) ||
             isequals(n, -1))
        printf("%c %s "   , n > 0 ? '+' : '-', str);
    else
        printf("%c %lg%s ", n > 0 ? '+' : '-', fabs(n), str);
}
