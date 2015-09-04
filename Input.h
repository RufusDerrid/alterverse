#ifndef _INPUT_H
#define _INPUT_H
#define WIN32_LEAN_AND_MEAN

class Input;

#include <windows.h>
#include <WindowsX.h>
#include <string>
#include <XInput.h>
#include "constants.h"
#include "gameError.h"

#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE ((USHORT) 0x02)
#endif

namespace inputNS
{
	const int KEYS_ARRAY_LEN = 256;

	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR MOUSE = 4;
	const UCHAR TEXT_IN = 8;
	const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}

const DWORD MAX_CONTROLLERS = 4;

struct ControllerState
{
	XINPUT_STATE state;
	XINPUT_VIBRATION vibration;
	float vibrateTimeLeft;
	float vibrateTimeRight;
	bool connected;
};

class Input
{
private:
	bool m_keysDown[inputNS::KEYS_ARRAY_LEN];
	bool m_keysPressed[inputNS::KEYS_ARRAY_LEN];

	std::string m_textIn;
	char m_charIn;
	bool m_newLine;
	int m_mouseX, m_mouseY;
	int m_mouseRawX, m_mouseRawY;
	RAWINPUTDEVICE m_rid[1];
	bool m_mouseCaptured;
	bool m_mouseLButton;
	bool m_mouseMButton;
	bool m_mouseRButton;
	bool m_mouseX1Button;
	bool m_mouseX2Button;
	ControllerState m_controllers[MAX_CONTROLLERS];

public:
	Input();
	virtual ~Input();

	void initialize(HWND hwnd, bool capture);
	//bool checkControllers();
	void keyDown(WPARAM wParam);
	void keyUp(WPARAM wParam);
	void keyIn(WPARAM wParam);
	bool isKeyDown(UCHAR key) const;
	bool wasKeyPressed(UCHAR key) const;
	bool anyKeyPressed() const;
	void clearKeyPress(UCHAR vkey);
	void clear(UCHAR what);
	void mouseIn(LPARAM lParam);
	void mouseRawIn(LPARAM lParam);

	std::string getTextIn() { return m_textIn; }
	char getChatIn() { return m_charIn; }
	void clearTextIn() { m_textIn.clear(); }
	void clearAll() { clear(inputNS::KEYS_MOUSE_TEXT); }

	//mouse
	void setMouseLButton(bool b) { m_mouseLButton = b; }
	void setMouseMButton(bool b) { m_mouseMButton = b; }
	void setMouseRButton(bool b) { m_mouseRButton = b; }

	void setMouseXButton(WPARAM wParam)
	{
		m_mouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
		m_mouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
	}

	int getMouseX() const { return m_mouseX; }
	int getMouseY() const { return m_mouseY; }
	int getMouseRawX() const { return m_mouseRawX; }
	int getMouseRawY() const { return m_mouseRawY; }

	bool getMouseLButton() const { return m_mouseLButton; }
	bool getMouseMButton() const { return m_mouseMButton; }
	bool getMouseRButton() const { return m_mouseRButton; }
	bool getMouseX1Button() const { return m_mouseX1Button; }
	bool getMouseX2Button() const { return m_mouseX2Button; }
};

#endif