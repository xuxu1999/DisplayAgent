#include<iostream>
#include<fstream>
using namespace std;

void asciiReadWriteFile(const char* readFileName, const char* writeFileName)
{
	fstream read(readFileName, ios::in);
	fstream write(writeFileName, ios::out);
	//1.ע�⣺����Կո�ͻ���
	/*while (!read.eof())
	{
		char key;
		read >> key;
		write << key;
	}*/

	//2.get() put()��д
	while (!read.eof())
	{
		char key;
		read.get(key);
		write.put(key);
	}
	read.close();
	write.close();
}

//��������ʽ��д�ļ�
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

//�ļ�ָ���ƶ�
void seekReadFile(const char* fileName)
{
	fstream fread(fileName, ios::in);
	if (!fread) {
		cout << "open err" << endl;

	}
	fread.seekg(3);
	char key = fread.get();
	cout << key << endl;
	fread.seekg(1, ios::beg);//��Կ�ʼλ��ƫ��һ��
	cout << (char)fread.get() << endl;
}
int main()
{
	//���ļ�����
	fstream file("xx.txt", ios::in | ios::out | ios::trunc);
	if (!file || !file.is_open())
	{
		cerr << "�ļ���ʧ��" << endl;
	}
	file.close();
	
	//��д�ļ�
	//asciiReadWriteFile("read.txt", "write.txt");

	binaryReadWrite("aa.txt", "bb.txt");

	//�ļ�ָ���ƶ�
	seekReadFile("seek.txt");
	return 0;
}