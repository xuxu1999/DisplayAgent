# dispalyAgent学习记录

* WinBase

![image-20230206184051538](./assets/image-20230206184051538.png)



* 字符集问题 解决办法https://blog.csdn.net/kieson_uabc/article/details/109672682

  ![image-20230206185350283](./assets/image-20230206185350283.png)

Q：窗口关闭后，进程并未结束

## 字符编码

## 窗口

> * 注册窗口类
> * 窗口创建

## 消息

> * 消息基础
> * 创建消息

## 模态框和非模态框

> https://blog.csdn.net/mpp_king/article/details/79902755
>
> 模态弹框和非模态弹框最大的区别就是是否强制用户交互。模态弹框会打断用户的当前操作流程，用户不在弹框上操作的话，其余功能都使用不了。从这方面，我们可以看出来模态弹框的优缺点都十分的明显：优点是可以很好的获取的用户的视觉焦点，缺点是打断了用户的当前操作流程。模态弹框属于一种重量性反馈，一般用于用户进行重要的操作。

# 项目问题

![image-20230209223408260](./assets/image-20230209223408260.png)

```c
BOOL CALLBACK DialogProc(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);
```

64位返回值用 LRESULT ,32位用BOOL

> ![image-20230209223716217](./assets/image-20230209223716217.png)



Dialog

> ![image-20230210002204808](./assets/image-20230210002204808.png)

![image-20230210011026549](./assets/image-20230210011026549.png)

* 2023.2.10
* ![image-20230210013534516](./assets/image-20230210013534516.png)

> 目前只是一个静态界面



# cpp_study

## 文件流

```c++
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
```

![image-20230210201534449](./assets/image-20230210201534449.png)

![image-20230210204045879](./assets/image-20230210204045879.png)



![image-20230210204526472](./assets/image-20230210204526472.png)