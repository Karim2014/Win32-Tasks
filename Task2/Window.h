#pragma once
#include "stdafx.h"

class Window {
protected:
	int isErr; // ���� ������
	HWND hwnd; // ��������� ����
public:
	Window(HINSTANCE, TCHAR*, TCHAR*, int);
	Window(HINSTANCE, TCHAR*, TCHAR*, int, HWND);
	int Error(void) { return isErr; }
	// ����������� ����
	void Show(int nCmdShow) { ShowWindow(hwnd, nCmdShow); }
	// �������� ������� WndProc 
	void Update(void) { UpdateWindow(hwnd); }
	// �������� ������� ��������  
	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};