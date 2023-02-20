#include<Windows.h>
#include "resource.h"
#include"ManagerConfigFile.h"

void testManagerConfigFile() {
	ManagerConfigFile config;
	config.SetFilePath("./a.ini");
	string value = "";
	string error = "";
	config.GetValue("ServerUrl", "PcName", value, error);

	cout << value << endl;
	cout << error << endl;

	error = "";
	config.ModifyValue("ServerUrl", "PcName", "5.0", error);
	cout << error << endl;
}
BOOL CALLBACK DialogProc(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);
HINSTANCE g_hInstance;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int result = DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOGMAIN),NULL,DialogProc);//阻塞函数
	if (result == IDCANCEL) {
		MessageBoxA(NULL, "点了取消", "提示", MB_OK);
	}
	else if (result == IDYES) {
		MessageBox(NULL, "点了确定", "提示", MB_OK);
	}

	//test
	testManagerConfigFile();

	return 0;
		
}

BOOL CALLBACK DialogProc(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	TCHAR szMsg[200];
	wsprintf(szMsg, "消息：0x%x\n", uMsg);
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//SetWindowText(hWnd, "win32对话框");
		//加载图标
		HICON hicon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1));
		//发送消息
		SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
		SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);
	}
		
		break;
	case WM_COMMAND://命令消息
	{
		int wId = LOWORD(wParam);
		switch (wId)
		{
		case IDOK:
			SetWindowText(hWnd, "点了确定");
			break;
		case IDCANCEL:
			SetWindowText(hWnd, "点了取消");
			break;
		default:
			break;
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hWnd, IDOK);
		//DestroyWindow(hWnd);
		break;
	/*case WM_DESTROY:
		EndDialog(hWnd, IDOK);
		break;*/
	default:
		break;
	}
	return FALSE;
}