#include "Game.h"

Game::Game()
{
	//TODO m_input = new Input();
	m_paused = false;
	m_graphics = NULL;
	m_initialized = false;
}

Game::~Game()
{
	deleteAll();
	ShowCursor(true);
}

void Game::initialize(HWND hwnd)
{
	m_hwnd = hwnd;
	m_graphics = new Graphics();
	m_graphics->initialize(m_hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);
	//TODO m_input->initialize(m_hwnd, false);

	if (QueryPerformanceFrequency(&m_timeFreq) == false)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));
	}

	QueryPerformanceCounter(&m_timeStart);
	m_initialized = true;
}

LRESULT Game::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_initialized)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN: case WM_SYSKEYDOWN:
			//TODO m_input->keyDown(wParam);
			return 0;

		case WM_KEYUP: case WM_SYSKEYUP:
			//TODO m_input->keyUp(wParam);
			return 0;

		case WM_CHAR:
			//TODO m_input->keyIn(wParam);
			return 0;

		case WM_MOUSEMOVE:
			//TODO m_input->mouseIn(lParam);
			return 0;

		case WM_INPUT:
			//TODO m_input->mouseRawIn(lParam);
			return 0;

		case WM_LBUTTONDOWN:
			//TODO m_input->setMouseLButton(true);
			//TODO m_input->mouseIn(lParam);
			return 0;

		case WM_LBUTTONUP:
			//TODO m_input->setMouseLButton(false);
			//TODO m_input->mouseIn(lParam);
			return 0;

		case WM_MBUTTONDOWN:
			//TODO m_input->setMouseMButton(true);
			//TODO m_input->mouseIn(lParam);
			return 0;

		case WM_MBUTTONUP:
			//TODO m_input->setMouseMButton(false);
			//TODO m_input->mouseIn(lParam);
			return 0;

		case WM_RBUTTONDOWN:
			//TODO m_input->setMouseRButton(true);
			//TODO m_input->mouseIn(lParam);
			return 0;

		case WM_RBUTTONUP:
			//TODO m_input->setMouseRButton(true);
			//TODO m_input->mouseIn(lParam);
			return 0;

		case WM_XBUTTONDOWN: case WM_NCXBUTTONUP:
			//TODO m_input->setMouseXButton(wParam);
			//TODO m_input->mouseIn(lParam);
			return 0;

		case WM_DEVICECHANGE:
			//TODO m_input->checkControllers();
			return 0;
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Game::handleLostGraphicsDevice()
{
	m_hr = m_graphics->getDeviceState();
	if (FAILED(m_hr))
	{
		if (m_hr == D3DERR_DEVICELOST)
		{
			Sleep(100);
			return;
		}
		else if (m_hr == D3DERR_DEVICENOTRESET)
		{
			releaseAll();
			m_hr = m_graphics->reset();
			if (FAILED(m_hr))
				return;
			resetAll();
		}
		else
			return;
	}
}

void Game::renderGame()
{
	if (SUCCEEDED(m_graphics->beginScene()))
	{
		render();

		m_graphics->endScene();
	}

	handleLostGraphicsDevice();

	m_graphics->showBackBuffer();
}

void Game::run(HWND hwnd)
{
	if (m_graphics == NULL)
		return;

	QueryPerformanceCounter(&m_timeEnd);
	m_frameTime = (float)(m_timeEnd.QuadPart - m_timeStart.QuadPart) / (float)m_timeFreq.QuadPart;

	if (m_frameTime < MIN_FRAME_TIME)
	{
		m_sleepTime = (DWORD)((MIN_FRAME_TIME - m_frameTime) * 1000);
		timeBeginPeriod(1);
		Sleep(m_sleepTime);
		timeEndPeriod(1);
		return;
	}

	if (m_frameTime > 0.0)
		m_fps = (m_fps*0.99f) + (0.01f / m_frameTime);
	if (m_frameTime > MAX_FRAME_TIME)
		m_frameTime = MAX_FRAME_TIME;

	m_timeStart = m_timeEnd;
	//TODO m_input->readControllers();

	if (!m_paused)
	{
		update();
		ai();
		collisions();

		//TODO m_input->vibrateControllers(m_frameTime);
	}

	renderGame();
	//TODO m_input->Clear(inputNS::KEYS_PRESSED);
}