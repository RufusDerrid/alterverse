#include <iostream>
#include <Winuser.h>
#include <XInput.h>

#ifndef _INPUT_H
#define _INPUT_H
#define WIN32_LEAN_AND_MEAN

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
	bool checkControllers();
	void keyDown(WPARAM wParam);
	void keyUp(WPARAM wParam);
	void keyIn(WPARAM wParam);
	bool isKeyDown(UCHAR key) const;
	bool wasKeyPressed(UCHAR key) const;
	bool anyKeyPressed() const;
	void clearKeyPress(UCHAR vkey);
	void clear(UCHAR what);

	std::string getTextIn() { return m_textIn; }
	char getChatIn() { return m_charIn; }
	void clearTextIn() { m_textIn.clear(); }
	void clearAll() { clear(inputNS::KEYS_MOUSE_TEXT); }
};

#endif