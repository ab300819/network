
#include <threads.h>
#include <stdio.h>
#include <errno.h>
#include <tgmath.h>
int run(void* data) {
  log(0.0);
  perror("Run");  // "Run: Numerical result out of range".
  return thrd_success;
}
int main(void) {
#ifndef __STDC_NO_THREADS__
  thrd_t thread;
  thrd_create(&thread, run, NULL);
  thrd_join(thread, NULL);
  perror("Main");  // "Main: Success".
#endif
  return 0; 
}