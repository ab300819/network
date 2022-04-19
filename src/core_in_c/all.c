// https://time.geekbang.org/column/article/470130
// 包含基本 C 语言语法

#include <stdio.h>
// 定义申明两个全局变量：hellostr、global，类型分别是：char*、int
char* hellostr = "HelloWorld";
int global = 5;
// 定义一个结构体类型HW
struct HW {
	char* str;
	int sum;
	long indx;
};
// 函数
void show(struct HW* hw, long x) {
	printf("%d %d %s\n", global, x, hellostr);
	printf("%d %d %s\n", hw->sum, hw->indx, hw->str);
}
// 函数
int main(int argc, char const* argv[]) {
	// 定义三个局部变量：x、parm、ishw，类型分别是：int、log、struct HW
	int x;
	long parm = 10;
	struct HW ishw;
	// 变量赋值
	ishw.str = hellostr;
	ishw.sum = global;
	ishw.indx = parm;
	// 调用函数
	show(&ishw, parm);
	return x;
}