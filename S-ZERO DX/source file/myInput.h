//=============================================================================
//
// Input class [myInput.h]
//
//
//=============================================================================
#ifndef _MYINPUT_H_
#define _MYINPUT_H_


//*****************************************************************************
// INCLUDE
//*****************************************************************************
#include <Windows.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <Xinput.h>


//*****************************************************************************
// MACRO DEFINITION
//*****************************************************************************
#define	REPEAT_COUNT_LIMIT			(20)			// Repeat count limit

#define MYKEYBOARD_KEY_MAX			(256)			// Key max
#define MYKEYBOARD_KEY_ESCAPE		DIK_ESCAPE
#define MYKEYBOARD_KEY_1			DIK_1
#define MYKEYBOARD_KEY_2			DIK_2
#define MYKEYBOARD_KEY_3			DIK_3
#define MYKEYBOARD_KEY_4			DIK_4
#define MYKEYBOARD_KEY_5			DIK_5
#define MYKEYBOARD_KEY_6			DIK_6
#define MYKEYBOARD_KEY_7			DIK_7
#define MYKEYBOARD_KEY_8			DIK_8
#define MYKEYBOARD_KEY_9			DIK_9
#define MYKEYBOARD_KEY_0			DIK_0
#define MYKEYBOARD_KEY_MINUS		DIK_MINUS		// - on main keyboard
#define MYKEYBOARD_KEY_EQUALS		DIK_EQUALS
#define MYKEYBOARD_KEY_BACK			DIK_BACK		// backspace
#define MYKEYBOARD_KEY_TAB			DIK_TAB
#define MYKEYBOARD_KEY_Q			DIK_Q
#define MYKEYBOARD_KEY_W			DIK_W
#define MYKEYBOARD_KEY_E			DIK_E
#define MYKEYBOARD_KEY_R			DIK_R
#define MYKEYBOARD_KEY_T			DIK_T
#define MYKEYBOARD_KEY_Y			DIK_Y
#define MYKEYBOARD_KEY_U			DIK_U
#define MYKEYBOARD_KEY_I			DIK_I
#define MYKEYBOARD_KEY_O			DIK_O
#define MYKEYBOARD_KEY_P			DIK_P
#define MYKEYBOARD_KEY_LBRACKET		DIK_LBRACKET
#define MYKEYBOARD_KEY_RBRACKET		DIK_RBRACKET
#define MYKEYBOARD_KEY_RETURN		DIK_RETURN		// Enter on main keyboard
#define MYKEYBOARD_KEY_LCONTROL		DIK_LCONTROL
#define MYKEYBOARD_KEY_A			DIK_A
#define MYKEYBOARD_KEY_S			DIK_S
#define MYKEYBOARD_KEY_D			DIK_D
#define MYKEYBOARD_KEY_F			DIK_F
#define MYKEYBOARD_KEY_G			DIK_G
#define MYKEYBOARD_KEY_H			DIK_H
#define MYKEYBOARD_KEY_J			DIK_J
#define MYKEYBOARD_KEY_K			DIK_K
#define MYKEYBOARD_KEY_L			DIK_L
#define MYKEYBOARD_KEY_SEMICOLON	DIK_SEMICOLON
#define MYKEYBOARD_KEY_APOSTROPHE	DIK_APOSTROPHE
#define MYKEYBOARD_KEY_GRAVE		DIK_GRAVE		// accent grave
#define MYKEYBOARD_KEY_LSHIFT		DIK_LSHIFT
#define MYKEYBOARD_KEY_BACKSLASH	DIK_BACKSLASH
#define MYKEYBOARD_KEY_Z			DIK_Z
#define MYKEYBOARD_KEY_X			DIK_X
#define MYKEYBOARD_KEY_C			DIK_C
#define MYKEYBOARD_KEY_V			DIK_V
#define MYKEYBOARD_KEY_B			DIK_B
#define MYKEYBOARD_KEY_N			DIK_N
#define MYKEYBOARD_KEY_M			DIK_M
#define MYKEYBOARD_KEY_COMMA		DIK_COMMA 
#define MYKEYBOARD_KEY_PERIOD		DIK_PERIOD		// . on main keyboard
#define MYKEYBOARD_KEY_SLASH		DIK_SLASH		// / on main keyboard
#define MYKEYBOARD_KEY_RSHIFT		DIK_RSHIFT
#define MYKEYBOARD_KEY_MULTIPLY		DIK_MULTIPLY	// * on numeric keypad */
#define MYKEYBOARD_KEY_LMENU		DIK_LMENU		// left Alt */
#define MYKEYBOARD_KEY_SPACE		DIK_SPACE
#define MYKEYBOARD_KEY_CAPITAL		DIK_CAPITAL
#define MYKEYBOARD_KEY_F1			DIK_F1
#define MYKEYBOARD_KEY_F2			DIK_F2
#define MYKEYBOARD_KEY_F3			DIK_F3
#define MYKEYBOARD_KEY_F4			DIK_F4
#define MYKEYBOARD_KEY_F5			DIK_F5
#define MYKEYBOARD_KEY_F6			DIK_F6
#define MYKEYBOARD_KEY_F7			DIK_F7
#define MYKEYBOARD_KEY_F8			DIK_F8
#define MYKEYBOARD_KEY_F9			DIK_F9
#define MYKEYBOARD_KEY_F10			DIK_F10
#define MYKEYBOARD_KEY_NUMLOCK		DIK_NUMLOCK
#define	MYKEYBOARD_KEY_SCROLL		DIK_SCROLL		// Scroll Lock
#define MYKEYBOARD_KEY_NUMPAD7		DIK_NUMPAD7
#define MYKEYBOARD_KEY_NUMPAD8		DIK_NUMPAD8
#define MYKEYBOARD_KEY_NUMPAD9		DIK_NUMPAD9
#define MYKEYBOARD_KEY_SUBTRACT		DIK_SUBTRACT	// - on numeric keypad
#define MYKEYBOARD_KEY_NUMPAD4		DIK_NUMPAD4
#define MYKEYBOARD_KEY_NUMPAD5		DIK_NUMPAD5 
#define MYKEYBOARD_KEY_NUMPAD6		DIK_NUMPAD6
#define MYKEYBOARD_KEY_ADD			DIK_ADD			// + on numeric keypad
#define MYKEYBOARD_KEY_NUMPAD1		DIK_NUMPAD1
#define MYKEYBOARD_KEY_NUMPAD2		DIK_NUMPAD2
#define MYKEYBOARD_KEY_NUMPAD3		DIK_NUMPAD3
#define MYKEYBOARD_KEY_NUMPAD0		DIK_NUMPAD0
#define MYKEYBOARD_KEY_DECIMAL		DIK_DECIMAL		// . on numeric keypad
#define MYKEYBOARD_KEY_OEM_102		DIK_OEM_102		// <> or \| on RT 102-key keyboard (Non-U.S.)
#define MYKEYBOARD_KEY_F11			DIK_F11
#define MYKEYBOARD_KEY_F12			DIK_F12
#define MYKEYBOARD_KEY_F13			DIK_F13			//                     (NEC PC98)
#define MYKEYBOARD_KEY_F14			DIK_F14			//                     (NEC PC98)
#define MYKEYBOARD_KEY_F15			DIK_F15			//                     (NEC PC98)
#define MYKEYBOARD_KEY_KANA			DIK_KANA		// (Japanese keyboard)
#define MYKEYBOARD_KEY_ABNT_C1		DIK_ABNT_C1		// /? on Brazilian keyboard
#define MYKEYBOARD_KEY_CONVERT		DIK_CONVERT		// (Japanese keyboard)
#define MYKEYBOARD_KEY_NOCONVERT	DIK_NOCONVERT	// (Japanese keyboard)
#define MYKEYBOARD_KEY_YEN			DIK_YEN			// (Japanese keyboard)
#define MYKEYBOARD_KEY_ABNT_C2		DIK_ABNT_C2		// Numpad . on Brazilian keyboard
#define MYKEYBOARD_KEY_NUMPADEQUALS	DIK_NUMPADEQUALS	// = on numeric keypad (NEC PC98)
#define MYKEYBOARD_KEY_PREVTRACK	DIK_PREVTRACK	// Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) 
#define MYKEYBOARD_KEY_AT			DIK_AT			//                     (NEC PC98)
#define MYKEYBOARD_KEY_COLON		DIK_COLON		//                     (NEC PC98)
#define MYKEYBOARD_KEY_UNDERLINE	DIK_UNDERLINE	//                     (NEC PC98)
#define MYKEYBOARD_KEY_KANJI		DIK_KANJI		// (Japanese keyboard)
#define MYKEYBOARD_KEY_STOP			DIK_STOP		//                     (NEC PC98)
#define MYKEYBOARD_KEY_AX			DIK_AX			//                     (Japan AX)
#define MYKEYBOARD_KEY_UNLABELED	DIK_UNLABELED	//                        (J3100)
#define MYKEYBOARD_KEY_NEXTTRACK	DIK_NEXTTRACK	// Next Track
#define MYKEYBOARD_KEY_NUMPADENTER	DIK_NUMPADENTER	// Enter on numeric keypad
#define MYKEYBOARD_KEY_RCONTROL		DIK_RCONTROL
#define MYKEYBOARD_KEY_MUTE			DIK_MUTE		// Mute
#define MYKEYBOARD_KEY_CALCULATOR	DIK_CALCULATOR	// Calculator
#define MYKEYBOARD_KEY_PLAYPAUSE	DIK_PLAYPAUSE	// Play / Pause
#define MYKEYBOARD_KEY_MEDIASTOP	DIK_MEDIASTOP	// Media Stop
#define MYKEYBOARD_KEY_VOLUMEDOWN	DIK_VOLUMEDOWN	// Volume -
#define MYKEYBOARD_KEY_VOLUMEUP		DIK_VOLUMEUP	// Volume +
#define MYKEYBOARD_KEY_WEBHOME		DIK_WEBHOME		// Web home
#define MYKEYBOARD_KEY_NUMPADCOMMA	DIK_NUMPADCOMMA	// , on numeric keypad (NEC PC98)
#define MYKEYBOARD_KEY_DIVIDE		DIK_DIVIDE		// / on numeric keypad
#define MYKEYBOARD_KEY_SYSRQ		DIK_SYSRQ
#define MYKEYBOARD_KEY_RMENU		DIK_RMENU		// right Alt
#define MYKEYBOARD_KEY_PAUSE		DIK_PAUSE		// Pause
#define MYKEYBOARD_KEY_HOME			DIK_HOME		// Home on arrow keypad
#define MYKEYBOARD_KEY_UP			DIK_UP			// UpArrow on arrow keypad
#define MYKEYBOARD_KEY_PRIOR		DIK_PRIOR		// PgUp on arrow keypad
#define MYKEYBOARD_KEY_LEFT			DIK_LEFT		// LeftArrow on arrow keypad
#define MYKEYBOARD_KEY_RIGHT		DIK_RIGHT		// RightArrow on arrow keypad
#define MYKEYBOARD_KEY_END			DIK_END			// End on arrow keypad
#define MYKEYBOARD_KEY_DOWN			DIK_DOWN		// DownArrow on arrow keypad
#define MYKEYBOARD_KEY_NEXT			DIK_NEXT		// PgDn on arrow keypad
#define MYKEYBOARD_KEY_INSERT		DIK_INSERT		// Insert on arrow keypad
#define MYKEYBOARD_KEY_DELETE		DIK_DELETE		// Delete on arrow keypad
#define MYKEYBOARD_KEY_LWIN			DIK_LWIN		// Left Windows key
#define MYKEYBOARD_KEY_RWIN			DIK_RWIN		// Right Windows key
#define MYKEYBOARD_KEY_APPS			DIK_APPS		// AppMenu key
#define MYKEYBOARD_KEY_POWER		DIK_POWER		// System Power
#define MYKEYBOARD_KEY_SLEEP		DIK_SLEEP		// System Sleep
#define MYKEYBOARD_KEY_WAKE			DIK_WAKE		// System Wake
#define MYKEYBOARD_KEY_WEBSEARCH	DIK_WEBSEARCH	// Web Search
#define MYKEYBOARD_KEY_WEBFAVORITES	DIK_WEBFAVORITES	// Web Favorites
#define MYKEYBOARD_KEY_WEBREFRESH	DIK_WEBREFRESH	// Web Refresh
#define MYKEYBOARD_KEY_WEBSTOP		DIK_WEBSTOP		// Web Stop
#define MYKEYBOARD_KEY_WEBFORWARD	DIK_WEBFORWARD	// Web Forward
#define MYKEYBOARD_KEY_WEBBACK		DIK_WEBBACK		// Web Back
#define MYKEYBOARD_KEY_MYCOMPUTER	DIK_MYCOMPUTER	// My Computer
#define MYKEYBOARD_KEY_MAIL			DIK_MAIL		// Mail
#define MYKEYBOARD_KEY_MEDIASELECT	DIK_MEDIASELECT	// Media Select

