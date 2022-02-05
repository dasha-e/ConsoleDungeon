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
	static int const nScreenWidth = 120;			// Ширина консольного окна (колонки)
	static int const nScreenHeight = 40;			// Высота консольного окна (строки)
	static int const nMapWidth = 16;				// Ширина поля
	static int const nMapHeight = 16;			// Высота поля

	static float const fViewAngle;	// Угол обзора (поле видимости)
	static float const fDepth;			// Максимальная дистанция обзора
	static float const fSpeed;			// Скорость передвижения

	float fPlayerX;			// Координата игрока по оси X
	float fPlayerY;			// Координата игрока по оси Y
	float fPlayerA;			// Направление игрока
	
	void SetDungeonColor(int number);

	void Rotation(float fElapsedTime); //обработка поворота: A - вправо, D - влево

	bool GetOutOfDungeon();//выход

	void Movements(Map map, float fElapsedTime);//обработка движений и столкновений: W- вперед, S - назад. Если столкнулись с стеной - шаг назад.

	void DisplayMap(wchar_t *screen, Map map);

	void DisplayStats(float fElapsedTime, wchar_t *screen);
public:
	Dungeon()
	{
		// Стартовое положение
		fPlayerX = 14.7f;
		fPlayerY = 5.09f;
		fPlayerA = 0.0f;
	}

	bool GoToDungeon(int number);
};
#endif // !DUNGEON_H