#include<iostream>
#include<fstream>
using namespace std;

void asciiReadWriteFile(const char* readFileName, const char* writeFileName)
{
	fstream read(readFileName, ios::in);
	fstream write(writeFileName, ios::out);
	//1.注意：会忽略空格和换行
	/*while (!read.eof())
	{
		char key;
		read >> key;
		write << key;
	}*/

	//2.get() put()读写
	while (!read.eof())
	{
		char key;
		read.get(key);
		write.put(key);
	}
	read.close();
	write.close();
}

//二进制形式读写文件
void binaryReadWrite(const char* readFileName, const char* writeFileName)
{
	fstream readObj(readFileName, ios::in | ios::binary);
	fstream writeObj(writeFileName, ios::out | ios::binary);
	while (!readObj.eof())
	{
		char str[1024] = "";
		readObj.read(str, 1024);
		writeObj.write(str, 1024);
	}
	readObj.close();
	writeObj.close();
}

//文件指针移动
void seekReadFile(const char* fileName)
{
	fstream fread(fileName, ios::in);
	if (!fread) {
		cout << "open err" << endl;

	}
	fread.seekg(3);
	char key = fread.get();
	cout << key << endl;
	fread.seekg(1, ios::beg);//相对开始位置偏移一个
	cout << (char)fread.get() << endl;
}
int main()
{
	//打开文件测试
	fstream file("xx.txt", ios::in | ios::out | ios::trunc);
	if (!file || !file.is_open())
	{
		cerr << "文件打开失败" << endl;
	}
	file.close();
	
	//读写文件
	//asciiReadWriteFile("read.txt", "write.txt");

	binaryReadWrite("aa.txt", "bb.txt");

	//文件指针移动
	seekReadFile("seek.txt");
	return 0;
}