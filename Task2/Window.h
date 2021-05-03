#pragma once
#include "stdafx.h"

class Window {
protected:
	int isErr; // флаг ошибки
	HWND hwnd; // дескритор окна
public:
	Window(HWND handle); // к-р по-умолч
	Window(HINSTANCE hInstance, TCHAR* className, TCHAR* wndTitle, int windowStyle);
	Window(HINSTANCE hInstance, TCHAR* className, TCHAR* windowTitle, int windowStyle, Window* hParentWnd);
	HWND getHWND() { return hwnd; }
	int Error(void) { return isErr; }
	// Отображение окна
	void Show(int nCmdShow) { ShowWindow(hwnd, nCmdShow); }
	// Передача функции WndProc 
	void Update(void) { UpdateWindow(hwnd); }
};