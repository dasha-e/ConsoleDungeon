#include <iostream>
#include <windows.h>
#include <SFML/Audio.hpp>
#include "Menu.h"


bool RunProcess(const char *lpApplicationName, DWORD dwWaitMilliseconds)
{

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	si.cb = sizeof(si);
	if (!CreateProcessA(NULL, const_cast<LPSTR>(lpApplicationName), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		std::cout << "CreateProcess failed [" << GetLastError() << "]\n";
		return false;
	}


	WaitForSingleObject(pi.hProcess, dwWaitMilliseconds);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return true;
}

int main()
{
	SetConsoleTitle("CONSOLE DUNGEON");
	ConsoleCursorVisible(false, 100);
	sf::Music music;
	music.openFromFile("music.ogg");
	music.setVolume(30);
	music.setLoop(true);
	music.play();

	std::string pname = "Dungeon.exe";
	bool out = false;
	char number;
	while (!out)
	{

		short option = MainMenu();
		switch (option)
		{
		case 0:
			Guide();
			break;
		case 1:
			RunProcess(pname.c_str(), INFINITE);
			system("CLS");
			break;
		case 2:
			music.stop();
			out = true;
			break;
		default:
			break;
		}
	}
	return 0;
}