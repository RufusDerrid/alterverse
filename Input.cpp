#include "Input.h"
#include "GameError.h"

Input::Input()
{
	for (int i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		m_keysDown[i] = false;

	for (int i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		m_keysPressed[i] = false;

	m_newLine = true;
	m_textIn = "";
	m_charIn = 0;

	m_mouseX = 0;
	m_mouseY = 0;
	m_mouseRawX = 0;
	m_mouseRawY = 0;
	m_mouseLButton = false;
	m_mouseMButton = false;
	m_mouseRButton = false;
	m_mouseX1Button = false;
	m_mouseX2Button = false;

	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		m_controllers[i].vibrateTimeLeft = 0;
		m_controllers[i].vibrateTimeRight = 0;
	}
}

void Input::initialize(HWND hwnd, bool mouseCaptured)
{
	try
	{
		m_mouseCaptured = mouseCaptured;
		m_rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		m_rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		m_rid[0].dwFlags = RIDEV_INPUTSINK;
		m_rid[0].hwndTarget = hwnd;
		RegisterRawInputDevices(m_rid, 1, sizeof(m_rid[0]));

		if (m_mouseCaptured)
			SetCapture(hwnd);

		ZeroMemory(m_controllers, sizeof(ControllerState) * MAX_CONTROLLERS);
		checkControllers();
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing input system"));
	}
}

void Input::keyDown(WPARAM wParam)
{
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{
		m_keysDown[wParam] = true;
		m_keysPressed[wParam] = true;
	}
}

bool Input::isKeyDown(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return m_keysDown[vkey];
	else
		return false;
}

bool Input::wasKeyPressed(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return m_keysPressed[vkey];
	else
		return false;
}

bool Input::anyKeyPressed() const
{
	for (int i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		if (m_keysPressed[i] == true)
			return true;

	return false;
}

void Input::keyUp(WPARAM wParam)
{
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{
		m_keysDown[wParam] = false;
	}
}

void Input::keyIn(WPARAM wParam)
{
	if (m_newLine)
	{
		m_textIn.clear();
		m_newLine = false;
	}
	
	if ((char)wParam == '\b')
	{
		if (m_textIn.length() > 0)
			m_textIn.erase(m_textIn.size() - 1);
	}
	else
	{
		m_textIn += wParam;
		m_charIn = wParam;
	}

	if ((char)wParam == '\r')
		m_newLine = true;

	const UCHAR CONSOLE_KEY = VK_OEM_3;
	const UCHAR ESC_KEY = VK_ESCAPE;
	const UCHAR ALT_KEY = VK_MENU;
	const UCHAR ENTER_KEY = VK_RETURN;
	const UCHAR SHIP1_LEFT_KEY = 'A';
	const UCHAR SHIP1_RIGHT_KEY = 'D';
	const UCHAR SHIP1_FORWARD_KEY = 'W';
	const UCHAR SHIP1_FIRE_KEY = 'S';
	const UCHAR SHIP2_LEFT_KEY = VK_LEFT;
	const UCHAR SHIP2_RIGHT_KEY = VK_RIGHT;
	const UCHAR SHIP2_FORWARD_KEY = VK_UP;
	const UCHAR SHIP2_FIRE_KEY = VK_DOWN;
}

void Input::clearKeyPress(UCHAR vkey)
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		m_keysPressed[vkey] = false;
}

void Input::clear(UCHAR what)
{

}

Input::~Input()
{
	if (m_mouseCaptured)
		ReleaseCapture();
}