#include<stdio.h>
#pragma comment(lib,"../x64/Debug/Clib.lib")
// 通知链接器到哪抓源码
int main()
{
	int sum, sub;
	sum = Clib_add(1, 2);
	sub = Clib_add(4, 1);
	printf("sum=%d\tsub=%d\n", sum, sub);
}