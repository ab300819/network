#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void){

    const char* strA="1.0";
    printf("%f\n",atof(strA));

    const char* strB="200000000000000000000000000000.0";
    char* end;
    double num=strtol(strB,&end,10);
    if (errno == ERANGE) {
        printf("Range error, got: ");
        errno=0;
    }
    printf("%f\n",num);
    return EXIT_SUCCESS;
}