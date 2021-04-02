#pragma once
#include "stdafx.h"

class WinApp {
	MSG msg; // структура для работы с сообщениями
	int isErr; // флаг ошибки
	HINSTANCE hInstance; // Идентификатор приложения
	
public:
	// К-р
	WinApp(HINSTANCE, HINSTANCE, LPSTR, int);
	// Регистрация класса окна
	BOOL RegisterWndClass(LPCWSTR, WNDPROC);
	// Запуск цикла обработки сообщений
	WORD Go(void);
	// Проверка флага ошибок
	int  Error(void) { return errno; }
};