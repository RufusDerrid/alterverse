#define _CRTDBG_MAP_ALLOC
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "Spacewar.h"

//Function proto
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);
bool AnotherInstance();

//Global vars
Game* g_game = NULL;

//Consts
const char CLASS_NAME[] = "WinMain";
const char APP_TITLE[] = "Hello Wold";
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

//==========================
//WinMain
//==========================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	MSG msg;
	HWND hwnd = NULL;

	if (AnotherInstance())
		return 1;

	g_game = new Spacewar;

	if (!CreateMainWindow(hwnd, hInstance, nCmdShow))
		return 1;

	try{
		
		g_game->initialize(hwnd);

		int done = 0;
		while (!done)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					done = 1;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				g_game->run(hwnd);
			}
		}

		safeDelete(g_game);
		return msg.wParam;
	}
	catch (const GameError &err)
	{
		g_game->deleteAll();
		DestroyWindow(hwnd);
		MessageBox(NULL, err.getMessage(), "Error", MB_OK);
	}
	catch (...)
	{
		g_game->deleteAll();
		DestroyWindow(hwnd);
		MessageBox(NULL, "Unknown error occured in game.", "Error", MB_OK);
	}

	safeDelete(g_game);
	return 0;
}

//==============================================
//Window event callback
//==============================================
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return (g_game->messageHandler(hWnd, msg, wParam, lParam));
}

//===================================
//Create window
//===================================
bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASS wcx;

	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WinProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = CLASS_NAME;
	wcx.hIcon = NULL;

	if (RegisterClass(&wcx) == 0)
		return false;

	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	hwnd = CreateWindowEx(0, CLASS_NAME, APP_TITLE, style, CW_USEDEFAULT, CW_USEDEFAULT,
		GAME_WIDTH, GAME_HEIGHT, (HWND)NULL, (HMENU)NULL, hInstance, (LPVOID)NULL);

	if (!hwnd)
		return false;

	if (!FULLSCREEN)
	{
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);
		MoveWindow(hwnd, 0, 0, GAME_WIDTH + (GAME_WIDTH - clientRect.right),
			GAME_HEIGHT + (GAME_HEIGHT - clientRect.bottom), TRUE);
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	return true;
}

//===================================
//Multiple instance prevent
//===================================
bool AnotherInstance()
{
	HANDLE ourMutex;

	ourMutex = CreateMutex(NULL, true, "Test mutex");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return true;

	return false;
}