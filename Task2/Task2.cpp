#include "stdafx.h"
// --- Прототип оконной функции главного окна
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK PopupWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

VOID InitMainWnd(HINSTANCE, int);
VOID InitPopupWnd(HINSTANCE, int);
VOID InitChildWnd(HINSTANCE, int);

// --- Объявление глобальных переменных
HINSTANCE hInst; // Дескриптор экземпляра приложения
TCHAR* ClassName = _T("WindowClass"); // Название класса окна
TCHAR* PopupClassName = _T("PopupWindow");
TCHAR* ChildClassName = _T("ChildWwindow");

TCHAR* AppTitle = _T("Задание №2 по ОС ст. Сабитова К.А. гр. ИСзск-19"); // Заголовок главн. окна

HWND hMainWnd; // дескритор главного окна

// --- Главная функция приложения WinMain
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg; // Структура для хранения сообщения

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

	hInst = hInstance; // Сохран. дескриптора экз. прилож.

	srand(time(0));

	InitMainWnd(hInst, SW_SHOWMAXIMIZED); // SW_SHOWMAXIMIZED - показать окно на весь экран
	InitPopupWnd(hInst, nCmdShow);
	InitChildWnd(hInst, nCmdShow);

	// Запуск цикла обработки очереди сообщений.
	while(GetMessage(&msg, NULL, 0, 0))
	{
		// Преобразов. сообщений клавиатуры в символьные
		TranslateMessage(&msg);
		// Отправление сообщения оконной функции
		DispatchMessage(&msg);
	}
	return msg.wParam; // Завершение работы приложения
}

VOID InitMainWnd(HINSTANCE hInstance, int nCmdShow) {
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(wc)); // Очистка полей структуры
	// Заполнение полей стр-ры WNDCLASS
	wc.lpszClassName = ClassName; // Имя класса окон
	//Адрес оконной ф-ции
	wc.lpfnWndProc = (WNDPROC) MainWndProc;
	wc.style = CS_HREDRAW|CS_VREDRAW; // Стиль класса окон
	wc.hInstance = hInstance; // Экземпляр приложения
	// Пиктограмма для окон
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// Курсор мыши для окон
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	// Кисть для окон
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL; // Ресурс меню окон
	wc.cbClsExtra = 0; // Дополнительная память класса
	wc.cbWndExtra = 0; // Дополнительная память окна
	// Pегистрация класса окна.
	BOOL k = RegisterClass(&wc);
	if (!k) {
		MessageBox(NULL, _T("Window create error"), AppTitle, MB_OK|MB_ICONSTOP);
	}
	// Создание главного окна приложения.
	hMainWnd = CreateWindow(
		ClassName, // Имя класса окон
		AppTitle, // Заголовок окна
		WS_OVERLAPPEDWINDOW, // Стиль окна
		CW_USEDEFAULT, // X-координата
		CW_USEDEFAULT, // Y-координата
		CW_USEDEFAULT, // Ширина окна
		CW_USEDEFAULT, // Высота окна
		NULL, // Дескриптор окна-родителя
		NULL, // Дескриптор меню окна
		hInstance, // Дескриптор экз. приложения
		NULL); // Дополнительная информация

	if(!hMainWnd) {
		// Окно не создано, выдается сообщение.
		MessageBox(NULL, _T("Window create error"), AppTitle, MB_OK|MB_ICONSTOP);
		return;
	}
	// Отображение окна и обновление его
	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);
}

