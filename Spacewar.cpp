#include "Spacewar.h"

Spacewar::Spacewar()
{

}

Spacewar::~Spacewar()
{
	releaseAll();
}

void Spacewar::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	return;
}

void Spacewar::update(){}

void Spacewar::ai(){}

void Spacewar::collisions(){}

void Spacewar::render(){}

void Spacewar::releaseAll()
{
	Game::releaseAll();
	return;
}

void Spacewar::resetAll()
{
	Game::resetAll();
	return;
}