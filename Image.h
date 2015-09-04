#ifndef _IMAGE_H
#define _IMAGE_H

#include "Graphics.h"
#include "TextureManager.h"

class Image
{
private:
	Graphics* m_graphics;
	TextureManager* m_textureManager;
	SpriteData m_spriteData;
	int m_ncols;
	int m_currentFrame;
	bool m_initialized;

public:
	Image(){}
	virtual ~Image(){}

	bool initialize(Graphics* graphics, int width, int height, int ncols, TextureManager* textureManager);
};

#endif