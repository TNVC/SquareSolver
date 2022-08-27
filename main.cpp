#include <stdio.h>
#include <string.h>
#include "square.h"
#include "squareio.h"
#include "solver.h"
#include "unittest.h"

int main(int argc, const char *argv[])
{
    #ifdef DEBUG_MODE_

    FILE *fileptr = nullptr;

    if (argc == 2 || argc > 3)
    {
        printf("Incorrect use!!\n");
        printf("%s -f [file name]\n", argv[0]);
    }

    if (argc >= 3)
    {
        if (strncmp(argv[1], "-f", 3) == 0)
        {
            fileptr = fopen(argv[2], "r");

            if (fileptr == nullptr)
                printf("Fail to open \"%s\"!!\n", argv[2]);
        }
        else
        {
            printf("Incorrect use!!\n");
            printf("%s -f [file name]\n", argv[0]);
        }
    }

    test_solveSquare(fileptr);

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
