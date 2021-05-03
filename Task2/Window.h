#pragma once
#include "stdafx.h"

class Window {
protected:
	int isErr; // ���� ������
	HWND hwnd; // ��������� ����
public:
	Window(HWND handle); // �-� ��-�����
	Window(HINSTANCE hInstance, TCHAR* className, TCHAR* wndTitle, int windowStyle);
	Window(HINSTANCE hInstance, TCHAR* className, TCHAR* windowTitle, int windowStyle, Window* hParentWnd);
	HWND getHWND() { return hwnd; }
	int Error(void) { return isErr; }
	// ����������� ����
	void Show(int nCmdShow) { ShowWindow(hwnd, nCmdShow); }
	// �������� ������� WndProc 
	void Update(void) { UpdateWindow(hwnd); }
};