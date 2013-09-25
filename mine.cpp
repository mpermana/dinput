#include <windows.h>
#include <stdio.h>


#define KEYEVENTF_UNICODE 0x0004

HWND hWndMain;

#include "mouse.cpp"

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
    for (int i=0;i<10;i++) {
	printf("click %d\n",i);
	MouseClick();
	Sleep(2500);
    }

    return 0;
}
