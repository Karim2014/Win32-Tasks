#pragma once
#include "stdafx.h"

class WinApp {
	MSG msg; // ��������� ��� ������ � �����������
	int isErr; // ���� ������
	HINSTANCE hInstance; // ������������� ����������
	
public:
	// �-�
	WinApp(HINSTANCE, HINSTANCE, LPSTR, int);
	// ����������� ������ ����
	BOOL RegisterWndClass(LPCWSTR, WNDPROC);
	// ������ ����� ��������� ���������
	WORD Go(void);
	// �������� ����� ������
	int  Error(void) { return errno; }
};