#include <math.h>
#include <cmath>
#include "isequals.h"
#include "newassert.h"

/// Calculate`s error for "isequals()"
static const double ZERO_VAL = 0.00001;

/// Equals two double values
/// @param [in] n1 First val to equals
/// @param [in] n2 Second val to equals
/// @return 1 if n1 == n2 or 0 if n1 != n2
/// @note ZERO_VAL is a calculate`s error
int isequals(double n1, double n2)
{
    newAssert(std::isfinite(n1));
    newAssert(std::isfinite(n1));

    return fabs(n1 - n2) < ZERO_VAL;
}
