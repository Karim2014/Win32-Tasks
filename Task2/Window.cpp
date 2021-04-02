#include "stdafx.h"
#include "Window.h"

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

Window::Window(HINSTANCE hInstance, TCHAR* szClassName, TCHAR* szWindowTitle, int windowStyle, HWND hParentWnd) {
	
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
		hParentWnd,                   // ������������� ������������� ����
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