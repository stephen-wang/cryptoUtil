/* Copyright (c) 2018, wenzhi wang */

#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "cryptoUtil_types.h"


typedef struct {
    char oriCh;
    char expCh;
    int shift;
} ShiftVec;


int
testShiftAlpha()
{
    ShiftVec testVectors[5] = { {'a', 'b', 1},
                                {'b', 'd', 2},
                                {'Y', 'B', 3},
                                {'a', 'z', -1},
                                {'a', 'y', -2}};

    for (int i=0; i < sizeof testVectors/sizeof(ShiftVec); i++) {
        ShiftVec vec = testVectors[i];
        char actCh = ShiftAlpha(vec.oriCh, vec.shift);
        if (actCh != vec.expCh) {
            printf("**Error** CaesarShift(%c, %d), expect %c, actual %c\n", vec.oriCh, vec.shift, vec.expCh, actCh);
             return -1;
        }
    }

    printf("Case testShiftAlpha() passed\n");
    return 0;
}


int main(void) {
    int result = 0;
    result += testShiftAlpha();

    return result;
}
