
#include<iostream>
#include<Windows.h>
#include<gameux.h>
#include<winapifamily.h>
#include<gameux.h>

DWORD ReadCPUSpeed();
bool checkHDD();
bool checkRAM();
void initInstance();

using namespace std;

class thisProgram{};

int main() {

	//Check if this program is already running
	CreateMutex(0, FALSE, "Local\\$myprogram$");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		cout << "Program is already running!" << endl << endl;
		system("pause");
		return 0;
	}
	else
	{
		cout << "Program Starting!" << endl << endl;
	}

	//Run initialization functions
	initInstance();

	//Pause before the program terminates
	system("pause");
	return 0;
}

void initInstance()
{
	//Output the cpu's speed
	cout << "CPU: ";
	cout << ReadCPUSpeed() << "Ghz" << endl;

	//Check for available space
	if (checkHDD == false)
		cout << "No available space, please make some" << endl;
	else
		cout << "You have enough space" << endl;

	if (checkRAM() == false)
		cout << "You dont have either the required physical or virtual RAM" << endl;
	else
		cout << "You have enough dedidated WAM!! Please wait..." << endl << endl;
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
	float Ghz = (float)dwMHz;
	dwMHz = (Ghz / 1000.f);
	return dwMHz;
}

bool checkHDD()
{
	__int64 available;
	__int64 total;
	__int64 free;
	GetDiskFreeSpaceEx(NULL, (PULARGE_INTEGER)&available, (PULARGE_INTEGER)&total, (PULARGE_INTEGER)&free);

	if ((available / (1024 * 1024)) < 200)
		return false;
	else
		return true;

}
bool checkRAM()
{
	MEMORYSTATUSEX ram;
	ram.dwLength = sizeof(ram);
	GlobalMemoryStatusEx(&ram);

	if (ram.ullTotalPhys < 100000)
		return false;
	else
		return true;

	if (ram.ullTotalVirtual < 600000)
		return false;
	else
		return true;
}