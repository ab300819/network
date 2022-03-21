#include <stdalign.h>
#include <stdio.h>

int main(void) {
#if __alignas_is_defined == 1 && __alignof_is_defined == 1
	alignas(1024) int n = 1;

	printf("The alignment of n is %zu\n",alignof(n));	 // "The alignment of n is 1024".
	printf("The address of n is: %p\n", &n);

#endif
	return 0;
}