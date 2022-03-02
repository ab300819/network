#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void){

        time_t current_time=time(NULL);
        if(current_time!=(time_t)(-1)){
            printf("The current timestamp is %ld(s)",current_time);
        }

    return EXIT_SUCCESS;
}