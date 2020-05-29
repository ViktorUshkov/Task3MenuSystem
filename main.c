#include <windows.h>
#include "header.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szProgName[] = "menu_system";

key_condition key = def;
menu_t* menu;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	menu = Extract();

	HWND hWnd;
	MSG lpMsg;
	WNDCLASS w;

	w.lpszClassName = szProgName;
	w.hInstance = hInstance;
	w.lpfnWndProc = WndProc;
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hIcon = 0;
	w.lpszMenuName = 0;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.cbClsExtra = 0;
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.cbWndExtra = 0;

	if (!RegisterClass(&w))
		return 0;


	hWnd = CreateWindow(szProgName, "Just Menu", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, (HWND)NULL, (HMENU)NULL, (HINSTANCE)hInstance, (HINSTANCE)NULL);

	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);

	while (GetMessage(&lpMsg, hWnd, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return (int)lpMsg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	GetClientRect(hWnd, &rect);

	switch (messg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_DOWN:
		{
			key = down;
			InvalidateRect(hWnd, &rect, TRUE);
			UpdateWindow(hWnd);
			break;
		}
		case VK_UP:
		{
			key = up;
			InvalidateRect(hWnd, &rect, TRUE);
			UpdateWindow(hWnd);
			break;
		}
		case VK_RIGHT:
		{
			key = right;
			InvalidateRect(hWnd, &rect, TRUE);
			UpdateWindow(hWnd);
			break;
		}
		case VK_LEFT:
		{
			key = left;
			InvalidateRect(hWnd, &rect, TRUE);
			UpdateWindow(hWnd);
			break;
		}
		default:
			break;
		}

	case WM_KEYUP:
		if (wParam == 27) ExitProcess(0);
		break;

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		Draw(hdc, menu, key);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, messg, wParam, lParam);
}
