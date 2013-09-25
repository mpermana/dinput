#include <windows.h>
#include <stdio.h>


#define KEYEVENTF_UNICODE 0x0004

HWND hWndMain;

static void SendVK(char vk)
{
    INPUT inp[2];
    memset(inp,0,sizeof(INPUT));
    inp[0].type = INPUT_KEYBOARD;
    inp[0].ki.dwFlags = 0;
    inp[1] = inp[0];
    inp[1].ki.dwFlags |= KEYEVENTF_KEYUP;

        inp[0].ki.wVk = inp[1].ki.wVk = vk;
	inp[0].ki.wScan = inp[1].ki.wScan = 0;

	printf("vk %d\n", vk);

        SendInput(1, inp, sizeof(INPUT));
	Sleep(30);
	SendInput(1, &inp[1], sizeof(INPUT));
	Sleep(30);
}

static void SendScan(char vk)
{
    INPUT inp[2];
    memset(inp,0,sizeof(INPUT));
    inp[0].type = INPUT_KEYBOARD;
    inp[0].ki.dwFlags = KEYEVENTF_UNICODE;
    inp[1] = inp[0];
    inp[1].ki.dwFlags |= KEYEVENTF_KEYUP;

        inp[0].ki.wVk = inp[1].ki.wVk = 0;
	inp[0].ki.wScan = inp[1].ki.wScan = vk;

	printf("uc %d\n", vk);

        SendInput(1, inp, sizeof(INPUT));
	SendInput(1, &inp[1], sizeof(INPUT));
}

static void SendString(LPCTSTR str)
{
    SetForegroundWindow(hWndMain);	
    SendVK(13);
    for (LPCTSTR p=str; *p; p++) {
	SendScan(*p);
    }
    Sleep(50);
    SendVK(13);
}

int main(int argc,char **argv)
{
    hWndMain = FindWindow(0, "FINAL FANTASY XIV: A Realm Reborn");
    if(hWndMain == NULL)
    {
        printf("Main window not found, terminating\n");
        return -1;
    }

    char *input = argv[1];
    while (true) {
	SendString(input);
	Sleep(20000);
    }

    return 0;
}
