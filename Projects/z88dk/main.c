// http://www.z88dk.org/wiki/doku.php?id=platform:zx
// ZCC setup
// Application: {z88dk path}\bin\zcc.exe
// Parameters : +zx -lndos -create-app -o %game% *.c

#include <stdio.h>
#include "library.h"

void main(void)
{
    printf("hello world\n");
    myFunc();
}
