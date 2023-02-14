// cJson-demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
extern "C" {
#include<string.h>
#include<stdio.h>
#include"cJSON.h"
}
using namespace std;
//解析带数组json
int main()
{
    /*  {
			"text": [
			{
				"width": 1280,
					"height" : 720
			},
		{
			"width": 1920,
			"height" : 1080
		},
		{
			"width": 3840,
			"height" : 2160
		}
			]
		}    */
	char data[] =
		"{"
		"\"text\": ["
		"{"
		"\"width\": 1280,"
		"\"height\" : 720"
		"},"
		"{"
		"\"width\": 1920,"
		"\"height\" : 1080"
		"},"
		"{"
		"\"width\": 3840,"
		"\"height\" : 2160"
		"}"
		"]"
		"}";
	cJSON* root = cJSON_Parse(data);
	if (root == NULL)return 0;
	//2. 解析字段
	cJSON* item;
	int i;
	item = cJSON_GetObjectItem(root, "text");
	if (item)
	{
		//获取数组的大小
		int ArraySize = cJSON_GetArraySize(item);//获取数组中有多少个{}对象
		//解析数组的里的每个成员
		for (i = 0; i < ArraySize; i++)
		{
			//取出数组下标对象
			cJSON* array_item = cJSON_GetArrayItem(item, i);
			if (array_item == NULL)continue;

			//解析数据
			cJSON* obj = cJSON_GetObjectItem(array_item, "width");
			if (obj)
			{
				printf("width=%d\n", obj->valueint);
			}
			obj = cJSON_GetObjectItem(array_item, "height");
			if (obj)
			{
				printf("height=%d\n", obj->valueint);
			}
		}
	}

	//3. 释放空间
	cJSON_Delete(root);
	return 0;
}
//解析嵌套json
int main2()
{
    char data[] =
        "{"
        "\"data1\": {"
        "\"text\": \"我是一个字符串数据1\","
        "\"number\" : 666,"
        "\"state1\" : false,"
        "\"state2\" : true,"
        "\"state3\" : null"
        "},"
        "\"data2\": {"
        "\"text\":\"我是一个字符串数据2\","
        "\"number\" : 666,"
        "\"state1\" : false,"
        "\"state2\" : true,"
        "\"state3\" : null"
        "}"
        "}";
	//1. 载入JSON数据
	cJSON* root = cJSON_Parse(data);
	if (root == NULL)return 0;

	//2. 解析字段
	cJSON* item;

	item = cJSON_GetObjectItem(root, "data1");
	if (item)
	{
		cJSON* obj;
		obj = cJSON_GetObjectItem(item, "text");
		if (obj)
		{
			printf("text=%s\n", obj->valuestring);
		}

		obj = cJSON_GetObjectItem(item, "number");
		if (obj)
		{
			printf("number=%d\n", obj->valueint);
		}

		obj = cJSON_GetObjectItem(item, "state1");
		if (obj)
		{
			printf("state1=%d\n", obj->valueint);
		}

		obj = cJSON_GetObjectItem(item, "state2");
		if (obj)
		{
			printf("state2=%d\n", obj->valueint);
		}

		obj = cJSON_GetObjectItem(item, "state3");
		if (obj)
		{
			printf("state3=%d\n", obj->valueint);
		}
	}

	item = cJSON_GetObjectItem(root, "data2");
	if (item)
	{
		cJSON* obj;
		obj = cJSON_GetObjectItem(item, "text");
		if (obj)
		{
			printf("text=%s\n", obj->valuestring);
		}

		obj = cJSON_GetObjectItem(item, "number");
		if (obj)
		{
			printf("number=%d\n", obj->valueint);
		}

		obj = cJSON_GetObjectItem(item, "state1");
		if (obj)
		{
			printf("state1=%d\n", obj->valueint);
		}

		obj = cJSON_GetObjectItem(item, "state2");
		if (obj)
		{
			printf("state2=%d\n", obj->valueint);
		}

		obj = cJSON_GetObjectItem(item, "state3");
		if (obj)
		{
			printf("state3=%d\n", obj->valueint);
		}
	}

	//3. 释放空间
	cJSON_Delete(root);
    return 0;
}
int main1()
{
   cJSON * pJsonObj = cJSON_CreateObject();

   if (pJsonObj != nullptr) {
       cJSON_AddStringToObject(pJsonObj, "name", "xuxu");
       cJSON_AddStringToObject(pJsonObj, "sex", "男");
       cJSON_AddStringToObject(pJsonObj, "address", "江西九江");
       cJSON_AddNumberToObject(pJsonObj, "age", 23);
       cJSON_AddBoolToObject(pJsonObj, "毕业",false);
       char *szJson = cJSON_Print(pJsonObj);//转字符串
       if (szJson != nullptr) {
           printf("%s\n", szJson);
           free(szJson);
       }
       cJSON_Delete(pJsonObj);
   }
   else
   {
       return -1;
   }

   return 0;
    //std::cout << "Hello World!\n";
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
