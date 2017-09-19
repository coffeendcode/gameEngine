
#include<iostream>
#include<Windows.h>
#include<gameux.h>
#include<winapifamily.h>
#include<gameux.h>

DWORD ReadCPUSpeed();
void initInstance();

using namespace std;
int main() {

	//std::cout << "Hello World!" << std::endl << std::endl;

	initInstance();

	system("pause");
	return 0;
}

void initInstance()
{
	cout << "CPU: ";
	cout << ReadCPUSpeed() << endl << endl;
}

bool IsOnlyInstance(LPCTSTR gameTitle)
{
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);

	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(gameTitle, NULL);
		if (hWnd)
		{
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			return false;
			std::cout << "Game is already Running";
		}
	}
	std::cout << "Game is starting";
	return true;
}

DWORD ReadCPUSpeed() {
	DWORD bufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)&dwMHz, &bufSize);
	}
	return dwMHz;
}