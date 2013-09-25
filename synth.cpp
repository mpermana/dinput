#include <windows.h>
#include <stdio.h>


#define KEYEVENTF_UNICODE 0x0004

HWND hWndMain;

#include "mouse.cpp"

static void SendString(LPCTSTR str)
{
    INPUT inp[2];
    memset(inp,0,sizeof(INPUT));
    inp[0].type = INPUT_KEYBOARD;
    inp[0].ki.dwFlags = 0;
    inp[1] = inp[0];
    inp[1].ki.dwFlags |= KEYEVENTF_KEYUP;

    for (LPCTSTR p=str; *p; p++) {

        inp[0].ki.wVk = inp[1].ki.wVk = *p;
	printf("send %d\n", inp[1].ki.wVk);

	HWND currentWindow;
	currentWindow = GetForegroundWindow();

	SetForegroundWindow(hWndMain);	
        SendInput(1, inp, sizeof(INPUT));
	Sleep(30);
	SendInput(1, &inp[1], sizeof(INPUT));
	SetForegroundWindow(currentWindow);
	Sleep(3000);
    }
}

int main(int argc,char **argv)
{
    hWndMain = FindWindow(0, "FINAL FANTASY XIV: A Realm Reborn");
    if(hWndMain == NULL)
    {
        printf("Main window not found, terminating\n");
        return -1;
    }

    SetForegroundWindow(hWndMain);	
    Sleep(100);

    char *input = argv[1];
    char *repeat = getenv("repeat");
    int  delay = 3000;
    if (repeat) {
	sscanf(repeat,"%d",&delay);
	printf("delay=%d\n",delay);
    }
    while (true) {
	printf("click\n");
	SendString("```");
	Sleep(1500);
	SendString(input);
	if (!repeat)
		break;
	printf("waiting\n");
	Sleep(delay);
    }

    return 0;
}
