#include<stdio.h>
int main()
{
	int a[5] = { 1,2,3,4,5 };
	int n = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < n; i++)
	{
		//printf("%d", a[i]);
		printf("%d", *(a + i));
	}
	int* p = a;
	for (int i = 0; i < n; i++)
	{
		p[i] = 2 * i;
	}
	for (int i = 0; i < n; i++)
	{
		//printf("%d", a[i]);
		printf("%d", *(a + i));
	}
	return 0;
}