//=============================================================================
//
// Input class [myInput.cpp]
//
//
//=============================================================================


//*****************************************************************************
// INCLUDE
//*****************************************************************************
#include "myInput.h"
//#include "myUtility.h"
#include <Windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")

//*****************************************************************************
// GLOBAL VARIABLE
//*****************************************************************************
LPDIRECTINPUT8			MyInputKeyboard::m_Input = NULL;
LPDIRECTINPUTDEVICE8	MyInputKeyboard::m_DevKeyboard = NULL;
BYTE					MyInputKeyboard::m_KeyState[MYKEYBOARD_KEY_MAX];
BYTE					MyInputKeyboard::m_KeyStateTrigger[MYKEYBOARD_KEY_MAX];
BYTE					MyInputKeyboard::m_KeyStateRelease[MYKEYBOARD_KEY_MAX];
BYTE					MyInputKeyboard::m_KeyStateRepeat[MYKEYBOARD_KEY_MAX];
int						MyInputKeyboard::m_KeyStateRepeatCnt[MYKEYBOARD_KEY_MAX];

XINPUT_STATE	MyInputGamepad::m_State;
BYTE			MyInputGamepad::m_ButtonState[MYGAMEPAD_BUTTON_MAX];
BYTE			MyInputGamepad::m_ButtonStateTrigger[MYGAMEPAD_BUTTON_MAX];
BYTE			MyInputGamepad::m_ButtonStateRelease[MYGAMEPAD_BUTTON_MAX];
BYTE			MyInputGamepad::m_ButtonStateRepeat[MYGAMEPAD_BUTTON_MAX];
int				MyInputGamepad::m_ButtonStateRepeatCnt[MYGAMEPAD_BUTTON_MAX];


//*****************************************************************************
// FUNCTION
//*****************************************************************************
//*****************************************************************************
// Input keyboard class
//*****************************************************************************
//==================================================
// Constructor
//==================================================
MyInputKeyboard::MyInputKeyboard()
{

}

//==================================================
// Destructor
//==================================================
MyInputKeyboard::~MyInputKeyboard()
{

}

//==================================================
// Initialize
//==================================================
void MyInputKeyboard::Initialize(HINSTANCE instance, HWND wnd)
{
	// Create direct input object
	if (m_Input == NULL) {
		if (FAILED(DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_Input, NULL))) {
			MessageBox(NULL, "[ERROR] Can't create direct input object.", "ERROR", MB_OK | MB_ICONWARNING);
		}
	}

	// Create device
	if (FAILED(m_Input->CreateDevice(GUID_SysKeyboard, &m_DevKeyboard, NULL))) {
		MessageBox(NULL, "[ERROR] Can't find any keyboard", "ERROR", MB_OK | MB_ICONWARNING);
	}

	// Set keyboard data format
	if (FAILED(m_DevKeyboard->SetDataFormat(&c_dfDIKeyboard))) {
		MessageBox(NULL, "[ERROR] Can't set keyboard data format", "ERROR", MB_OK | MB_ICONWARNING);
	}

	// Set cooperative level
	if (FAILED(m_DevKeyboard->SetCooperativeLevel(wnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))) {
		MessageBox(NULL, "[ERROR] Can't set keyboard cooperative level.", "ERROR", MB_OK | MB_ICONWARNING);
	}

	// Get access right
	m_DevKeyboard->Acquire();
}

//==================================================
// Uninitialize
//==================================================
void MyInputKeyboard::Uninitialize(void)
{
	// Release device
	if (m_DevKeyboard != NULL) {
		// Release access right
		m_DevKeyboard->Unacquire();

		m_DevKeyboard->Release();
		m_DevKeyboard = NULL;
	}

	// Release direct input object
	if (m_Input != NULL) {
		m_Input->Release();
		m_Input = NULL;
	}
}

//==================================================
// Update
//==================================================
void MyInputKeyboard::Update(void)
{
	BYTE keyState[MYKEYBOARD_KEY_MAX];

	// Get data from device
	if (SUCCEEDED(m_DevKeyboard->GetDeviceState(sizeof(keyState), keyState))) {
		for (int countKey = 0; countKey < MYKEYBOARD_KEY_MAX; countKey++) {
			// Get key trigger, release
			m_KeyStateTrigger[countKey] = (m_KeyState[countKey] ^ keyState[countKey]) & keyState[countKey];
			m_KeyStateRelease[countKey] = (m_KeyState[countKey] ^ keyState[countKey]) & ~keyState[countKey];

			// Get key repeat
			if (keyState[countKey]) {
				if (m_KeyStateRepeatCnt[countKey] < REPEAT_COUNT_LIMIT) {
					m_KeyStateRepeatCnt[countKey]++;

					// Key repeat on
					if (m_KeyStateRepeatCnt[countKey] == 1 || m_KeyStateRepeatCnt[countKey] >= REPEAT_COUNT_LIMIT) {
						m_KeyStateRepeat[countKey] = keyState[countKey];
					}
					else {
						m_KeyStateRepeat[countKey] = 0;
					}
				}
			}
			else {
				m_KeyStateRepeatCnt[countKey] = 0;
				m_KeyStateRepeat[countKey] = 0;
			}

			// Get key press
			m_KeyState[countKey] = keyState[countKey];
		}
	}
	else {
		// Get keyboard access right
		m_DevKeyboard->Acquire();
	}
}

//==================================================
// Get press
//==================================================
bool MyInputKeyboard::GetPress(int key)
{
	return (m_KeyState[key] & 0x80) ? true : false;
}

