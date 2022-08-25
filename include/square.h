#ifndef SQUARE_H_
#define SQUARE_H_

/// Value which means infinite roots
static const int INF_ROOTS = -1;

/// Struct with info about square
typedef struct {
    double   a;///< a-coeff
    double   b;///< b-coeff
    double   c;///< c-coeff
    int nRoots;///< Count of roots
    double  x1;///< First root
    double  x2;///< Second root
} Square;

#endif
