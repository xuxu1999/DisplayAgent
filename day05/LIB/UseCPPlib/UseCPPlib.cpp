#include<iostream>

using namespace std;
//����Ҫ����
int CPPlib_add(int a, int b);
int CPPlib_sub(int a, int b);
#pragma comment(lib,"../x64/Debug/CPPlib.lib")

//c++��c��
extern "C" int Clib_add(int a, int b);
extern "C" int Clib_sub(int a, int b);
#pragma comment(lib,"../x64/Debug/Clib.lib")
int main()
{
	int sum = CPPlib_add(1, 2);
	int sub = CPPlib_sub(2, 1);
	cout << "sum=" << sum << "\tsub=" << sub << endl;

	//c++����c��
	sum = Clib_add(4, 5);
	sub = Clib_sub(6, 4);
	cout << "sum=" << sum << "\tsub=" << sub << endl;
	system("pause");

	return 0;
}