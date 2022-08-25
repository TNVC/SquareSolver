#ifndef NEWASSERT_H_
#define NEWASSERT_H_

#include <stdio.h>
#include <stdlib.h>

#define newAssert(expression)                                          \
    if (!(expression))                                                 \
    {                                                                  \
        printf("Fail in %s. File: %s, Function: %s, Line: %d\n",       \
              #expression, __FILE__, __PRETTY_FUNCTION__, __LINE__);   \
        abort();                                                       \
    }

#endif

