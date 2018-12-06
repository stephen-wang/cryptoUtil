/* Copyright (c) 2018, wenzhi wang */

#include <ctype.h>

/*
 *  Shift an alphabet ch by abs(steps) positions. If steps > 0, right shift;
 *  left shift, otherwise, e.g.
 *      ch='a', steps=1, return 'b'
 *      ch='b', steps=2, return 'd'
 *      ch='Y', steps=3, return 'B'
 *      ch='a', steps=-1, return 'z'
 *      ch='A', steps=-2, return 'Y'
 *      ch='2', steps=-2, return '2'
 *
 *  Note: it's no-op if ch is non English charcter. 
 */

char
ShiftAlpha(char ch, int steps)
{
    char result = ch;
    char base = 0;

    //printf("%s shift <%c> %d positions\n", (steps > 0 ? "Right" : "Left"), ch, steps);
    if (islower(ch)) {
        base = 'a';
    } else if (isupper(ch)) {
        base = 'A';
    }

    if (base != 0) {
       if (steps < 0) {  //left shift
           steps *= -1;
           while (steps > 0) {
               result--;    
               steps --;
               if (result < base) {
                  result = base + 25;
               }
           }
       } else {          // right shift
           while (steps > 0) {
               result++;    
               steps--;
               if (result > base + 25) {
                  result = base;
               }
           }
       }
    }

    return result;
}
