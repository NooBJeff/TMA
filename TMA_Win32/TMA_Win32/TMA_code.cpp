#include<Windows.h>

#include <iostream>
#include <cmath>
#include <cstdlib>
#define DIM 1024
#define DM1 (DIM-1)
#define _sq(x) ((x)*(x)) // square
#define _cb(x) abs((x)*(x)*(x)) // absolute value of cube
#define _cr(x) (unsigned char)(pow((x),1.0/3.0)) // cube root

unsigned char GR(int, int);
unsigned char BL(int, int);

unsigned char RD(int i, int j)
{
	// YOUR CODE HERE
	return (char)(_sq(cos(atan2(j - 512, i - 512) / 2)) * 255);
}
unsigned char GR(int i, int j)
{
	// YOUR CODE HERE
	return (char)(_sq(cos(atan2(j - 512, i - 512) / 2 - 2 * acos(-1) / 3)) * 255);
}
unsigned char BL(int i, int j)
{
	// YOUR CODE HERE
	return (char)(_sq(cos(atan2(j - 512, i - 512) / 2 + 2 * acos(-1) / 3)) * 255);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	static unsigned char color[3];
	switch (Msg)
	{
	case WM_PAINT:
		PAINTSTRUCT paint;
		BeginPaint(hWnd, &paint);
		SelectObject(paint.hdc, GetStockObject(DC_BRUSH));
		for (int i = 0; i < DIM;i ++)
		{
			for (int j = 0; j < DIM; j++)
			{
				color[0] = RD(i, j) & 255;
				color[1] = GR(i, j) & 255;
				color[2] = BL(i, j) & 255;
				SetPixel(paint.hdc, i, j, RGB(color[0], color[1], color[2]));
			}
		}
		EndPaint(hWnd, &paint);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevApp, LPSTR lpCmd, int nShowCmd)
{
	char *Name = "Tweetable Mathematical Art";
	WNDCLASSEX wnd = {};
	wnd.cbClsExtra = 0;
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = WinProc;
	wnd.lpszClassName = Name;
	wnd.style = CS_VREDRAW | CS_HREDRAW;

	RegisterClassEx(&wnd);

	HWND hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, Name, "Tweetable Mathematical Art", WS_OVERLAPPEDWINDOW^WS_THICKFRAME, 0, 0, 1024, 1024, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
	{
		return 0;
	}

	ShowWindow(hWnd, nShowCmd);

	UpdateWindow(hWnd);
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.message;
}
