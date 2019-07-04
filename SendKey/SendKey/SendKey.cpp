#include <iostream>
#include <Windows.h>


using namespace std;

HWND hWndMain = NULL;

static void SendString(char *str)
{
	INPUT inp[2];
	memset(inp, 0, sizeof(INPUT));
	inp[0].type = INPUT_KEYBOARD;
	inp[0].ki.dwFlags = 0;
	inp[1] = inp[0];
	inp[1].ki.dwFlags |= KEYEVENTF_KEYUP;

	for (char *p=str; *p; p++) {
		inp[0].ki.wVk = inp[1].ki.wVk = *p;
		printf("send %d\n", inp[1].ki.wVk);
		HWND currentWindow;
		currentWindow = GetForegroundWindow();
		SetForegroundWindow(hWndMain);
		SendInput(1, inp, sizeof(INPUT));
		Sleep(30);
		SendInput(1, &inp[1], sizeof(INPUT));
		SetForegroundWindow(currentWindow);
		Sleep(1000);
	}
}

int main(int argc, char **argv) {
	hWndMain = FindWindow(NULL, TEXT("FINAL FANTASY XIV"));
	if (hWndMain == NULL) {
		cout << "Did not find window";
		return 1;
	}
	cout << argv[1];
	char* input = argv[1];
	while (true) {
		SendString(input);
	}
}