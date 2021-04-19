#include "stdafx.h"
#include "Window.h"

Window::Window(HWND handle) {
	isErr = 0;
	hwnd = handle;
	isErr = !hwnd ? 1 : 0;
}

Window::Window(HINSTANCE hInstance, TCHAR* szClassName, TCHAR* szWindowTitle, int windowStyle) {
	// ���������� ���� ������
	isErr = 0;
	// ������� ����
	hwnd = CreateWindow(
		szClassName,         // ��� ������ ����
		szWindowTitle,       // ��������� ����
		windowStyle, // ����� ����
		CW_USEDEFAULT,       // ������ ������� � ������������
		CW_USEDEFAULT,       // ����, �������� �� ��������� 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,                   // ������������� ������������� ����
		0,                   // ������������� ����
		hInstance,           // ������������� ����������
		NULL);               // ��������� �� �������������� ���������
	// ���� ��� �������� ���� ���� ������,
	// ������������� ���� ������
	if(!hwnd) {  
		isErr = 1;
		return;
	}
}

Window::Window(HINSTANCE hInstance, TCHAR* szClassName, TCHAR* szWindowTitle, int windowStyle, Window* hParentWnd) {
	
	// ���������� ���� ������
	isErr = 0;
	// ������� ����
	hwnd = CreateWindow(
		szClassName,         // ��� ������ ����
		szWindowTitle,       // ��������� ����
		windowStyle, // ����� ����
		CW_USEDEFAULT,       // ������ ������� � ������������
		CW_USEDEFAULT,       // ����, �������� �� ��������� 
		100,
		200,
		hParentWnd->hwnd,                   // ������������� ������������� ����
		0,                   // ������������� ����
		hInstance,           // ������������� ����������
		NULL);               // ��������� �� ��������������
	// ���������
	// ���� ��� �������� ���� ���� ������,
	// ������������� ���� ������
	if(!hwnd) {  
		isErr = 1;
		return;
	}
}