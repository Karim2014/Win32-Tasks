#pragma once
#include "stdafx.h"

class Window {
protected:
	int isErr; // флаг ошибки
	HWND hwnd; // дескритор окна
public:
	Window(HINSTANCE, TCHAR*, TCHAR*, int);
	Window(HINSTANCE, TCHAR*, TCHAR*, int, HWND);
	int Error(void) { return isErr; }
	// Отображение окна
	void Show(int nCmdShow) { ShowWindow(hwnd, nCmdShow); }
	// Передача функции WndProc 
	void Update(void) { UpdateWindow(hwnd); }
	// прототип оконной фунгкции  
	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};