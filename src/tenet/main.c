//
// Created by 孟伸 on 2021/12/8.
//

#include <stdio.h>
int main(void){
	register long num asm("rax")=0x100000000;
	asm("movl $0x1, %eax");
	printf("%ld\n",num);
	return 0;
}