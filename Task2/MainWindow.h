#pragma once
#include "Window.h"

class MainWindow : public Window {
public:
	MainWindow(HINSTANCE hInstance, TCHAR* szClassName, TCHAR* szWindowTitle) : Window(hInstance, szClassName, szWindowTitle, WS_OVERLAPPED) {};
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};