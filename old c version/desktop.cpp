#define WINVER 0x0500
#include <windows.h>

 INPUT ip;

void key_press(char code){
	ip.ki.wVk = code; 
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
	
	Sleep(100);
}

int main()
{
    // This structure will be used to create the keyboard
    // input event.

	int count = 0;
	char tab = 0x09;
	char right_arrow = 0x27;
	char a = 0x41;
	char enter = 0x0D;

	while(!(GetKeyState(enter) & 0x8000)){

	}

	Sleep(500);

	while(count <= 30){

		// Set up a generic keyboard event.
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0; // hardware scan code for key
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;
		
		key_press(tab);
		key_press(tab);
		//key_press(tab);
		key_press(right_arrow);
		key_press(a);
		key_press(enter);
		
		Sleep(500);
		++count;
	}


    // Exit normally
    return 0;
}
