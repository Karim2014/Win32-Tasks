#pragma once
#include "window.h"

class ChildWindow : public Window {
public:
	ChildWindow(HINSTANCE hInstance, TCHAR* szClassName, TCHAR* szWindowTitle, Window* hMainWnd) : Window(hInstance, szClassName, szWindowTitle, WS_OVERLAPPED, hMainWnd) {};
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

