#include "stdafx.h"
#include "WinApp.h"

WinApp::WinApp(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
	// ���������� ���� ������
	isErr = 0;
	// ��������� ��������� ����������
	hInstance = hInst;
};

//����������� ������ ����
BOOL WinApp::RegisterWndClass(LPCWSTR szClassName, WNDPROC WndProc) {
	ATOM aWndClass; // ���� ��� ���� ��������
	WNDCLASS wc; // ��������� ��� ����������� ������ ����
	
	wc.style         = 0;
	wc.lpfnWndProc   = (WNDPROC) WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = szClassName;
	aWndClass = RegisterClass(&wc);
	return (aWndClass != 0);
	
};

// ������ ����� ��������� ���������
WORD WinApp::Go(void)
{
  // ��������� ���� ��������� ���������
  while(GetMessage(&msg, 0, 0, 0))
  {
    DispatchMessage(&msg);
  }
  return msg.wParam;
};