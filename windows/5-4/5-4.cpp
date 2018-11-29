/*------------------------------------------------------------
   HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
				 (c) Charles Petzold, 1998
  ------------------------------------------------------------*/

#include <windows.h>
#include<math.h>
#include<stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int count = 0;//存储点的数量
 static int flag = 0;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("5-4");
	HWND         hwnd;
	MSG          msg;
	WNDCLASS     wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName,                  // window class name
		TEXT("4-5"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		CW_USEDEFAULT,              // initial x position
		CW_USEDEFAULT,              // initial y position
		CW_USEDEFAULT,              // initial x size
		CW_USEDEFAULT,              // initial y size
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);                     // creation parameters

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT rect;
	int x;
	int y;
	POINT pt;
	POINT array[10000];//存储点的坐标
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hwnd, 1111, 200, NULL);
		break;
	case WM_TIMER:
		if (wParam == 1111)
			InvalidateRect(hwnd, NULL, 1);//刷新用户区域
		break;
	
	case WM_MOUSEMOVE:
	{
		if (wParam&MK_LBUTTON) {
			hdc = BeginPaint(hwnd, &ps);//获取设备环境指针
			if (count < 10000)
			{
				//x= LOWORD(lParam);
			    //y = HIWORD(lParam);
				GetCursorPos(&pt);
				ScreenToClient(hwnd, &pt);
				array[count].x = pt.x;
				array[count].y = pt.y;
			
				SetPixel(hdc, array[count].x, array[count].y, RGB(0,0,0));
				count++;
				InvalidateRect(hwnd, NULL, 1);
			}
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		flag = 1;
		//InvalidateRect(hwnd, NULL, 1);
	    break;
	}
	case WM_LBUTTONDOWN:
		flag = 0;
		break;
	case WM_PAINT:
	{
		if (flag == 1)
		{
			hdc = BeginPaint(hwnd, &ps);
			GetClientRect(hwnd, &rect);
			
			Polyline(hdc, array, count);
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

}



