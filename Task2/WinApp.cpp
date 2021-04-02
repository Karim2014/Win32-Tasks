#include "stdafx.h"
#include "WinApp.h"

WinApp::WinApp(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
	// сбрасываем флаг ошибки
	isErr = 0;
	// сохран€ем дескритор приложени€
	hInstance = hInst;
};

//–егистраци€ класса окна
BOOL WinApp::RegisterWndClass(LPCWSTR szClassName, WNDPROC WndProc) {
	ATOM aWndClass; // атом дл€ кода возврата
	WNDCLASS wc; // структура дл€ регистрации класса окна
	
	wc.style         = 0;
	wc.lpfnWndProc   = (WNDPROC) WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = szClassName;
	aWndClass = RegisterClass(&wc);
	return (aWndClass != 0);
	
};

// «апуск цикла обработки сообщений
WORD WinApp::Go(void)
{
  // «апускаем цикл обработки сообщений
  while(GetMessage(&msg, 0, 0, 0))
  {
    DispatchMessage(&msg);
  }
  return msg.wParam;
};