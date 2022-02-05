#pragma once
#ifndef MENU_H
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>

const short X = 30;
const short Y = 6;
const short ENTER = 13;


HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size) //сокрытие курсора
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show; // изменяем видимость курсора
	structCursorInfo.dwSize = size;   // изменяем размер курсора
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void PrintHere(int x, int y, std::string str)
{
	GoToXY(x, y);
	std::cout << str;
}

void PrintActiveMenu(bool f, std::string str, int x, int y)
{
	if (f) 	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	else SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
	PrintHere(X + x, Y + y, str);
}

short MainMenu()
{
	system("CLS");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
	short active_menu = 0; char key;
	int y = Y;
	PrintHere(X, y++, "_____________________________________________________");
	PrintHere(X, y++, "|                                                   |");
	PrintHere(X, y++, "|        <<  WELCOME TO CONSOLE DUNGEON  >>         |");
	PrintHere(X, y++, "|___________________________________________________|");
	for (int i = 0; i < 6; i++)
		PrintHere(X, y++, "|                                                   |");
	PrintHere(X, y++, "|___________________________________________________|");
	while (1)
	{
		PrintActiveMenu(active_menu == 0, "GUIDE", 23, 5);
		PrintActiveMenu(active_menu == 1, "GO TO DUNGEON", 19, 7);
		PrintActiveMenu(active_menu == 2, " EXIT", 23, 9);
		key = _getch();
		switch (tolower(key))
		{
		case 'w':
			if (active_menu > 0) active_menu--;
			break;
		case 's':
			if (active_menu < 2) active_menu++;
			break;
		case ENTER:
			return active_menu;
		default:
			break;
		}
	}
	return -1;
}

void Guide()
{
	system("CLS");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
	int y = Y;
	PrintHere(X, y++, "_____________________________________________________");
	PrintHere(X, y++, "|                                                   |");
	PrintHere(X, y++, "|                   %  GUIDE  %                     |");
	PrintHere(X, y++, "|___________________________________________________|");
	PrintHere(X, y++, "|                                                   |");
	PrintHere(X, y++, "|1. to go to the dungeon select 'GO TO DUNGEON' in  |");
	PrintHere(X, y++, "|   the menu and input an integer from 1 to 5 to    |");
	PrintHere(X, y++, "|   choose the dungeon.                             |");
	PrintHere(X, y++, "|                                                   |");
	PrintHere(X, y++, "|2. use the WSAD keys to move around the dungeon.   |");
	PrintHere(X, y++, "|                                                   |");
	PrintHere(X, y++, "|3. press Q to return to the menu.                  |");
	PrintHere(X, y++, "|___________________________________________________|");
	while (1)
	{
		if (GetAsyncKeyState((unsigned short)'Q') & 0x8000) break;
	}
}

#endif // !MENU_H

