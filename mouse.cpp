static void MouseClick()
{
	INPUT Input;
	Input.type        = INPUT_MOUSE;
	Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &Input, sizeof(INPUT));
	Sleep(30);
	Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
	SendInput(1, &Input, sizeof(INPUT));
	Sleep(10);
}
