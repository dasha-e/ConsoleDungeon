#pragma once
#include "Dungeon.h"

const float Dungeon::fViewAngle = 3.14159f / 4.0f;
const float Dungeon::fDepth = 16.0f;
const float Dungeon::fSpeed = 2.0f;

void Dungeon::SetDungeonColor(int number)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (number)
	{
	case 1:
		SetConsoleTextAttribute(hStdOut, 14); // желтый
		break;
	case 2:
		SetConsoleTextAttribute(hStdOut, 2); //зеленый 
		break;
	case 3:
		SetConsoleTextAttribute(hStdOut, 4); //красный
		break;
	case 4:
		SetConsoleTextAttribute(hStdOut, 1); // синий
		break;
	case 5:
		SetConsoleTextAttribute(hStdOut, 6); // коричневый
		break;
	case 6:
		SetConsoleTextAttribute(hStdOut, 3); // бирюзовый
		break;
	case 7:
		SetConsoleTextAttribute(hStdOut, 13); //розовый
		break;
	default:
		SetConsoleTextAttribute(hStdOut, 15); //белый
		break;
	}
}

void Dungeon::Rotation(float fElapsedTime) //обработка поворота: A - вправо, D - влево
{
	float sign = 0;
	if (GetAsyncKeyState((unsigned short)'A') & 0x8000) sign = -1.f;
	if (GetAsyncKeyState((unsigned short)'D') & 0x8000) sign = 1.f;

	fPlayerA += sign * (fSpeed * 0.75f) * fElapsedTime;
}

bool Dungeon::GetOutOfDungeon()//выход
{
	return (GetAsyncKeyState((unsigned short)'Q'));
}

void Dungeon::Movements(Map map, float fElapsedTime)//обработка движений и столкновений: W- вперед, S - назад. Если столкнулись с стеной - шаг назад.
{
	float sign = 0;
	if (GetAsyncKeyState((unsigned short)'W') & 0x8000) sign = 1.f;
	if (GetAsyncKeyState((unsigned short)'S') & 0x8000) sign = -1.f;
	fPlayerX += sign * sinf(fPlayerA) * fSpeed * fElapsedTime;;
	fPlayerY += sign * cosf(fPlayerA) * fSpeed * fElapsedTime;;
	if (map.field.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
	{
		fPlayerX -= sign * sinf(fPlayerA) * fSpeed * fElapsedTime;;
		fPlayerY -= sign * cosf(fPlayerA) * fSpeed * fElapsedTime;;
	}
}

void Dungeon::DisplayMap(wchar_t *screen, Map map)
{
	for (int nx = 0; nx < nMapWidth; nx++)
		for (int ny = 0; ny < nMapWidth; ny++)
		{
			screen[(ny + 1)*nScreenWidth + nx] = map.field[ny * nMapWidth + nx];
		}
	screen[((int)fPlayerX + 1) * nScreenWidth + (int)fPlayerY] = 'P';
}

void Dungeon::DisplayStats(float fElapsedTime, wchar_t *screen)
{
	swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f", fPlayerX, fPlayerY, fPlayerA, 1.0f / fElapsedTime);
}

bool Dungeon::GoToDungeon(int number)
{
	SetDungeonColor(number);
	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight]; // Массив для записи в буфер
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // Буфер экрана
	SetConsoleActiveScreenBuffer(hConsole); // Настройка консоли
	DWORD dwBytesWritten = 0; // Для отладки
	Map map(number);
	// Переменные для подсчета пройденного времени
	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	bool out = false;
	while (!out)
	{
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		Rotation(fElapsedTime);

		Movements(map, fElapsedTime);

		for (int x = 0; x < nScreenWidth; x++)
		{
			float fRayAngle = (fPlayerA - fViewAngle / 2.0f) + ((float)x / (float)nScreenWidth) * fViewAngle; //Направление луча

			float fStepSize = 0.1f;		  // Шаг луча										
			float fDistanceToWall = 0.0f; //Расстояние до препятствия в направлении fRayAngle

			bool bHitWall = false;		// Попадание луча в блок стены
			bool bBoundary = false;		// Попадание луча между блоками стен

			float fEyeX = sinf(fRayAngle); // Координата X единичного вектора fRayAngle
			float fEyeY = cosf(fRayAngle); // Координата Y единичного вектора fRayAngle

			// Бросаем луч пока он не достигнет стены или не выйдет за границы карты
			while (!bHitWall && fDistanceToWall < fDepth)
			{
				fDistanceToWall += fStepSize;
				int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
				int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

				// Проверяем не вышел ли луч за пределы карты
				if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
				{
					bHitWall = true;			//  Если мы вышли за карту, фиксируем соударение на расстоянии видимости
					fDistanceToWall = fDepth;
				}
				else
				{
					// Луч внутри карты. Проверяем является ли достигнутая точка стеной
					if (map.field.c_str()[nTestX * nMapWidth + nTestY] == '#')
					{
						// Луч достиг стены
						bHitWall = true;

						// Отображение ребер
						vector<pair<float, float>> p;

						for (int tx = 0; tx < 2; tx++)
							for (int ty = 0; ty < 2; ty++)
							{
								float vy = (float)nTestY + ty - fPlayerY; //Координата Y вектора идущего от наблюдателя к ребру
								float vx = (float)nTestX + tx - fPlayerX; //Координата X вектора идущего от наблюдателя к ребру
								float d = sqrt(vx*vx + vy * vy); // Длина вектора идущего от наблюдателя к ребру
								float dot = (fEyeX * vx / d) + (fEyeY * vy / d); // Скалярное произведение единичных векторов v и fRayAngle
								p.push_back(make_pair(d, dot)); // Сохраняем результат в массив
							}

						// Сортируем ребра от ближнего к дальнему
						sort(p.begin(), p.end(), [](const pair<float, float> &left, const pair<float, float> &right) 
						{return left.first < right.first; });

						// Отобразим первые 2 или 3 ребра
						float fBound = 0.01; // Угол, при котором начинаем различать ребро
						if (acos(p.at(0).second) < fBound) bBoundary = true;
						if (acos(p.at(1).second) < fBound) bBoundary = true;
						if (acos(p.at(2).second) < fBound) bBoundary = true;
					}
				}
			}

			// Вычисляем расстояние до пола и потолка
			int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
			int nFloor = nScreenHeight - nCeiling;

			// Отображаем стены в зависимости от расстояния до них
			short nShade = ' ';
			if (fDistanceToWall <= fDepth / 4.0f)			nShade = 0x2588;	// Чем ближе, тем светлее	
			else if (fDistanceToWall < fDepth / 3.0f)		nShade = 0x2593;
			else if (fDistanceToWall < fDepth / 2.0f)		nShade = 0x2592;
			else if (fDistanceToWall < fDepth)				nShade = 0x2591;
			else											nShade = ' ';		// Чем дальше, тем темнее

			if (bBoundary)		nShade = '|'; // Выделение ребер

			for (int y = 0; y < nScreenHeight; y++)
			{
				// Для каждой строки консоли
				if (y <= nCeiling) // Потолок
					screen[y*nScreenWidth + x] = ' ';
				else if (y > nCeiling && y <= nFloor)
					screen[y*nScreenWidth + x] = nShade;
				else // Пол
				{
					float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
					if (b < 0.75)		nShade = '.';
					else if (b < 0.9)	nShade = '-';
					else				nShade = ' ';
					screen[y*nScreenWidth + x] = nShade;
				}
			}
		}
		DisplayStats(fElapsedTime, screen);
		DisplayMap(screen, map);
		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		out = GetOutOfDungeon();
	}
	delete[] screen;
	return out;
}