#define MYGAMEPAD_LEFT_THUMB_DEADZONE	XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
#define MYGAMEPAD_RIGHT_THUMB_DEADZONE	XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
#define MYGAMEPAD_TRIGGER_THRESHOLD		XINPUT_GAMEPAD_TRIGGER_THRESHOLD

#define MYGAMEPAD_BUTTON_MAX			(18)
#define MYGAMEPAD_BUTTON_UP				(0)
#define MYGAMEPAD_BUTTON_DOWN			(1)
#define MYGAMEPAD_BUTTON_LEFT			(2)
#define MYGAMEPAD_BUTTON_RIGHT			(3)
#define MYGAMEPAD_BUTTON_START			(4)
#define MYGAMEPAD_BUTTON_BACK			(5)
#define MYGAMEPAD_BUTTON_LEFT_THUMB		(6)
#define MYGAMEPAD_BUTTON_RIGHT_THUMB	(7)
#define MYGAMEPAD_BUTTON_LEFT_SHOULDER	(8)
#define MYGAMEPAD_BUTTON_RIGHT_SHOULDER	(9)
#define MYGAMEPAD_BUTTON_A				(10)
#define MYGAMEPAD_BUTTON_B				(11)
#define MYGAMEPAD_BUTTON_X				(12)
#define MYGAMEPAD_BUTTON_Y				(13)
#define MYGAMEPAD_BUTTON_STAIC1			(14)
#define MYGAMEPAD_BUTTON_STAIC2			(15)
#define MYGAMEPAD_BUTTON_STAIC3			(16)
#define MYGAMEPAD_BUTTON_STAIC4			(17)
//*****************************************************************************
// CLASS DEFINITION
//*****************************************************************************
//==================================================
// Input keyboard class
//==================================================
class MyInputKeyboard {
public:
	MyInputKeyboard();
	~MyInputKeyboard();
	