VOID InitPopupWnd(HINSTANCE hInstance, int nCmdShow) {
	WNDCLASS wc;
	HWND hWndPopup;

	// Заполнение структуры WNDCLASS для регистрации класса всплывающего окна.
	memset(&wc, 0, sizeof(wc));
	wc.lpszClassName = PopupClassName;			// Имя класса окон
	wc.lpfnWndProc = (WNDPROC) PopupWndProc;			// Адрес оконной функции
	wc.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;			// Стиль класса окон
	wc.hInstance = hInstance;				// Экземпляр приложения
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);		// Пиктограмма для окон
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);			// Курсор мыши для окон
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);	// Кисть для окон
	wc.lpszMenuName = NULL;					// Ресурс меню окон
	wc.cbClsExtra = 0;					// Дополнительная память
	wc.cbWndExtra = 0;					// Дополнительная память

	// Pегистрация класса окна.
	BOOL k = RegisterClass(&wc);

	if (!k) {
		MessageBox(NULL, _T("Window create error"), AppTitle, MB_OK|MB_ICONSTOP);
	}

	int rx = 1 + (rand() % (GetSystemMetrics(SM_CXSCREEN) - 300) - 1);
	int ry = rand() % (GetSystemMetrics(SM_CYSCREEN) - 300) + 1;

	// создание временного окна
 	hWndPopup = CreateWindow(
		PopupClassName,					// Имя класса окна
		_T("POPUPWINDOW"),						// Заголовок окна
		WS_POPUPWINDOW|WS_CAPTION|WS_VISIBLE,// Стиль окна
		rx, // X-координата
		ry,// Y-координата
		200,								// Ширина окна
		GetSystemMetrics(SM_CYCAPTION) + 50,	// Высота окна   
    	hMainWnd,							// Дескриптор окна-родителя
		NULL,								// Дескриптор меню окна
		hInstance,							// Дескриптор экземпляра приложения
		NULL);								// Дополнительная информация
 	if(hWndPopup == 0) { 
		DestroyWindow(hMainWnd); 
		return; 
 	}
 	ShowWindow(hWndPopup, nCmdShow); 
 	UpdateWindow(hWndPopup);
}

VOID InitChildWnd(HINSTANCE hInstance, int nCmdShow) {
	WNDCLASS wc;
	HWND hWndChild;

	// Заполнение структуры WNDCLASS для регистрации класса дочернего окна.
	memset(&wc, 0, sizeof(wc));
	wc.lpszClassName = ChildClassName;			// Имя класса окон
	wc.lpfnWndProc = (WNDPROC)ChildWndProc;			// Адрес оконной функции
	wc.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;			// Стиль класса окон
	wc.hInstance = hInstance;				// Экземпляр приложения
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);		// Пиктограмма для окон
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);			// Курсор мыши для окон
	wc.hbrBackground = (HBRUSH)(COLOR_HIGHLIGHT);		// Кисть для окон
	wc.lpszMenuName = NULL;					// Ресурс меню окон
	wc.cbClsExtra = 0;					// Дополнительная память
	wc.cbWndExtra = 0;					// Дополнительная память

	// Pегистрация класса окна.
	RegisterClass(&wc);

	int width = GetSystemMetrics(SM_CXSCREEN)/16;
	int height = GetSystemMetrics(SM_CYSCREEN)/16;

	// создание дочернего окна
 	hWndChild = CreateWindow(
		ChildClassName,
		L"CHILDWINDOW",
		WS_CHILDWINDOW|WS_CAPTION|WS_VISIBLE,
		GetSystemMetrics(SM_CXSCREEN)/2 - width/2,// X-координата
		GetSystemMetrics(SM_CYSCREEN)/2 - height/2 ,// Y-координата
		width,
		height, 
		hMainWnd, 
		NULL, 
		hInstance,
		NULL);

 	if(!hWndChild) { 
		//MessageBox(hMainWnd, L"Ты дэбил", L"Ошибка", MB_HELP);
		DestroyWindow(hMainWnd); 
      	return; 
    } 
 	ShowWindow(hWndChild, nCmdShow); 
 	UpdateWindow(hWndChild);
}

