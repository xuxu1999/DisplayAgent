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
	int result = DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOGMAIN),NULL,DialogProc);//��������
	if (result == IDCANCEL) {
		MessageBoxA(NULL, "����ȡ��", "��ʾ", MB_OK);
	}
	else if (result == IDYES) {
		MessageBox(NULL, "����ȷ��", "��ʾ", MB_OK);
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
	wsprintf(szMsg, "��Ϣ��0x%x\n", uMsg);
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//SetWindowText(hWnd, "win32�Ի���");
		//����ͼ��
		HICON hicon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1));
		//������Ϣ
		SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
		SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);
	}
		
		break;
	case WM_COMMAND://������Ϣ
	{
		int wId = LOWORD(wParam);
		switch (wId)
		{
		case IDOK:
			SetWindowText(hWnd, "����ȷ��");
			break;
		case IDCANCEL:
			SetWindowText(hWnd, "����ȡ��");
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