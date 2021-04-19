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

	wc.style         = CS_HREDRAW|CS_VREDRAW;
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
	if (!aWndClass) {
		MessageBox(NULL, _T("Window create error"), szClassName, MB_OK|MB_ICONSTOP);
	}
	return (aWndClass != 0);
	
};

// ������ ����� ��������� ���������
WORD WinApp::Go() {
	// ��������� ���� ��������� ���������
	while(GetMessage(&msg, 0, 0, 0)) {
		// ����������. �����., ����� � ������� ����������
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
};