// --- Оконная функция главного окна
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
		// Нажата левая кнопка мыши в клиентской обл. окна.
		case WM_LBUTTONDOWN:
			// Вывод информации о приложении с помощью
			// диалогового окна сообщений MessageBox()
			FLASHWINFO  fi;
			fi.cbSize = sizeof(FLASHWINFO);
			fi.hwnd = hWnd;
			fi.dwFlags = FLASHW_ALL;
			fi.uCount = 4;
			fi.dwTimeout = 0;
			FlashWindowEx(&fi);			
			ShowWindow(hWnd, SW_MINIMIZE);
			//MessageBox(hWnd, _T("Windows Aplication"), _T("MainWindowMessage"), MB_OK|MB_ICONINFORMATION);
			break;
		// Пользователь удалил окно
		case WM_RBUTTONDOWN:
			Beep(2500, 1000);
			//MessageBox(hWnd, _T("Windows Aplication"), _T("MainWindowMessage"), MB_OK|MB_ICONINFORMATION);
			break;
		case WM_DESTROY:
			// Если это оконная функция главного окна, то в очередь
			// сообщений посылается сообщение WM_QUIT
			PostQuitMessage(0);
			break;
		// Необработанные сообщения возвращаются в
		// ОС с помощью функции DefWindowProc()
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

WORD GetWindowWidth(HWND hwnd) {
	RECT rect;
	GetWindowRect(hwnd, &rect);
	return rect.right - rect.left;
}

WORD GetWindowHeight(HWND hwnd) {
	RECT rect;
	GetWindowRect(hwnd, &rect);
	return rect.bottom - rect.top;
}

LRESULT CALLBACK PopupWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
		// Нажата левая кнопка мыши в клиентской обл. окна.
	case WM_LBUTTONDBLCLK:
			MessageBox(hMainWnd, L"Данное окно является всплывающим. При двойном нажатии правой кнопкой окно центрируется по позиции курсора", L"Информация", MB_OK | MB_ICONINFORMATION );
			break;
		// Пользователь удалил окно
		case WM_RBUTTONDBLCLK:
			WORD xPos, yPos, newX, newY, width, height;
			// Сохраняем координаты курсора мыши
			POINT pt;
			GetCursorPos(&pt);
			xPos = pt.x;
			yPos = pt.y;
			width = GetWindowWidth(hWnd);
			height = GetWindowHeight(hWnd);
			newX = xPos - width / 2;
			newY = yPos - height / 2 - GetSystemMetrics(SM_CYCAPTION) / 2;
		
			MoveWindow(hWnd, newX, newY, width, height, FALSE);
			break;
		case WM_DESTROY:
			// Если это оконная функция главного окна, то в очередь
			// сообщений посылается сообщение WM_QUIT
			//PostQuitMessage(0);
			break;
		// Необработанные сообщения возвращаются в
		// ОС с помощью функции DefWindowProc()
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}



LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
		// Нажата левая кнопка мыши в клиентской обл. окна.
		case WM_LBUTTONDOWN:
			WORD MWH, width, height, newY, newX;
			MWH = GetWindowHeight(hMainWnd);
			width = GetWindowWidth(hWnd);
			height = GetWindowHeight(hWnd);
			newY = MWH - width;
			MoveWindow(hWnd, 0, newY, width, height, true);
			break;
		// Пользователь удалил окно
		case WM_RBUTTONDOWN:
			width = GetWindowWidth(hWnd);
			height = GetWindowHeight(hWnd);
			newX = GetSystemMetrics(SM_CXSCREEN)/2 - width/2,// X-координата
			newY = GetSystemMetrics(SM_CYSCREEN)/2 - height/2 ,// Y-координата
			MoveWindow(hWnd, newX, newY, width, height, true);			
			break;
		case WM_DESTROY:
			// Если это оконная функция главного окна, то в очередь
			// сообщений посылается сообщение WM_QUIT
			PostQuitMessage(0);
			break;
		// Необработанные сообщения возвращаются в
		// ОС с помощью функции DefWindowProc()
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}