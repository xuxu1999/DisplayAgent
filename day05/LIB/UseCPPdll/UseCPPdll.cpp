#include<iostream>
using namespace std;
_declspec(dllimport) int CPPdll_add(int a, int b);
_declspec(dllimport) int CPPdll_sub(int a, int b);
_declspec(dllimport) int CPPdll_mul(int a, int b);
#pragma comment(lib,"../x64/Debug/CPPdll.lib")
int main()
{
	int sum = CPPdll_add(1, 2);
	int sub = CPPdll_sub(4, 2);
	int mul = CPPdll_mul(2, 4);
	cout << "sum=" << sum << "\tsub=" << sub << "\tmul=" << mul << endl;

	return 0;
}