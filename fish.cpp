#include <windows.h>
#include <stdio.h>


#define KEYEVENTF_UNICODE 0x0004

HWND hWndMain;
HWND hWndSave;

static void SendVK(char vk)
{
    hWndSave = GetForegroundWindow();
    SetForegroundWindow(hWndMain);	

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
	Sleep(40);
	SendInput(1, &inp[1], sizeof(INPUT));
	Sleep(40);

    SetForegroundWindow(hWndSave);	

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

        SendInput(2, inp, sizeof(INPUT));
}

static void SendString(LPCTSTR str)
{
    SendVK(13);
    for (LPCTSTR p=str; *p; p++) {
	SendScan(*p);
    }
    Sleep(50);
    SendVK(13);
    Sleep(1000);
}

static void sleeper(int n) {
	for (int i=0;i<n;i++) {
		printf("%d\n",i);
		Sleep(1000);
	}
	printf("\n");
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
    Sleep(2000);

   int delay1 = 15;
   int delay2 = 12;
   if (argc > 1) {
     delay1 = atoi(argv[1]);
   }
   if (argc > 2) {
     delay2 = atoi(argv[2]);
   }
   printf("%d %d\n",delay1,delay2);
    while (true) {
	SendVK('2');
	sleeper(delay1);
	SendVK('3');
	sleeper(delay2);
    }

    return 0;
}
