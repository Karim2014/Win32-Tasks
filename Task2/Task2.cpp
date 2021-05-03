#include "stdafx.h"
#include "Window.h"
#include "WinApp.h"
#include "WndProc.h"

/*
Функции обработки событий для окон
*/
HWND CreateMainWindow();
HWND CreateChildWindow(Window* parent);
HWND CreatePopupWindow(Window* parent);

// --- Объявление глобальных переменных
TCHAR* ClassName = _T("WindowClass"); // Название класса окна
TCHAR* PopupClassName = _T("PopupWindow");
TCHAR* ChildClassName = _T("ChildWwindow");

TCHAR* AppTitle = _T("Главное окно"); // Заголовок главн. окна

HINSTANCE hInstance;

// --- Главная функция приложения WinMain
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Указатель на объект класса Window - главное окно приложения
	Window* pMainWindow;
	Window* pPopupWindow;
	Window* pChildWindow;

	HWND hMainWnd;
	// --- Проверка, было ли приложение запущено ранее
	if((hMainWnd = FindWindow(ClassName, NULL)) != NULL) {
		// Если прилож. было запущено ранее, активизировать
		// и выдвинуть на передний план его главное окно
		if (MessageBox(hMainWnd, L"Экземпляр программы уже запущен! Продолжить работу с программой?", 
			L"Внимание!", MB_YESNO | MB_ICONEXCLAMATION|MB_TASKMODAL) != IDYES) {
				DestroyWindow(hMainWnd);
				return FALSE;
		}
		if(IsIconic(hMainWnd))
			ShowWindow(hMainWnd, SW_RESTORE);
		SetForegroundWindow(hMainWnd);
		// Работа новой копии прекращается
		return FALSE;
	}

	// Создаем объект класса WinApp - наше приложение
	WinApp App(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	// регистрируем окна
	App.RegisterWndClass(ClassName, MainWndProc);
	App.RegisterWndClass(PopupClassName, PopupWndProc);
	App.RegisterWndClass(ChildClassName, ChildWndProc);
	if(App.Error()) return App.Error();
	// создаем окна
	pMainWindow = new Window(CreateMainWindow());
	pPopupWindow = new Window(CreatePopupWindow(pMainWindow));
	pChildWindow = new Window(CreateChildWindow(pMainWindow));		
	// Проверяем ошибки, которые могли возникнуть при создании окон
	if(pMainWindow->Error()) pMainWindow->Error();
	if(pChildWindow->Error()) pChildWindow->Error();
	if(pPopupWindow->Error()) pPopupWindow->Error();
	// Отображаем окно
	pMainWindow->Show(SW_SHOWMAXIMIZED);
	pChildWindow->Show(nCmdShow);
	pPopupWindow->Show(nCmdShow);
	// Посылаем в окна сообщения
	pMainWindow->Update();
	pChildWindow->Update();
	pPopupWindow->Update();
	// запускаем приложение
	App.Go();
	// завершаем работу
	return App.Error();
}

HWND CreateMainWindow() {
	return CreateWindow(
		ClassName,         // имя класса окна
		AppTitle,       // заголовок окна
		WS_OVERLAPPEDWINDOW, // стиль окна
		CW_USEDEFAULT,       // задаем размеры и расположение
		CW_USEDEFAULT,       // окна, принятые по умолчанию 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,                   // идентификатор родительского окна
		0,                   // идентификатор меню
		hInstance,           // идентификатор приложения
		NULL);     
}

HWND CreateChildWindow(Window* parent) {
	return CreateWindow(
		ChildClassName,         // имя класса окна
		L"Дочернее окно",       // заголовок окна
		WS_CHILDWINDOW|WS_CAPTION|WS_VISIBLE, // стиль окна
		150,       // задаем размеры и расположение
		150,       // окна, принятые по умолчанию 
		250,
		250,
		parent->getHWND(),                   // идентификатор родительского окна
		0,                   // идентификатор меню
		hInstance,           // идентификатор приложения
		NULL);    
}

HWND CreatePopupWindow(Window* parent) {
	return CreateWindow(
		PopupClassName,         // имя класса окна
		L"Временное окно",       // заголовок окна
		WS_POPUPWINDOW|WS_CAPTION|WS_VISIBLE, // стиль окна
		300,       // задаем размеры и расположение
		100,       // окна, принятые по умолчанию 
		300,
		300,
		parent->getHWND(),                   // идентификатор родительского окна
		0,                   // идентификатор меню
		hInstance,           // идентификатор приложения
		NULL);    
}