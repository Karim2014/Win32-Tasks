// Task3.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "Task3.h"

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szMainTitle[MAX_LOADSTRING];					// ����� ������ ���������
TCHAR szMainWindowClass[MAX_LOADSTRING];			// ��� ������ �������� ����
TCHAR szPopupTitle[MAX_LOADSTRING]; // ����� ������ ��������� ���������� ����
TCHAR szPopupWindowClass[MAX_LOADSTRING]; // ��� ������ ���������� ����

// ��������� ���������� �������, ���������� � ���� ������ ����:
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

 	// TODO: ���������� ��� �����.
	MSG msg;
	HACCEL hAccelTable;
	srand(time(0));

	// ������������� ���������� �����
	LoadString(hInstance, IDS_APP_TITLE, szMainTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDS_POPUP_TITLE, szPopupTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TASK3, szMainWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDC_POPUP, szPopupWindowClass, MAX_LOADSTRING);

	HWND hMainWnd;
	// --- ��������, ���� �� ���������� �������� �����
	if((hMainWnd = FindWindow(szMainWindowClass, NULL)) != NULL) {
		// ���� ������. ���� �������� �����, ��������������
		// � ��������� �� �������� ���� ��� ������� ����
		if (MessageBox(hMainWnd, L"��������� ��������� ��� �������! ���������� ������ � ����������?", 
			L"��������!", MB_YESNO | MB_ICONEXCLAMATION|MB_TASKMODAL) != IDYES) {
				DestroyWindow(hMainWnd);
				return FALSE;
		}
		if(IsIconic(hMainWnd))
			ShowWindow(hMainWnd, SW_RESTORE);
		SetForegroundWindow(hMainWnd);
		// ������ ����� ����� ������������
		return FALSE;
	}

	RegisterMainClass(hInstance);
	RegisterPopupClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TASK3));

	// ���� ��������� ���������:
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
//  �������: RegisterMainClass()
//
//  ����������: ������������ ����� ����.
//
//  �����������:
//
//    ��� ������� � �� ������������� ���������� ������ � ������, ���� �����, ����� ������ ���
//    ��� ��������� � ��������� Win32, �� �������� ������� RegisterClassEx'
//    ������� ���� ��������� � Windows 95. ����� ���� ������� ����� ��� ����,
//    ����� ���������� �������� "������������" ������ ������ � ���������� �����
//    � ����.
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
	wcex.hCursor		= LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_TASK3);
	wcex.lpszClassName	= szMainWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//  �������: RegisterPopupClass()
//
//  ����������: ������������ ����� ���������� ����.
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POPUP)); // todo
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW); // todo
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_POPUP);
	wcex.lpszClassName	= szPopupWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_POPUP)); // todo

	return RegisterClassEx(&wcex);
}

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWndMain, hWndPopup;

   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   // ������� ������� ����
   hWndMain = CreateWindow(szMainWindowClass, szMainTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   // ���� ������� ���� �� ������� - ���������
   if (!hWndMain) {
	   // todo �������� ������ �� ������
	   return FALSE;
   }
   // ������� ��������� ����
   hWndPopup = CreateWindow(szPopupWindowClass, szPopupTitle, WS_POPUPWINDOW | WS_VISIBLE | WS_CAPTION, 
	   300, 100, 400, 300, hWndMain, NULL, hInstance, NULL);
   if (!hWndPopup) {
	   // todo �������� ������ �� ������
	   MessageBox(NULL, L"������ �������� ��������� ����", L"������", MB_OK | MB_ICONERROR);
	   return FALSE;
   }
   
   czCreateMainMenu(hWndMain);

   ShowWindow(hWndMain, SW_MAXIMIZE);
   UpdateWindow(hWndMain);
   ShowWindow(hWndPopup, nCmdShow);
   UpdateWindow(hWndPopup);

   SetTimer(hWndMain, 1, 1000, NULL);
   SetTimer(hWndPopup, 2, 700, NULL);

   return TRUE;
}

