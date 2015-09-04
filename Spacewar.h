#ifndef _SPACEWAR_H
#define _SPACEWAR_H
#define WIN23_LEAN_AND_MEAN

#include "Game.h"

class Spacewar : public Game
{
private:

public:
	Spacewar();
	virtual ~Spacewar();

	void initialize(HWND hwnd);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();
};

#endif