//==================================================
// Get trigger
//==================================================
bool MyInputKeyboard::GetTrigger(int key)
{
	return (m_KeyStateTrigger[key] & 0x80) ? true : false;
}

//==================================================
// Get release
//==================================================
bool MyInputKeyboard::GetRelease(int key)
{
	return (m_KeyStateRelease[key] & 0x80) ? true : false;
}

//==================================================
// Get repeat
//==================================================
bool MyInputKeyboard::GetRepeat(int key)
{
	return (m_KeyStateRepeat[key] & 0x80) ? true : false;
}

//*****************************************************************************
// Input gamepad class
//*****************************************************************************
//==================================================
// Constructor
//==================================================
MyInputGamepad::MyInputGamepad()
{

}

//==================================================
// Destructor
//==================================================
MyInputGamepad::~MyInputGamepad()
{

}

//==================================================
// Initialize
//==================================================
void MyInputGamepad::Initialize(void)
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
}

//==================================================
// Uninitialize
//==================================================
void MyInputGamepad::Uninitialize(void)
{

}
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30
//==================================================
// Update
//==================================================
void MyInputGamepad::Update(void)
{
	for (int i = 0; i < 4; i++) {
		if (!XInputGetState(i, &m_State)) {
			break;
		}
	}

	BYTE buttonState[MYGAMEPAD_BUTTON_MAX];
	buttonState[0] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) ? 1 : 0;
	buttonState[1] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? 1 : 0;
	buttonState[2] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? 1 : 0;
	buttonState[3] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? 1 : 0;
	buttonState[4] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_START) ? 1 : 0;
	buttonState[5] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) ? 1 : 0;
	buttonState[6] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? 1 : 0;
	buttonState[7] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? 1 : 0;
	buttonState[8] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? 1 : 0;
	buttonState[9] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? 1 : 0;
	buttonState[10] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_A) ? 1 : 0;
	buttonState[11] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_B) ? 1 : 0;
	buttonState[12] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_X) ? 1 : 0;
	buttonState[13] = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_Y) ? 1 : 0;
	buttonState[14] = m_State.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	buttonState[15] = m_State.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	buttonState[16] = m_State.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	buttonState[17] = m_State.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	// Get button data
	for (int countButton = 0; countButton < MYGAMEPAD_BUTTON_MAX; countButton++) {
		// Get button trigger, release
		m_ButtonStateTrigger[countButton] = (m_ButtonState[countButton] ^ buttonState[countButton]) & buttonState[countButton];
		m_ButtonStateRelease[countButton] = (m_ButtonState[countButton] ^ buttonState[countButton]) & ~buttonState[countButton];

		// Get button repeat
		if (buttonState[countButton]) {
			if (m_ButtonStateRepeatCnt[countButton] < REPEAT_COUNT_LIMIT) {
				m_ButtonStateRepeatCnt[countButton]++;

				// button repeat on
				if (m_ButtonStateRepeatCnt[countButton] == 1 || m_ButtonStateRepeatCnt[countButton] >= REPEAT_COUNT_LIMIT) {
					m_ButtonStateRepeat[countButton] = buttonState[countButton];
				}
				else {
					m_ButtonStateRepeat[countButton] = 0;
				}
			}
		}
		else {
			m_ButtonStateRepeatCnt[countButton] = 0;
			m_ButtonStateRepeat[countButton] = 0;
		}

		// Get button press
		m_ButtonState[countButton] = buttonState[countButton];
	}
	// Zero value if thumbsticks are within the dead zone 
	if ((m_State.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		m_State.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(m_State.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			m_State.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_State.Gamepad.sThumbLX = 0;
		m_State.Gamepad.sThumbLY = 0;
	}

	if ((m_State.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		m_State.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(m_State.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			m_State.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		m_State.Gamepad.sThumbRX = 0;
		m_State.Gamepad.sThumbRY = 0;
	}

}

//==================================================
// Get button press
//==================================================
bool MyInputGamepad::GetButtonPress(int button)
{
	return m_ButtonState[button] ? true : false;
}

//==================================================
// Get button trigger
//==================================================
bool MyInputGamepad::GetButtonTrigger(int button)
{
	return m_ButtonStateTrigger[button] ? true : false;
}

//==================================================
// Get button repeat
//==================================================
bool MyInputGamepad::GetButtonRepeat(int button)
{
	return m_ButtonStateRepeat[button] ? true : false;
}

//==================================================
// Get button release
//==================================================
bool MyInputGamepad::GetButtonRelease(int button)
{
	return m_ButtonStateRelease[button] ? true : false;
}

//==================================================
// Get left trigger
//==================================================
int MyInputGamepad::GetLeftTrigger(void)
{
	return m_State.Gamepad.bLeftTrigger;
}

//==================================================
// Get right trigger
//==================================================
int MyInputGamepad::GetRightTrigger(void)
{
	return m_State.Gamepad.bRightTrigger;
}

//==================================================
// Get left thumb
//==================================================
D3DXVECTOR2 MyInputGamepad::GetLeftThumb(void)
{
	return D3DXVECTOR2(m_State.Gamepad.sThumbLX, m_State.Gamepad.sThumbLY);
}

//==================================================
// Get right thumb
//==================================================
D3DXVECTOR2 MyInputGamepad::GetRightThumb(void)
{
	return D3DXVECTOR2(m_State.Gamepad.sThumbRX, m_State.Gamepad.sThumbRY);
}