// ������� �� �������� ���� �������� ����
VOID czCreateMainMenu(HWND hwnd) {
	HMENU hMenu				= CreateMenu();
	HMENU hPopupMenuMove	= CreatePopupMenu();
	HMENU hPopupMenuParam	= CreatePopupMenu();

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) hPopupMenuMove, L"&�������� �������");
	{
		AppendMenu(hPopupMenuMove, MF_STRING, IDM_MOVE_STOP, L"��&��������");
		AppendMenu(hPopupMenuMove, MF_STRING, IDM_MOVE_RESET, L"&�����������");
	}
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) hPopupMenuParam, L"&��������� �������");
	{
		AppendMenu(hPopupMenuParam, MF_STRING, IDM_PARAM_RESET, L"&������ ��������");
		AppendMenu(hPopupMenuParam, MF_STRING, IDM_PARAM_CHANGE, L"&�������� � �������");
	}
	AppendMenu(hMenu, MF_STRING, IDM_ABOUT, L"&� ���������");
	AppendMenu(hMenu, MF_STRING, IDM_EXIT, L"�&����");
	SetMenu(hwnd, hMenu);
}

HMENU PrepareContextMenu() {
	HMENU hMenu				= CreatePopupMenu();
	HMENU hPopupMenuMove	= CreatePopupMenu();
	HMENU hPopupMenuParam	= CreatePopupMenu();

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) hPopupMenuMove, L"&������� �������");
	{
		AppendMenu(hPopupMenuMove, MF_STRING, IDM_SIZE_INC, L"�&�������� � 1,2 ����");
		AppendMenu(hPopupMenuMove, MF_STRING, IDM_SIZE_DEC, L"�&�������� � 1,2 ����");
		AppendMenu(hPopupMenuMove, MF_STRING, IDM_SIZE_RESET, L"&������ ��������");
	}
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) hPopupMenuParam, L"�&�������� ��������");
	{
		AppendMenu(hPopupMenuParam, MF_STRING, IDM_TIME_INC, L"�&�������� � 1,5 ����");
		AppendMenu(hPopupMenuParam, MF_STRING, IDM_TIME_DEC, L"�&�������� � 1,5 ����");
		AppendMenu(hPopupMenuParam, MF_STRING, IDM_TIME_RESET, L"&������ ��������");
	}
	AppendMenu(hMenu, MF_STRING, IDM_EXIT, L"��&����� ����");
	return hMenu;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND	- ��������� ���� ����������
//  WM_PAINT	-��������� ������� ����
//  WM_DESTROY	 - ������ ��������� � ������ � ���������.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	TCHAR str[] = L"Lorem Ipsum Dolar Sit Ammet";
	PAINTSTRUCT ps;
	RECT rectPlace, rect;
	static INT cx = 0, cy = 0;
	HDC hdc;	
	HFONT hFont;
	static LOGFONT lf;
	CHOOSEFONT cf;

	ZeroMemory(&cf, sizeof(CHOOSEFONT));
	cf.Flags		= CF_EFFECTS | CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS;
	cf.hwndOwner	= hWnd;
	cf.lpLogFont	= &lf;
	cf.lStructSize	= sizeof(CHOOSEFONT);

	switch (message) {
	case WM_CREATE:
		GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), (LPSTR)&lf);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId)
		{
		case IDM_PARAM_CHANGE:
			if (ChooseFont(&cf)) 
				InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_PARAM_RESET:
			GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), (LPSTR)&lf);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_MOVE_STOP:
			KillTimer(hWnd, 1);
			break;
		case IDM_MOVE_RESET:
			SetTimer(hWnd, 1, 1000, NULL);
			break;
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
		// ������������� ���� ������
		SetTextColor(hdc, NULL);
		// ������� �����
		hFont = CreateFontIndirect(&lf);
		// �������� �����
		SelectObject(hdc, hFont);
		TextOut(hdc, cx, cy, str, wcslen(str));
		//DrawText(hdc, (LPCWSTR) str, wcslen(str), &rectPlace, DT_WORDBREAK|DT_CENTER|DT_VCENTER);
		// ������� ������ �����
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		// ���������� ������ � ������� ���������� ����
		DrawText(GetDC(hWnd), (LPCWSTR) str, wcslen(str), &rect, DT_CALCRECT);
		// �������� ������ ������� �������
		GetClientRect(hWnd, &rectPlace);
		cx = (rectPlace.left + rand() % rectPlace.right) - (rect.right - rect.left);
		cy = (rectPlace.top + rand() % rectPlace.bottom) - (rect.bottom - rect.right);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���������� ��������� ��� ���������� ����
LRESULT CALLBACK WndProcPopup(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HMENU hMenu;
	int wmId, wmEvent;
	HDC hdc;	
	PAINTSTRUCT ps;
	static INT R = 25;
	static INT posIndex = 0;
	static INT msTimer = 700;
	RECT r;
	static POINT pos[4];// = { {0,0}, {1,0}, {1,1}, {0,1} };

	switch(message) {
	case WM_CREATE:
		GetClientRect(hWnd, &r);
		pos[0].x = 0;			pos[0].y = 0;
		pos[1].x = r.right-R*2; pos[1].y = 0; 
		pos[2].x = r.right-R*2; pos[2].y = r.bottom-R*2; 
		pos[3].x = 0;			pos[3].y = r.bottom-R*2; 
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch(wmId) {
		case IDM_SIZE_INC:
			R *= 1.2;
			GetClientRect(hWnd, &r);
			pos[0].x = 0;			pos[0].y = 0;
			pos[1].x = r.right-R*2; pos[1].y = 0; 
			pos[2].x = r.right-R*2; pos[2].y = r.bottom-R*2; 
			pos[3].x = 0;			pos[3].y = r.bottom-R*2; 
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_SIZE_DEC:
			R /= 1.2;
			GetClientRect(hWnd, &r);
			pos[0].x = 0;			pos[0].y = 0;
			pos[1].x = r.right-R*2; pos[1].y = 0; 
			pos[2].x = r.right-R*2; pos[2].y = r.bottom-R*2; 
			pos[3].x = 0;			pos[3].y = r.bottom-R*2; 
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_SIZE_RESET:
			R = 25;
			GetClientRect(hWnd, &r);
			pos[0].x = 0;			pos[0].y = 0;
			pos[1].x = r.right-R*2; pos[1].y = 0; 
			pos[2].x = r.right-R*2; pos[2].y = r.bottom-R*2; 
			pos[3].x = 0;			pos[3].y = r.bottom-R*2; 
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_TIME_INC:
			msTimer *= 1.5;
			KillTimer(hWnd, 2);
			SetTimer(hWnd, 2, msTimer, NULL);
			break;
		case IDM_TIME_DEC:
			msTimer /= 1.5;
			KillTimer(hWnd, 2);
			SetTimer(hWnd, 2, msTimer, NULL);
			break;
		case IDM_TIME_RESET:
			msTimer = 700;
			KillTimer(hWnd, 2);
			SetTimer(hWnd, 2, msTimer, NULL);
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
		GetClientRect(hWnd, &r);
		Ellipse(hdc, pos[posIndex].x, pos[posIndex].y, pos[posIndex].x+R*2, pos[posIndex].y+R*2);
		//Ellipse(hdc, (r.right-R*2)*pos[posIndex].x, (r.bottom-R*2)*pos[posIndex].y, (r.right)*pos[posIndex].x, (r.bottom)*pos[posIndex].y);
		EndPaint(hWnd, &ps);
		break;
	case WM_CONTEXTMENU:
		hMenu = PrepareContextMenu();
		TrackPopupMenu(hMenu, TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN,
			LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
		DestroyMenu(hMenu);
		break;
	case WM_TIMER:
		posIndex = ++posIndex % 4;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

// ���������� ��������� ��� ���� "� ���������".
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
