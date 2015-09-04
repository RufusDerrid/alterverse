#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H

#include "Graphics.h"
#include "constants.h"

class TextureManager
{
private:
	Graphics* m_graphics;
	const char* m_fileName;
	HRESULT m_result;
	UINT m_width;
	UINT m_height;
	LP_TEXTURE m_texture;
	bool m_initialized;

public:
	TextureManager(){}
	virtual ~TextureManager(){}

	bool initialize(Graphics* graphics, const char* fileName);
	void onLostDevice();
	void onResetDevice();

	LP_TEXTURE getTexture() const { return m_texture; }
	UINT getWidth() const { return m_width; }
	UINT getHeight() const { return m_height; }
};

#endif