//���� _declspec(dllexport) ����������ַ
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