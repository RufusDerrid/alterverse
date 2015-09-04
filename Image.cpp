#include "Image.h"

bool Image::initialize(Graphics* graphics, int width, int height, int ncols, TextureManager* textureManager)
{
	try
	{
		m_graphics = graphics;
		m_textureManager = textureManager;
		m_spriteData.texture = m_textureManager->getTexture();

		if (width == 0)
			width = m_textureManager->getWidth();
		m_spriteData.width = width;

		if (height == 0)
			height = m_textureManager->getHeight();
		m_spriteData.height = height;

		m_ncols = ncols;

		if (m_ncols == 0) m_ncols = 1;

		m_spriteData.rect.left = (m_currentFrame % m_ncols) * m_spriteData.width;
		m_spriteData.rect.right = m_spriteData.rect.left + m_spriteData.width;
		m_spriteData.rect.top = (m_currentFrame / m_ncols) * m_spriteData.height;
		m_spriteData.rect.bottom = m_spriteData.rect.top + m_spriteData.height;
	}
	catch (...) { return false; }

	m_initialized = true;

	return true;
}