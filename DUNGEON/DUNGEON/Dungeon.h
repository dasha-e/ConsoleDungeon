#pragma once
#ifndef DUNGEON_H
#define UNICODE
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <conio.h>
#include <Windows.h>

#include "Map.h"

class Dungeon {
private:
	static int const nScreenWidth = 120;	// columns
	static int const nScreenHeight = 40;	// rows
	static int const nMapWidth = 16; 	
	static int const nMapHeight = 16;	

	static float const fViewAngle;	// viewing angle (visibility area)
	static float const fDepth;	// maximum viewing distance
	static float const fSpeed;	// walking speed

	float fPlayerX;			// X coordinate of player
	float fPlayerY;			// Y coordinate of player
	float fPlayerA;			// players direction
	
	void SetDungeonColor(int number);

	void Rotation(float fElapsedTime);

	bool GetOutOfDungeon();

	void Movements(Map map, float fElapsedTime);

	void DisplayMap(wchar_t *screen, Map map);

	void DisplayStats(float fElapsedTime, wchar_t *screen);
public:
	Dungeon()
	{
		// starting position
		fPlayerX = 14.7f;
		fPlayerY = 5.09f;
		fPlayerA = 0.0f;
	}

	bool GoToDungeon(int number);
};
#endif // !DUNGEON_H
