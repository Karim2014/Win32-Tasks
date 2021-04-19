#include "stdafx.h"
#include "Window.h"
#include "WinApp.h"
#include "WndProc.h"

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

//VOID InitMainWnd(HINSTANCE hInstance, int nCmdShow) {
//	WNDCLASS wc;
//
//	ZeroMemory(&wc, sizeof(wc)); // Очистка полей структуры
//	// Заполнение полей стр-ры WNDCLASS
//	wc.lpszClassName = ClassName; // Имя класса окон
//	//Адрес оконной ф-ции
//	wc.lpfnWndProc = (WNDPROC) MainWndProc;
//	wc.style = CS_HREDRAW|CS_VREDRAW; // Стиль класса окон
//	wc.hInstance = hInstance; // Экземпляр приложения
//	// Пиктограмма для окон
//	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	// Курсор мыши для окон
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	// Кисть для окон
//	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
//	wc.lpszMenuName = NULL; // Ресурс меню окон
//	wc.cbClsExtra = 0; // Дополнительная память класса
//	wc.cbWndExtra = 0; // Дополнительная память окна
//	// Pегистрация класса окна.
//	BOOL k = RegisterClass(&wc);
//	if (!k) {
//		MessageBox(NULL, _T("Window create error"), AppTitle, MB_OK|MB_ICONSTOP);
//	}
//	// Создание главного окна приложения.
//	hMainWnd = CreateWindow(
//		ClassName, // Имя класса окон
//		AppTitle, // Заголовок окна
//		WS_OVERLAPPEDWINDOW, // Стиль окна
//		CW_USEDEFAULT, // X-координата
//		CW_USEDEFAULT, // Y-координата
//		CW_USEDEFAULT, // Ширина окна
//		CW_USEDEFAULT, // Высота окна
//		NULL, // Дескриптор окна-родителя
//		NULL, // Дескриптор меню окна
//		hInstance, // Дескриптор экз. приложения
//		NULL); // Дополнительная информация
//
//	if(!hMainWnd) {
//		// Окно не создано, выдается сообщение.
//		MessageBox(NULL, _T("Window create error"), AppTitle, MB_OK|MB_ICONSTOP);
//		return;
//	}
//	// Отображение окна и обновление его
//	ShowWindow(hMainWnd, nCmdShow);
//	UpdateWindow(hMainWnd);
//}
//
//VOID InitPopupWnd(HINSTANCE hInstance, int nCmdShow) {
//	WNDCLASS wc;
//	HWND hWndPopup;
//
//	// Заполнение структуры WNDCLASS для регистрации класса всплывающего окна.
//	memset(&wc, 0, sizeof(wc));
//	wc.lpszClassName = PopupClassName;			// Имя класса окон
//	wc.lpfnWndProc = (WNDPROC) PopupWndProc;			// Адрес оконной функции
//	wc.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;			// Стиль класса окон
//	wc.hInstance = hInstance;				// Экземпляр приложения
//	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);		// Пиктограмма для окон
//	wc.hCursor = LoadCursor(NULL,IDC_ARROW);			// Курсор мыши для окон
//	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);	// Кисть для окон
//	wc.lpszMenuName = NULL;					// Ресурс меню окон
//	wc.cbClsExtra = 0;					// Дополнительная память
//	wc.cbWndExtra = 0;					// Дополнительная память
//
//	// Pегистрация класса окна.
//	BOOL k = RegisterClass(&wc);
//
//	if (!k) {
//		MessageBox(NULL, _T("Window create error"), AppTitle, MB_OK|MB_ICONSTOP);
//	}
//
//	int rx = 1 + (rand() % (GetSystemMetrics(SM_CXSCREEN) - 300) - 1);
//	int ry = rand() % (GetSystemMetrics(SM_CYSCREEN) - 300) + 1;
//
//	// создание временного окна
//	hWndPopup = CreateWindow(
//		PopupClassName,					// Имя класса окна
//		_T("POPUPWINDOW"),						// Заголовок окна
//		WS_POPUPWINDOW|WS_CAPTION|WS_VISIBLE,// Стиль окна
//		rx, // X-координата
//		ry,// Y-координата
//		200,								// Ширина окна
//		GetSystemMetrics(SM_CYCAPTION) + 50,	// Высота окна   
//		hMainWnd,							// Дескриптор окна-родителя
//		NULL,								// Дескриптор меню окна
//		hInstance,							// Дескриптор экземпляра приложения
//		NULL);								// Дополнительная информация
//	if(hWndPopup == 0) { 
//		DestroyWindow(hMainWnd); 
//		return; 
//	}
//	ShowWindow(hWndPopup, nCmdShow); 
//	UpdateWindow(hWndPopup);
//}
//
//VOID InitChildWnd(HINSTANCE hInstance, int nCmdShow) {
//	WNDCLASS wc;
//	HWND hWndChild;
//
//	// Заполнение структуры WNDCLASS для регистрации класса дочернего окна.
//	memset(&wc, 0, sizeof(wc));
//	wc.lpszClassName = ChildClassName;			// Имя класса окон
//	wc.lpfnWndProc = (WNDPROC)ChildWndProc;			// Адрес оконной функции
//	wc.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;			// Стиль класса окон
//	wc.hInstance = hInstance;				// Экземпляр приложения
//	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);		// Пиктограмма для окон
//	wc.hCursor = LoadCursor(NULL,IDC_ARROW);			// Курсор мыши для окон
//	wc.hbrBackground = (HBRUSH)(COLOR_HIGHLIGHT);		// Кисть для окон
//	wc.lpszMenuName = NULL;					// Ресурс меню окон
//	wc.cbClsExtra = 0;					// Дополнительная память
//	wc.cbWndExtra = 0;					// Дополнительная память
//
//	// Pегистрация класса окна.
//	RegisterClass(&wc);
//
//	int width = GetSystemMetrics(SM_CXSCREEN)/16;
//	int height = GetSystemMetrics(SM_CYSCREEN)/16;
//
//	// создание дочернего окна
//	hWndChild = CreateWindow(
//		ChildClassName,
//		L"CHILDWINDOW",
//		WS_CHILDWINDOW|WS_CAPTION|WS_VISIBLE,
//		GetSystemMetrics(SM_CXSCREEN)/2 - width/2,// X-координата
//		GetSystemMetrics(SM_CYSCREEN)/2 - height/2 ,// Y-координата
//		width,
//		height, 
//		hMainWnd, 
//		NULL, 
//		hInstance,
//		NULL);
//
//	if(!hWndChild) { 
//		//MessageBox(hMainWnd, L"Ты дэбил", L"Ошибка", MB_HELP);
//		DestroyWindow(hMainWnd); 
//		return; 
//	} 
//	ShowWindow(hWndChild, nCmdShow); 
//	UpdateWindow(hWndChild);
//}
//
//// --- Оконная функция главного окна
//LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//	switch(uMsg) {
//		// Нажата левая кнопка мыши в клиентской обл. окна.
//	case WM_LBUTTONDOWN:
//		// Вывод информации о приложении с помощью
//		// диалогового окна сообщений MessageBox()
//		FLASHWINFO  fi;
//		fi.cbSize = sizeof(FLASHWINFO);
//		fi.hwnd = hWnd;
//		fi.dwFlags = FLASHW_ALL;
//		fi.uCount = 4;
//		fi.dwTimeout = 0;
//		FlashWindowEx(&fi);			
//		ShowWindow(hWnd, SW_MINIMIZE);
//		//MessageBox(hWnd, _T("Windows Aplication"), _T("MainWindowMessage"), MB_OK|MB_ICONINFORMATION);
//		break;
//		// Пользователь удалил окно
//	case WM_RBUTTONDOWN:
//		Beep(2500, 1000);
//		//MessageBox(hWnd, _T("Windows Aplication"), _T("MainWindowMessage"), MB_OK|MB_ICONINFORMATION);
//		break;
//	case WM_DESTROY:
//		// Если это оконная функция главного окна, то в очередь
//		// сообщений посылается сообщение WM_QUIT
//		PostQuitMessage(0);
//		break;
//		// Необработанные сообщения возвращаются в
//		// ОС с помощью функции DefWindowProc()
//	default:
//		return DefWindowProc(hWnd, uMsg, wParam, lParam);
//	}
//	return 0;
//}
//
//WORD GetWindowWidth(HWND hwnd) {
//	RECT rect;
//	GetWindowRect(hwnd, &rect);
//	return rect.right - rect.left;
//}
//
//WORD GetWindowHeight(HWND hwnd) {
//	RECT rect;
//	GetWindowRect(hwnd, &rect);
//	return rect.bottom - rect.top;
//}
//
//LRESULT CALLBACK PopupWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//	switch(uMsg) {
//		// Нажата левая кнопка мыши в клиентской обл. окна.
//	case WM_LBUTTONDBLCLK:
//		MessageBox(hMainWnd, L"Данное окно является всплывающим. При двойном нажатии правой кнопкой окно центрируется по позиции курсора", L"Информация", MB_OK | MB_ICONINFORMATION );
//		break;
//		// Пользователь удалил окно
//	case WM_RBUTTONDBLCLK:
//		WORD xPos, yPos, newX, newY, width, height;
//		// Сохраняем координаты курсора мыши
//		POINT pt;
//		GetCursorPos(&pt);
//		xPos = pt.x;
//		yPos = pt.y;
//		width = GetWindowWidth(hWnd);
//		height = GetWindowHeight(hWnd);
//		newX = xPos - width / 2;
//		newY = yPos - height / 2 - GetSystemMetrics(SM_CYCAPTION) / 2;
//
//		MoveWindow(hWnd, newX, newY, width, height, FALSE);
//		break;
//	case WM_DESTROY:
//		// Если это оконная функция главного окна, то в очередь
//		// сообщений посылается сообщение WM_QUIT
//		//PostQuitMessage(0);
//		break;
//		// Необработанные сообщения возвращаются в
//		// ОС с помощью функции DefWindowProc()
//	default:
//		return DefWindowProc(hWnd, uMsg, wParam, lParam);
//	}
//	return 0;
//}
//
//
//
//LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//	switch(uMsg) {
//		// Нажата левая кнопка мыши в клиентской обл. окна.
//	case WM_LBUTTONDOWN:
//		WORD MWH, width, height, newY, newX;
//		MWH = GetWindowHeight(hMainWnd);
//		width = GetWindowWidth(hWnd);
//		height = GetWindowHeight(hWnd);
//		newY = MWH - width;
//		MoveWindow(hWnd, 0, newY, width, height, true);
//		break;
//		// Пользователь удалил окно
//	case WM_RBUTTONDOWN:
//		width = GetWindowWidth(hWnd);
//		height = GetWindowHeight(hWnd);
//		newX = GetSystemMetrics(SM_CXSCREEN)/2 - width/2,// X-координата
//			newY = GetSystemMetrics(SM_CYSCREEN)/2 - height/2 ,// Y-координата
//			MoveWindow(hWnd, newX, newY, width, height, true);			
//		break;
//	case WM_DESTROY:
//		// Если это оконная функция главного окна, то в очередь
//		// сообщений посылается сообщение WM_QUIT
//		PostQuitMessage(0);
//		break;
//		// Необработанные сообщения возвращаются в
//		// ОС с помощью функции DefWindowProc()
//	default:
//		return DefWindowProc(hWnd, uMsg, wParam, lParam);
//	}
//}