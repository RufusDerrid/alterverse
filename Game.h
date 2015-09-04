#ifndef _GAME_H
#define _GAME_H
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <Mmsystem.h>
#include "Graphics.h"
#include "input.h"
#include "constants.h"
#include "GameError.h"

class Game
{
protected:
	Graphics *m_graphics;
	Input *m_input;
	HWND m_hwnd;
	HRESULT m_hr;
	LARGE_INTEGER m_timeStart;
	LARGE_INTEGER m_timeEnd;
	LARGE_INTEGER m_timeFreq;
	float m_frameTime;
	float m_fps;
	DWORD m_sleepTime;
	bool m_paused;
	bool m_initialized;

public:
	Game();
	virtual ~Game();
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void initialize(HWND hwnd);
	virtual void run(HWND);
	virtual void releaseAll();
	virtual void resetAll();
	virtual void deleteAll();
	virtual void renderGame();
	virtual void handleLostGraphicsDevice();
	Graphics* getGraphics() { return m_graphics; }
	Input* getInput() { return m_input; }
	void exitGame() { PostMessage(m_hwnd, WM_DESTROY, 0, 0); }

	virtual void update() = 0;
	virtual void ai() = 0;
	virtual void collisions() = 0;
	virtual void render() = 0;
};

#endif