	static void Initialize(HINSTANCE instance, HWND wnd);
	static void Uninitialize(void);
	static void Update(void);
	static bool GetPress(int key);
	static bool GetTrigger(int key);
	static bool GetRelease(int key);
	static bool GetRepeat(int key);
	
private:
	static LPDIRECTINPUT8		m_Input;									// DirectInput object pointer
	static LPDIRECTINPUTDEVICE8	m_DevKeyboard;								// Keyboard device pointer
	static BYTE					m_KeyState[MYKEYBOARD_KEY_MAX];				// Keyboard state
	static BYTE					m_KeyStateTrigger[MYKEYBOARD_KEY_MAX];		// Keyboard trigger
	static BYTE					m_KeyStateRelease[MYKEYBOARD_KEY_MAX];		// Keyboard release
	static BYTE					m_KeyStateRepeat[MYKEYBOARD_KEY_MAX];		// Keyboard repeat
	static int					m_KeyStateRepeatCnt[MYKEYBOARD_KEY_MAX];	// Keyboard repeat count
};

//==================================================
// Input gamepad class
//==================================================
class MyInputGamepad {
public:
	MyInputGamepad();
	~MyInputGamepad();

	static void Initialize(void);
	static void Uninitialize(void);
	static void Update(void);
	static bool GetButtonPress(int button);
	static bool GetButtonTrigger(int button);
	static bool GetButtonRepeat(int button);
	static bool GetButtonRelease(int button);
	static int GetLeftTrigger(void);
	static int GetRightTrigger(void);
	static D3DXVECTOR2 GetLeftThumb(void);
	static D3DXVECTOR2 GetRightThumb(void);

private:
	static XINPUT_STATE	m_State;								// X input state
	static BYTE m_ButtonState[MYGAMEPAD_BUTTON_MAX];			// Button state
	static BYTE m_ButtonStateTrigger[MYGAMEPAD_BUTTON_MAX];		// Button trigger
	static BYTE m_ButtonStateRelease[MYGAMEPAD_BUTTON_MAX];		// Button release
	static BYTE m_ButtonStateRepeat[MYGAMEPAD_BUTTON_MAX];		// Button release
	static int	m_ButtonStateRepeatCnt[MYGAMEPAD_BUTTON_MAX];	// Button repeat count
};


#endif // _MYINPUT_H_