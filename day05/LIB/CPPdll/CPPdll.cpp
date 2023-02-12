//导出 _declspec(dllexport) 导出函数地址
 int CPPdll_add(int a, int b)
{
	return a + b;
}
 int CPPdll_sub(int a, int b)
{
	return a - b;
}
_declspec(dllexport) int CPPdll_mul(int a, int b)
{
	return a * b;
}