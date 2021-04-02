#include "StdAfx.h"
#include "PopupWindow.h"

LRESULT CALLBACK PopupWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
};
