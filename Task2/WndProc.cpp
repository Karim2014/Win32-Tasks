#include "WndProc.h"
#include "stdafx.h"

WORD GetWindowWidth(HWND hwnd);
WORD GetWindowHeight(HWND hwnd);
void Redraw(HWND hWnd);

INT x = 0, y = 0, cx, cy;
RECT rectPlace;
PTCHAR text = L"Задание №2 по ОC,\nст. Сабитова К.А. гр. ИСзск-19";
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc = GetDC(hWnd);
	PAINTSTRUCT ps;
	INT height, width;
	switch (uMsg) {
	case WM_SIZE:
		// получаем центр окна
		x = GetWindowWidth(hWnd)/2;
		y = GetWindowHeight(hWnd)/2;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// определяем размеры выводимой области
		DrawText(hdc, (LPCWSTR) text, strlen((char*)text)*3.2, &rectPlace, DT_CALCRECT);
		// устанавливаем вертикаль посередине
		height = rectPlace.bottom-rectPlace.top;
		rectPlace.top = y - (height)/2;
		rectPlace.bottom = rectPlace.top + height;
		// устанавливаем горизонталь посередине
		width = rectPlace.right-rectPlace.left;
		rectPlace.left = x - (width)/2;
		rectPlace.right = rectPlace.left + width;
		// прямоугольник для отладки
		//Rectangle(hdc, rectPlace.left, rectPlace.top, rectPlace.right, rectPlace.bottom);
		// выводим текст
		DrawText(hdc, (LPCWSTR) text, strlen((char*)text)*3.2, &rectPlace, DT_CENTER);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_HOME:
			// смещаем к левому краю
			x = (rectPlace.right-rectPlace.left)/2;
			Redraw(hWnd);
			break;
		case VK_END:
			// смещаем к правому краю
			x = GetWindowWidth(hWnd) - (rectPlace.right-rectPlace.left)/2;
			Redraw(hWnd);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: 
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
};

static INT curHPenIndex = 2;
static INT curBrushIndex = 2;
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	HBRUSH hBrush;
	HPEN hPen;
	PAINTSTRUCT ps;
	RECT rect;
	hPen = CreatePen(curHPenIndex, 1, RGB(0,0,0));
	GetWindowRect(hWnd, &rect);
	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_SIZE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//создаем объект кисть
		hBrush = CreateHatchBrush(curBrushIndex, RGB(250,200,100));
		// выбриаем объекты
		SelectObject(hdc, hBrush);
		SelectObject(hdc, hPen);
		//рисуем закруглённый прямоугольник
		RoundRect(hdc, 20, 20, rect.right-rect.left-20, rect.bottom-rect.top-40, 15, 15);
		DeleteObject(hPen);
		DeleteObject(hBrush);
		break;
	case WM_LBUTTONDOWN:
		curHPenIndex = 0 + rand() % 7;
		Redraw(hWnd);
		break;
	case WM_RBUTTONDOWN:
		curBrushIndex = 0 + rand() % 5;
		Redraw(hWnd);
		break;
	case WM_KEYDOWN:
		break;
	default: 
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
};

static int fontSize = 16;
LRESULT CALLBACK PopupWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	PTCHAR str = L"Lorem Ipsum Dolar Sit Amet";
	PAINTSTRUCT ps;
	HDC hdc;
	HFONT hFont;
	RECT rectPlace;
	switch (uMsg) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);		
		// получаем рамеры рабочей области
		GetClientRect(hWnd, &rectPlace);
		// устанавливаем цвет текста
		SetTextColor(hdc, NULL);
		// создаем шрифт
		hFont = CreateFont(fontSize,0,0,0,0,0,0,0,
								DEFAULT_CHARSET,100,0,0, DEFAULT_PITCH, L"Times New Roman");
		// выбираем шрифт
		SelectObject(hdc, hFont);
		// выводим текст
		DrawText(hdc, (LPCWSTR) str, 26, &rectPlace, DT_WORDBREAK|DT_CENTER|DT_VCENTER);
		// удаляем объект шрифт
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch(wParam) {
		case VK_NEXT:
			fontSize -= 4;
			break;
		case VK_PRIOR:
			fontSize += 4;
			break;
		}
		Redraw(hWnd);
		break;
	default: 
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
};

void Redraw(HWND hWnd) {
	InvalidateRect(hWnd, NULL, TRUE);
}

// полуаем ширину рабочей области
WORD GetWindowWidth(HWND hwnd) {
	RECT rect;
	GetClientRect(hwnd, &rect);
	return rect.right - rect.left;
};

// получаем всоту рабочей области
WORD GetWindowHeight(HWND hwnd) {
	RECT rect;
	GetClientRect(hwnd, &rect);
	return rect.bottom - rect.top;
};
