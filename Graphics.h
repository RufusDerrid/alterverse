#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif

#include "d3d9.h"
#include "D3dx9core.h"
#include "constants.h"
#include "GameError.h"

#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D LPDIRECT3D9
#define LP_SPRITE LPD3DXSPRITE
#define LP_TEXTURE LPDIRECT3DTEXTURE9

#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
	((COLOR_ARGB)((((a)&0xff)<<24) | (((r)&0xff)<<16) | (((g)&0xff)<<8) | ((b)&0xff)))

struct SpriteData
{
	int width;
	int height;
	float x;
	float y;
	float scale;
	float angle;
	RECT rect;
	LP_TEXTURE texture;
	bool flipHorizontal;
	bool flipVertical;
};

class Graphics
{
private:
	LP_3D m_direct3d;
	LP_3DDEVICE m_device3d;
	LP_SPRITE m_sprite;
	LP_TEXTURE m_texture;
	D3DPRESENT_PARAMETERS m_d3dpp;

	HRESULT m_result;
	HWND m_hwnd;
	bool m_fullscreen;
	int m_width;
	int m_height;
	D3DDISPLAYMODE m_pMode;

	void InitD3Dpp();
	bool IsAdapterCompatible();

public:
	Graphics();
	virtual ~Graphics();
	void releaseAll();
	void initialize(HWND hwnd, int width, int height, bool fullscreen);
	HRESULT showBackBuffer();
	HRESULT getDeviceState();
	HRESULT reset();
	HRESULT loadTexture(const char* filename, COLOR_ARGB transcolor, UINT &width, UINT &height, LP_TEXTURE &texture);
	void drawSprite(const SpriteData &spriteData, COLOR_ARGB color);
	HRESULT beginScene();
	HRESULT endScene();
};
#endif