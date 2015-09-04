#include "TextureManager.h"

bool TextureManager::initialize(Graphics* graphics, const char* fileName)
{
	try
	{
		m_graphics = graphics;
		m_fileName = fileName;
		m_result = m_graphics->loadTexture(m_fileName, TRANSCOLOR, m_width, m_height, m_texture);

		if (FAILED(m_result))
		{
			safeRelease(m_texture);
			return false;
		}
	}
	catch (...) { return false; }

	m_initialized = true;

	return true;
}

void TextureManager::onLostDevice()
{
	if (!m_initialized)
		return;

	safeRelease(m_texture);
}

void TextureManager::onResetDevice()
{
	if (!m_initialized)
		return;

	m_graphics->loadTexture(m_fileName, TRANSCOLOR, m_width, m_height, m_texture);
}