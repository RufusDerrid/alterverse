#pragma once
#ifndef _CONSTANTS_H
#define _CONSTANTS_H
#define WIN32_LEAN_MEAN

//Constants

//window
const UINT GAME_WIDTH = 1024;
const UINT GAME_HEIGHT = 768;
const bool FULLSCREEN = false;

//key mapping
const UCHAR ESC_KEY = VK_ESCAPE;

//game
const float FRAME_RATE = 200.0f;
const float MIN_FRAME_RATE = 10.0f;
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;

#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
	((COLOR_ARGB)((((a)&0xff)<<24) | (((r)&0xff)<<16) | (((g)&0xff)<<8) | ((b)&0xff)))

const COLOR_ARGB TRANSCOLOR = SETCOLOR_ARGB(0, 255, 0, 255);

template <typename T>
inline void safeRelease(T& ptr)
{
	if (ptr) 
	{
		ptr->Release();
		ptr = NULL;
	}
}
#define SAFE_RELEASE safeRelease

template <typename T>
inline void safeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = NULL;
	}
}

#endif