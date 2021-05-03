#include "stdafx.h"
#include "Window.h"
#include "WinApp.h"
#include "WndProc.h"

/*
������� ��������� ������� ��� ����
*/
HWND CreateMainWindow();
HWND CreateChildWindow(Window* parent);
HWND CreatePopupWindow(Window* parent);

// --- ���������� ���������� ����������
TCHAR* ClassName = _T("WindowClass"); // �������� ������ ����
TCHAR* PopupClassName = _T("PopupWindow");
TCHAR* ChildClassName = _T("ChildWwindow");

TCHAR* AppTitle = _T("������� ����"); // ��������� �����. ����

HINSTANCE hInstance;

// --- ������� ������� ���������� WinMain
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// ��������� �� ������ ������ Window - ������� ���� ����������
	Window* pMainWindow;
	Window* pPopupWindow;
	Window* pChildWindow;

	HWND hMainWnd;
	// --- ��������, ���� �� ���������� �������� �����
	if((hMainWnd = FindWindow(ClassName, NULL)) != NULL) {
		// ���� ������. ���� �������� �����, ��������������
		// � ��������� �� �������� ���� ��� ������� ����
		if (MessageBox(hMainWnd, L"��������� ��������� ��� �������! ���������� ������ � ����������?", 
			L"��������!", MB_YESNO | MB_ICONEXCLAMATION|MB_TASKMODAL) != IDYES) {
				DestroyWindow(hMainWnd);
				return FALSE;
		}
		if(IsIconic(hMainWnd))
			ShowWindow(hMainWnd, SW_RESTORE);
		SetForegroundWindow(hMainWnd);
		// ������ ����� ����� ������������
		return FALSE;
	}

	// ������� ������ ������ WinApp - ���� ����������
	WinApp App(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	// ������������ ����
	App.RegisterWndClass(ClassName, MainWndProc);
	App.RegisterWndClass(PopupClassName, PopupWndProc);
	App.RegisterWndClass(ChildClassName, ChildWndProc);
	if(App.Error()) return App.Error();
	// ������� ����
	pMainWindow = new Window(CreateMainWindow());
	pPopupWindow = new Window(CreatePopupWindow(pMainWindow));
	pChildWindow = new Window(CreateChildWindow(pMainWindow));		
	// ��������� ������, ������� ����� ���������� ��� �������� ����
	if(pMainWindow->Error()) pMainWindow->Error();
	if(pChildWindow->Error()) pChildWindow->Error();
	if(pPopupWindow->Error()) pPopupWindow->Error();
	// ���������� ����
	pMainWindow->Show(SW_SHOWMAXIMIZED);
	pChildWindow->Show(nCmdShow);
	pPopupWindow->Show(nCmdShow);
	// �������� � ���� ���������
	pMainWindow->Update();
	pChildWindow->Update();
	pPopupWindow->Update();
	// ��������� ����������
	App.Go();
	// ��������� ������
	return App.Error();
}

HWND CreateMainWindow() {
	return CreateWindow(
		ClassName,         // ��� ������ ����
		AppTitle,       // ��������� ����
		WS_OVERLAPPEDWINDOW, // ����� ����
		CW_USEDEFAULT,       // ������ ������� � ������������
		CW_USEDEFAULT,       // ����, �������� �� ��������� 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,                   // ������������� ������������� ����
		0,                   // ������������� ����
		hInstance,           // ������������� ����������
		NULL);     
}

HWND CreateChildWindow(Window* parent) {
	return CreateWindow(
		ChildClassName,         // ��� ������ ����
		L"�������� ����",       // ��������� ����
		WS_CHILDWINDOW|WS_CAPTION|WS_VISIBLE, // ����� ����
		150,       // ������ ������� � ������������
		150,       // ����, �������� �� ��������� 
		250,
		250,
		parent->getHWND(),                   // ������������� ������������� ����
		0,                   // ������������� ����
		hInstance,           // ������������� ����������
		NULL);    
}

HWND CreatePopupWindow(Window* parent) {
	return CreateWindow(
		PopupClassName,         // ��� ������ ����
		L"��������� ����",       // ��������� ����
		WS_POPUPWINDOW|WS_CAPTION|WS_VISIBLE, // ����� ����
		300,       // ������ ������� � ������������
		100,       // ����, �������� �� ��������� 
		300,
		300,
		parent->getHWND(),                   // ������������� ������������� ����
		0,                   // ������������� ����
		hInstance,           // ������������� ����������
		NULL);    
}