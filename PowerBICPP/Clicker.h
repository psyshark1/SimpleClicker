#include <WinUser.h>
#pragma once
class Clicker {
	//private:
		//DWORD Xpos, Ypos;

	public:

		void SetCursorPosition(int x, int y) {
			SetCursorPos(x, y);
		}

		void mButtonClick(DWORD mButtonPress, DWORD mButtonUnPress) {
			mouse_event(mButtonPress | mButtonUnPress, 0, 0, 0, 0);
		}

		void mWheelRoll(TCHAR* WheelRollValue) {
			mouse_event(MOUSEEVENTF_WHEEL, 0, 0, strtol(WheelRollValue, NULL, 10), 0);
		}

		void kButtonClick(BYTE kButtonPress, BYTE kButtonUnPress) {
			keybd_event(kButtonPress, 0, 0, 0);
			keybd_event(kButtonPress, 0, kButtonUnPress, 0);
		}
};


