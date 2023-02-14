// XML-demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;
void createXML();
void readXML();
int main()
{
	XMLDocument xml;
	if (xml.LoadFile("computer.xml") != XML_SUCCESS)
		createXML();
    cout << "--------" << endl;
    readXML();
    
}
void createXML()
{
	
    //声明
    XMLDocument xml;
    //创建xml头，文件格式 <?xml version="1.0" ....>
    XMLDeclaration* declaration = xml.NewDeclaration();
    xml.InsertFirstChild(declaration);

    //创建根节点
    XMLElement* rootNode = xml.NewElement("computer");
    xml.InsertEndChild(rootNode);

    //创建子节点
    XMLElement* root_1_NodeComputerMonitor = xml.NewElement("ComputerMonitor");
    XMLElement* root_1_NodeKeyboard = xml.NewElement("Keyboard");
    XMLElement* root_1_CPU = xml.NewElement("CPU");

	//------------
	//给子节点增加内容
	//------------
	XMLText* text_root_1_NodeComputerMonitor = xml.NewText("SAMSUNG");
	root_1_NodeComputerMonitor->InsertFirstChild(text_root_1_NodeComputerMonitor);

	XMLText* text_root_1_root_1_CPU = xml.NewText("intel");
	root_1_CPU->InsertFirstChild(text_root_1_root_1_CPU);

	//------------
	//给子节点增加内容
	//------------
	root_1_NodeComputerMonitor->SetAttribute("size", "15");
	root_1_CPU->SetAttribute("series", "XEON");

	//------------
	//创建子节点的子节点
	//------------
	XMLElement* root_2_NodeKeyboardAttribute = xml.NewElement("KeyboardAttribute");

	//------------
	//给子节点的子节点增加内容
	//------------
	XMLText* text_root_2_NodeKeyboardAttribute = xml.NewText("cherry Mechanical Keyboard");
	root_2_NodeKeyboardAttribute->InsertFirstChild(text_root_2_NodeKeyboardAttribute);

	//------------
	//构建xml树，根节点的下的子节点树
	//------------
	rootNode->InsertEndChild(root_1_NodeComputerMonitor);//childNodeStu是root的子节点
	rootNode->InsertEndChild(root_1_NodeKeyboard);
	rootNode->InsertEndChild(root_1_CPU);
	//------------
	//构建xml树，根节点的下的子节点的子节点树
	//------------
	root_1_NodeKeyboard->InsertEndChild(root_2_NodeKeyboardAttribute);

	//------------
	//将xml保存到当前项目中
	//------------
	xml.SaveFile("./computer.xml");
	cout << "xml创建";

}

void readXML()
{
	//声明
	XMLDocument xml;

	//导入xml文件
	if (xml.LoadFile("computer.xml") != XML_SUCCESS)
		return;

	//根节点
	XMLElement* rootNode = xml.RootElement();
	if (rootNode == nullptr)
		return;
	//cout<<rootNode->GetLineNum()<<endl;
	//读取第一层子节点信息打印
	XMLElement* root_1_NodeComputerMonitor = rootNode->FirstChildElement("ComputerMonitor");
	string text_root_1_NodeComputerMonitor = root_1_NodeComputerMonitor->GetText();
	cout << "text_root_1_NodeComputerMonitor:" << text_root_1_NodeComputerMonitor << endl;

	////读取第二层子节点信息打印
	XMLElement* root_1_NodeKeyboard = rootNode->FirstChildElement("Keyboard");
	XMLElement* root_2_NodeKeyboardAttribute = root_1_NodeKeyboard->FirstChildElement("KeyboardAttribute");
	string text_root_2_NodeKeyboardAttribute = root_2_NodeKeyboardAttribute->GetText();
	cout << "text_root_2_NodeKeyboardAttribute = " << text_root_2_NodeKeyboardAttribute.c_str() << endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
