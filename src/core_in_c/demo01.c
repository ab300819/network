#include <stdio.h>
#include <threads.h>

int run(void *args){
thrd_t id=thrd_current();
printf((const char*)args,id);
return thrd_success;
}

int main(void) {
#ifndef __STDC_NO_THREADS__
	thrd_t thread;
    int result;
    thrd_create(&thread, run, "hello C11 thread with id: %lu.\n");
    if(thrd_join(thread, &result)==thrd_success){
        printf("Thread return %d at the end.\n",result);
    }
#endif
	return 0;
}