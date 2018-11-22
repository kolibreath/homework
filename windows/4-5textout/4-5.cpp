/*------------------------------------------------------------
   HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
				 (c) Charles Petzold, 1998
  ------------------------------------------------------------*/

#include <windows.h>
#include<math.h>
#include<stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int count = 0;//记录输出的字符行
long Y = 0;
int f = 0;
//RGB
int c1 = 0;
int c2 = 0;
int c3 = 0;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("4-5");
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
	HFONT hf[3];//定义字体句柄
	TEXTMETRIC tm;//声明字体结构
	short Lncount = 6;
//	PAINTSTRUCT PtStr;//定义指向包含绘图信息的结构体变量
	static TCHAR *textbuf[5] = {
		L"我特别爱学习",
		L"所以我是好孩子",
		L"老师喜欢我",
		L"同学们也爱我",
		L"真开心"
	};
	long x = 0;
	long y = 0;
	
	long X = 0;
	int i;
	
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hwnd, 9999, 1000, NULL);
		break;
	case WM_TIMER:
		if(wParam==9999)
		InvalidateRect(hwnd, NULL, 1);//刷新用户区域
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		//for (int k = 0; k < Lncount; k = k +  1) {
		int c = count % 5;
		int len = lstrlen(textbuf[c]);
		TCHAR *term = textbuf[c];
		count++;
		X = 0;
		for (i = 0; i < len; i++) {
			int h = 20 + 10 * i;
			
			hf[0] = CreateFont(h, // nHeight
				0, // nWidth
				0, // nEscapement
				0, // nOrientation
				FW_BOLD, // nWeight
				FALSE, // bItalic
				FALSE, // bUnderline
				0, // cStrikeOut
				ANSI_CHARSET, // nCharSet
				OUT_DEFAULT_PRECIS, // nOutPrecision
				CLIP_DEFAULT_PRECIS, // nClipPrecision
				DEFAULT_QUALITY, // nQuality
				DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
				L"楷体"); // lpszFac
			hf[1] = CreateFont(h, // nHeight
				0, // nWidth
				0, // nEscapement
				0, // nOrientation
				FW_BOLD, // nWeight
				FALSE, // bItalic
				FALSE, // bUnderline
				0, // cStrikeOut
				ANSI_CHARSET, // nCharSet
				OUT_DEFAULT_PRECIS, // nOutPrecision
				CLIP_DEFAULT_PRECIS, // nClipPrecision
				DEFAULT_QUALITY, // nQuality
				DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
				L"宋体"); // lpszFac
			hf[2] = CreateFont(h, // nHeight
				20, // nWidth
				0, // nEscapement
				0, // nOrientation
				FW_BOLD, // nWeight
				FALSE, // bItalic
				TRUE, // bUnderline
				0, // cStrikeOut
				ANSI_CHARSET, // nCharSet
				OUT_DEFAULT_PRECIS, // nOutPrecision
				CLIP_DEFAULT_PRECIS, // nClipPrecision
				DEFAULT_QUALITY, // nQuality
				DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
				L"微软雅黑"); // lpszFac
			hf[3] = CreateFont(h, // nHeight
				0, // nWidth
				0, // nEscapement
				0, // nOrientation
				FW_BOLD, // nWeight
				TRUE, // bItalic
				FALSE, // bUnderline
				0, // cStrikeOut
				ANSI_CHARSET, // nCharSet
				OUT_DEFAULT_PRECIS, // nOutPrecision
				CLIP_DEFAULT_PRECIS, // nClipPrecision
				DEFAULT_QUALITY, // nQuality
				DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
				L"宋体"); // lpszFac
			hf[4] = CreateFont(h, // nHeight
				20, // nWidth
				0, // nEscapement
				0, // nOrientation
				FW_BOLD, // nWeight
				FALSE, // bItalic
				FALSE, // bUnderline
				0, // cStrikeOut
				ANSI_CHARSET, // nCharSet
				OUT_DEFAULT_PRECIS, // nOutPrecision
				CLIP_DEFAULT_PRECIS, // nClipPrecision
				DEFAULT_QUALITY, // nQuality
				DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
				L"隶书"); // lpszFac
			HFONT hh = hf[f % 5];
			SelectObject(hdc, hh);
			GetTextMetrics(hdc, &tm);
			SetTextColor(hdc, RGB(c1,c2,c3));
			c1 = (c1 + 10)%255;
			c2 = (c2 + 50)%255;
			c3 = (c3 + 10)%255;
			x = X + i * 70;
			TextOut(hdc, x, Y, &term[i], 1);
			DeleteObject(hf);
		}
		Y = (Y + 70) % 350;
		f++;
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	
}



