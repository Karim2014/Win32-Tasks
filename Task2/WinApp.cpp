#include "stdafx.h"
#include "WinApp.h"

WinApp::WinApp(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
	// сбрасываем флаг ошибки
	isErr = 0;
	// сохраняем дескритор приложения
	hInstance = hInst;
};

//Регистрация класса окна
BOOL WinApp::RegisterWndClass(LPCWSTR szClassName, WNDPROC WndProc) {
	ATOM aWndClass; // атом для кода возврата
	WNDCLASS wc; // структура для регистрации класса окна

	wc.style         = CS_HREDRAW|CS_VREDRAW;
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
	if (!aWndClass) {
		MessageBox(NULL, _T("Window create error"), szClassName, MB_OK|MB_ICONSTOP);
	}
	return (aWndClass != 0);
	
};

// Запуск цикла обработки сообщений
WORD WinApp::Go() {
	// Запускаем цикл обработки сообщений
	while(GetMessage(&msg, 0, 0, 0)) {
		// Преобразов. сообщ., получ с помощью клавиатуры
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
};