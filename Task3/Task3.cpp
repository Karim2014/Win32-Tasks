// Task3.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Task3.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szMainTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szMainWindowClass[MAX_LOADSTRING];			// имя класса главного окна
TCHAR szPopupTitle[MAX_LOADSTRING]; // текст строки заголовка временного окна
TCHAR szPopupWindowClass[MAX_LOADSTRING]; // имя класса временного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				RegisterMainClass(HINSTANCE hInstance);
ATOM				RegisterPopupClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
VOID				czCreateMainMenu(HWND hwnd);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcPopup(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szMainTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDS_POPUP_TITLE, szPopupTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TASK3, szMainWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDC_POPUP, szPopupWindowClass, MAX_LOADSTRING);
	RegisterMainClass(hInstance);
	RegisterPopupClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TASK3));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: RegisterMainClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
//  КОММЕНТАРИИ:
//
//    Эта функция и ее использование необходимы только в случае, если нужно, чтобы данный код
//    был совместим с системами Win32, не имеющими функции RegisterClassEx'
//    которая была добавлена в Windows 95. Вызов этой функции важен для того,
//    чтобы приложение получило "качественные" мелкие значки и установило связь
//    с ними.
//
ATOM RegisterMainClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TASK3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_TASK3);
	wcex.lpszClassName	= szMainWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//  ФУНКЦИЯ: RegisterPopupClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс временного окна.
//
ATOM RegisterPopupClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProcPopup;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TASK3)); // todo
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW); // todo
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_POPUP);
	wcex.lpszClassName	= szPopupWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // todo

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWndMain, hWndPopup;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   // создаем главное окно
   hWndMain = CreateWindow(szMainWindowClass, szMainTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   // если главное окно не создано - закончить
   if (!hWndMain) {
	   // todo добавить диалог об ошибке
	   return FALSE;
   }
   // создаем временное окно
   hWndPopup = CreateWindow(szPopupWindowClass, szPopupTitle, WS_POPUPWINDOW | WS_VISIBLE | WS_CAPTION, 
	   300, 100, 400, 300, hWndMain, NULL, hInstance, NULL);
   if (!hWndPopup) {
	   // todo добавить диалог об ошибке
	   MessageBox(NULL, L"Ошибка создания дочернего окна", L"Ошибка", MB_OK | MB_ICONERROR);
	   return FALSE;
   }
   
   czCreateMainMenu(hWndMain);

   ShowWindow(hWndMain, SW_MAXIMIZE);
   UpdateWindow(hWndMain);
   ShowWindow(hWndPopup, nCmdShow);
   UpdateWindow(hWndPopup);

   return TRUE;
}

// функция дл создания меню главного окна
VOID czCreateMainMenu(HWND hwnd) {
	HMENU hMenu				= CreateMenu();
	HMENU hPopupMenuMove	= CreatePopupMenu();
	HMENU hPopupMenuParam	= CreatePopupMenu();

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) hPopupMenuMove, L"&Движение объекта");
	{
		AppendMenu(hPopupMenuMove, MF_STRING, IDM_MOVE_STOP, L"Ос&тановить");
		AppendMenu(hPopupMenuMove, MF_STRING, IDM_MOVE_RESET, L"&Возобновить");
	}
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) hPopupMenuParam, L"&Параметры объекта");
	{
		AppendMenu(hPopupMenuParam, MF_STRING, IDM_PARAM_RESET, L"&Задать исходные");
		AppendMenu(hPopupMenuParam, MF_STRING, IDM_PARAM_CHANGE, L"&Изменить в диалоге");
	}
	AppendMenu(hMenu, MF_STRING, IDM_ABOUT, L"&О программе");
	AppendMenu(hMenu, MF_STRING, IDM_EXIT, L"В&ыход");
	SetMenu(hwnd, hMenu);
}

HMENU PrepareContextMenu() {
	HMENU hMenu				= CreatePopupMenu();
	HMENU hPopupMenuMove	= CreatePopupMenu();
	HMENU hPopupMenuParam	= CreatePopupMenu();

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) hPopupMenuMove, L"&Размеры объекта");
	{
		AppendMenu(hPopupMenuMove, MF_STRING, IDM_SIZE_INC, L"У&величить в 1,2 раза");
		AppendMenu(hPopupMenuMove, MF_STRING, IDM_SIZE_DEC, L"У&меньшить в 1,2 раза");
		AppendMenu(hPopupMenuMove, MF_STRING, IDM_SIZE_RESET, L"&Задать исходные");
	}
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) hPopupMenuParam, L"В&ременной интервал");
	{
		AppendMenu(hPopupMenuParam, MF_STRING, IDM_TIME_INC, L"У&величить в 1,5 раза");
		AppendMenu(hPopupMenuParam, MF_STRING, IDM_TIME_DEC, L"У&меньшить в 1,5 раза");
		AppendMenu(hPopupMenuParam, MF_STRING, IDM_TIME_RESET, L"&Задать исходные");
	}
	AppendMenu(hMenu, MF_STRING, IDM_EXIT, L"За&крыть окно");
	return hMenu;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: добавьте любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// обработчик сообщений для временного окна
LRESULT CALLBACK WndProcPopup(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HMENU hMenu;
	switch(message) {
	case WM_CONTEXTMENU:
		hMenu = PrepareContextMenu();
		TrackPopupMenu(hMenu, TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN,
			LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
		DestroyMenu(hMenu);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
