#include "Window.h"
#include <stdio.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onDestroy();
			break;
		}
		case WM_SIZING:
		{
			//win->setSize(LOWORD(lParam), HIWORD(lParam));
			//win->swapBuffers();
			break;
		}
		case WM_SIZE:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->setSize(LOWORD(lParam), HIWORD(lParam));
			break;
		}
		case WM_MOVING:
		{
			//Sleep(5);
			//win->swapBuffers();
			break;
		}
		case WM_MOVE:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			int left = (int)(short) LOWORD(lParam);
			int top  = (int)(short) HIWORD(lParam);
			window->setPos(left, top);
			break;
		}
		case WM_SETFOCUS:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onFocus();
			break;
		}
		case WM_KILLFOCUS:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onKillFocus();
			break;
		}
		case WM_SYSKEYDOWN: 
		{ 
			return 0;
		}
		case WM_PAINT:
		{
			break;
		}
		default:
		{
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

Window::Window()
{
}

Window::~Window()
{
	DestroyWindow(_hwnd);
}

void Window::init(const char* windowName, int width, int height, bool fullscreen)
{
	this->width = width;
	this->height = height;
	screen_width = GetSystemMetrics(SM_CXSCREEN);
	screen_height = GetSystemMetrics(SM_CYSCREEN);
	arrowCursor = LoadCursor(NULL, IDC_ARROW);
	noneCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_NONECURSOR));


	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
	wc.hInstance = NULL;
	wc.lpszClassName = windowName;
	wc.lpszMenuName = "";
	wc.lpfnWndProc = WndProc;
	wc.style = 0;

	if (!RegisterClassEx(&wc)) {
		onDestroy();
	}

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, WS_SYSMENU, false);

	_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		windowName, windowName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME,
		rc.left, rc.top,
		rc.right, rc.bottom, NULL, NULL, NULL, NULL);

	SetWindowLongPtr(_hwnd, GWLP_USERDATA, (LONG_PTR)this);
	if (!_hwnd) {
		onDestroy();
	}
	if (fullscreen)
	{
		setFullscreen(1);
	}

	GetClientRect(_hwnd, &rc);
	width = rc.right - rc.left;
	height = rc.bottom - rc.top;
	left = rc.left;
	top = rc.top;
	centerX = left + width / 2;
	centerY = top + height / 2;

	ShowWindow(_hwnd, SW_SHOW);
	UpdateWindow(_hwnd);


	hDC = GetDC(_hwnd);
	memBitmap = CreateBitmap(
		width, height,
		1, 8 * 4, nullptr);
}

void Window::broadcast()
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		DispatchMessage(&msg);
	}
	Sleep(1);
}

void Window::setBuffer(int* image)
{
	HDC hdc = GetDC(_hwnd);

	SetBitmapBits(memBitmap, height * 4 * width, image);
	HDC src = CreateCompatibleDC(hdc);
	SelectObject(src, memBitmap);
	BitBlt(hdc, 0, 0, width, height, src, 0, 0, SRCCOPY);
	DeleteDC(src);
	ReleaseDC(_hwnd, hdc);
}

//windows size block
void Window::setPos(int x, int y)
{
	left = x;
	top  = y;
	centerX = left + width  / 2;
	centerY = top  + height / 2;
}
Rect Window::getCenter()
{
	return Rect(centerX, centerY);
}

Rect Window::getInnerSize()
{
	return Rect(left, top, width, height);
}

void Window::setFullscreen(const bool state)
{
	if(state)
	{
		LONG l_WinStyle = GetWindowLong (_hwnd, GWL_STYLE);
		SetWindowLong(_hwnd, GWL_STYLE,(l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~(WS_CAPTION | WS_THICKFRAME));
        SetWindowLong(_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST);
		
		SetWindowPos (_hwnd, HWND_TOP, 0, 0, screen_width, screen_height, 0);
	}
	else
	{
		LONG l_WinStyle = GetWindowLong (_hwnd, GWL_STYLE);
		SetWindowLong(_hwnd, GWL_STYLE,(l_WinStyle | WS_CAPTION | WS_THICKFRAME | WS_BORDER) & ~WS_POPUP & ~WS_MAXIMIZE);
		//SetWindowPos(_hwnd, HWND_TOP, left, top, width, height, 0);
	}
}


//windows virtuals
void Window::onDestroy()
{
	
}

void Window::setSize(unsigned int width, unsigned int height)
{
	this->width   = width;
	this->height  = height;
	
	RECT rc;
	GetClientRect (_hwnd, 	 	   &rc);
	ClientToScreen(_hwnd, (POINT *)&rc);
	left    = rc.left;
	top     = rc.top;
	
	centerX = left + width  / 2;
	centerY = top  + height / 2;
}

void Window::onFocus()
{
	
}

void Window::onKillFocus()
{
	
}



//system metrics
Rect Window::screenSize()
{
	return Rect(screen_width, screen_height);
}


//cursor
void Window::showCursor(const bool show)
{
	if(show)
	{
		SetCursor(arrowCursor);
	}
	else
	{
		SetCursor(noneCursor);
	}
}