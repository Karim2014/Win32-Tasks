#include "StdAfx.h"
#include "ChildWindow.h"

LRESULT CALLBACK ChildWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
};

