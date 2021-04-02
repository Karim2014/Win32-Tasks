#include "stdafx.h"
#include "Window.h"

Window::Window(HINSTANCE hInstance, TCHAR* szClassName, TCHAR* szWindowTitle, int windowStyle) {
	// Сбрасываем флаг ошибки
	isErr = 0;
	// Создаем окно
	hwnd = CreateWindow(
		szClassName,         // имя класса окна
		szWindowTitle,       // заголовок окна
		windowStyle, // стиль окна
		CW_USEDEFAULT,       // задаем размеры и расположение
		CW_USEDEFAULT,       // окна, принятые по умолчанию 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,                   // идентификатор родительского окна
		0,                   // идентификатор меню
		hInstance,           // идентификатор приложения
		NULL);               // указатель на дополнительные параметры
	// Если при создании окна были ошибки,
	// устанавливаем флаг ошибки
	if(!hwnd) {  
		isErr = 1;
		return;
	}
}

Window::Window(HINSTANCE hInstance, TCHAR* szClassName, TCHAR* szWindowTitle, int windowStyle, HWND hParentWnd) {
	
	// Сбрасываем флаг ошибки
	isErr = 0;
	// Создаем окно
	hwnd = CreateWindow(
		szClassName,         // имя класса окна
		szWindowTitle,       // заголовок окна
		windowStyle, // стиль окна
		CW_USEDEFAULT,       // задаем размеры и расположение
		CW_USEDEFAULT,       // окна, принятые по умолчанию 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		hParentWnd,                   // идентификатор родительского окна
		0,                   // идентификатор меню
		hInstance,           // идентификатор приложения
		NULL);               // указатель на дополнительные
	// параметры
	// Если при создании окна были ошибки,
	// устанавливаем флаг ошибки
	if(!hwnd) {  
		isErr = 1;
		return;
	}
}