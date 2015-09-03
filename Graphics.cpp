#include "Graphics.h"

Graphics::Graphics()
{
	m_direct3d = NULL;
	m_device3d = NULL;
	m_fullscreen = false;
	m_width = GAME_WIDTH;
	m_height = GAME_HEIGHT;
}

void Graphics::initialize(HWND hwnd, int width, int height, bool fullscreen)
{
	m_hwnd = hwnd;
	m_width = width;
	m_height = height;
	m_fullscreen = fullscreen;

	m_direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_direct3d == NULL)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Direct3D"));

	InitD3Dpp();

	if (m_fullscreen)
	{
		if (IsAdapterCompatible())
			m_d3dpp.FullScreen_RefreshRateInHz = m_pMode.RefreshRate;
		else
			throw(GameError(gameErrorNS::FATAL_ERROR,
			"The graphics device does not support the specified resolution and/or format."));
	}

	D3DCAPS9 caps;
	DWORD behivior;
	m_result = m_direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		behivior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else
		behivior = D3DCREATE_HARDWARE_VERTEXPROCESSING;


	m_result = m_direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwnd,
		behivior, &m_d3dpp, &m_device3d);

	if (FAILED(m_result))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));
}

void Graphics::InitD3Dpp()
{
	try
	{
		ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
		m_d3dpp.BackBufferWidth = m_width;
		m_d3dpp.BackBufferHeight = m_height;
		if (m_fullscreen)
			m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		else
			m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		m_d3dpp.BackBufferCount = 1;
		m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_d3dpp.hDeviceWindow = m_hwnd;
		m_d3dpp.Windowed = (!m_fullscreen);
		m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing D3D presentation parameters"));
	}
}

bool Graphics::IsAdapterCompatible()
{
	UINT modes = m_direct3d->GetAdapterModeCount(D3DADAPTER_DEFAULT, m_d3dpp.BackBufferFormat);
	
	for (int i = 0; i < modes - 1; i++)
	{
		m_result = m_direct3d->EnumAdapterModes(D3DADAPTER_DEFAULT, m_d3dpp.BackBufferFormat, i, &m_pMode);

		if (m_pMode.Height == m_d3dpp.BackBufferHeight &&
			m_pMode.Width == m_d3dpp.BackBufferWidth &&
			m_pMode.RefreshRate >= m_d3dpp.FullScreen_RefreshRateInHz)
			return true;
	}

	return false;
}

HRESULT Graphics::getDeviceState()
{
	m_result = E_FAIL;
	if (m_device3d == NULL)
		return m_result;
	m_result = m_device3d->TestCooperativeLevel();
	return m_result;
}

HRESULT Graphics::reset()
{
	m_result = E_FAIL;
	InitD3Dpp();
	m_result = m_device3d->Reset(&m_d3dpp);
	return m_result;
}

HRESULT Graphics::beginScene()
{
	m_result = E_FAIL;
	if (m_device3d == NULL)
		return m_result;

	m_device3d->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 0.0f, 0);

	m_result = m_device3d->BeginScene();
	
	return m_result;
}

HRESULT Graphics::endScene()
{
	m_result = E_FAIL;
	if (m_device3d)
		m_result = m_device3d->EndScene();

	return m_result;
}

HRESULT Graphics::showBackBuffer()
{
	m_result = E_FAIL;
	m_result = m_device3d->Present(NULL, NULL, NULL, NULL);

	return m_result;
}

Graphics::~Graphics()
{
	releaseAll();
}

void Graphics::releaseAll()
{
	SAFE_RELEASE(m_device3d);
	SAFE_RELEASE(m_direct3d);
}