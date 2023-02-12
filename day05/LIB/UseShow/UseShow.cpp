#include<Windows.h>
#include<iostream>
using namespace std;
typedef int(*ADD)(int m, int n);
typedef int(*SUB)(int m, int n);
typedef int(*MUL)(int m, int n);
int main() {
	HINSTANCE hDll= LoadLibrary(L"CPPdll.dll");
	cout << "hDll:" << hDll << endl;

	SUB mySub = (SUB)GetProcAddress(hDll, "CPPdll_sub");
	int sub = mySub(5, 4);
	cout << "sub=" << sub << endl;
	return 0;
}