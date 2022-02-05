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
	static int const nScreenWidth = 120;			// ������ ����������� ���� (�������)
	static int const nScreenHeight = 40;			// ������ ����������� ���� (������)
	static int const nMapWidth = 16;				// ������ ����
	static int const nMapHeight = 16;			// ������ ����

	static float const fViewAngle;	// ���� ������ (���� ���������)
	static float const fDepth;			// ������������ ��������� ������
	static float const fSpeed;			// �������� ������������

	float fPlayerX;			// ���������� ������ �� ��� X
	float fPlayerY;			// ���������� ������ �� ��� Y
	float fPlayerA;			// ����������� ������
	
	void SetDungeonColor(int number);

	void Rotation(float fElapsedTime); //��������� ��������: A - ������, D - �����

	bool GetOutOfDungeon();//�����

	void Movements(Map map, float fElapsedTime);//��������� �������� � ������������: W- ������, S - �����. ���� ����������� � ������ - ��� �����.

	void DisplayMap(wchar_t *screen, Map map);

	void DisplayStats(float fElapsedTime, wchar_t *screen);
public:
	Dungeon()
	{
		// ��������� ���������
		fPlayerX = 14.7f;
		fPlayerY = 5.09f;
		fPlayerA = 0.0f;
	}

	bool GoToDungeon(int number);
};
#endif // !DUNGEON_H