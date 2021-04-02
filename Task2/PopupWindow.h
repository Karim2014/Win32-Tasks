#pragma once
#include "Window.h"

class PopupWindow : public Window {
public:
	PopupWindow(HINSTANCE hInstance, TCHAR* szClassName, TCHAR* szWindowTitle, HWND hMainWnd) : Window(hInstance, szClassName, szWindowTitle, WS_OVERLAPPED, hMainWnd) {};
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

