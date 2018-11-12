/*------------------------------------------------------------
   HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
                 (c) Charles Petzold, 1998
  ------------------------------------------------------------*/

#include <windows.h>
#include<math.h>
#include<stdio.h>

double a = 360.0;//初始角度

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("windmill") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
     hwnd = CreateWindow (szAppName,                  // window class name
                          TEXT ("windmill Program"), // window caption
                          WS_OVERLAPPEDWINDOW,        // window style
                          CW_USEDEFAULT,              // initial x position
                          CW_USEDEFAULT,              // initial y position
                          CW_USEDEFAULT,              // initial x size
                          CW_USEDEFAULT,              // initial y size
                          NULL,                       // parent window handle
                          NULL,                       // window menu handle
                          hInstance,                  // program instance handle
                          NULL) ;                     // creation parameters
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect ;
	 HPEN hpen;
	 HBRUSH hbrush;

	 int xo, yo;//风车的中心
	 int r;//风车半径
	 int xstart1 = 0, xend1 = 0, ystart1 = 0, yend1 = 0;
	 int xstart2 = 0, xend2 = 0, ystart2 = 0, yend2 = 0;
	 int xstart3 = 0, xend3 = 0, ystart3 = 0, yend3 = 0;

     switch (message)
     {
     case WM_CREATE:
		 SetTimer(hwnd, 9999, 100, NULL);
		 break;
     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;
          
          GetClientRect (hwnd, &rect) ;
		  hpen = (HPEN)GetStockObject(BLACK_PEN);
		  hbrush = CreateSolidBrush(RGB(255, 220, 220));

		  SelectObject(hdc, hpen);
		  SelectObject(hdc, hbrush);
		  //设置风车的中心点在屏幕中心
		  xo = (rect.left + rect.right) / 2;
		  yo = (rect.bottom + rect.top) / 2;

		  //遍历
		  a--;
		  r = min(xo, yo) - 50;
		  double angle = 3.1415926 / 180;
		  SelectObject(hdc, hbrush);
		  //绘制扇形区域
		  
		  //划定矩形区域
		  int left = xo - r;
		  int right = xo + r;
		  int top = yo + r;
		  int bottom = yo - r;
		  //规定扇形边界
		  int ax = xo + r * sin(a*angle);
		  int ay = yo + r * cos(a*angle);

		  int bx = xo + r * sin((a+120)*angle);
		  int by = yo + r * cos((a+120)*angle);

		  int cx = xo + r * sin((a+240)*angle);
		  int cy = yo + r * cos((a+240)*angle);

		  //第一个
		  Pie(
			  hdc,
			  left, top,
			  right, bottom,
			  ax, ay,
			  bx, by
		  );

		  hbrush = CreateSolidBrush(RGB(255, 255, 200));
		  SelectObject(hdc, hbrush);

		  //第二个
		  Pie(
			  hdc,
			  left, top,
			  right, bottom,
			  bx, by,
			  cx, cy
		  );

		  hbrush = CreateSolidBrush(RGB(200, 255, 255));
		  SelectObject(hdc, hbrush);
		  
		  //第三个
		  Pie(
			  hdc,
			  left, top,
			  right, bottom,
			  cx, cy,
			  ax, ay
		  );
	 case WM_TIMER:
		 if (wParam == 9999) {
			 InvalidateRect(hwnd, NULL, TRUE);
		 }
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}