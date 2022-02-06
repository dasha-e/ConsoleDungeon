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
		SetConsoleTextAttribute(hStdOut, 14); // yellow
		break;
	case 2:
		SetConsoleTextAttribute(hStdOut, 2); //green 
		break;
	case 3:
		SetConsoleTextAttribute(hStdOut, 4); //red
		break;
	case 4:
		SetConsoleTextAttribute(hStdOut, 1); // blue
		break;
	case 5:
		SetConsoleTextAttribute(hStdOut, 6); // brown
		break;
	case 6:
		SetConsoleTextAttribute(hStdOut, 3); // cyan
		break;
	case 7:
		SetConsoleTextAttribute(hStdOut, 13); // pink
		break;
	default:
		SetConsoleTextAttribute(hStdOut, 15); // white
		break;
	}
}

void Dungeon::Rotation(float fElapsedTime) // rotation processing: A - left, D - right
{
	float sign = 0;
	if (GetAsyncKeyState((unsigned short)'A') & 0x8000) sign = -1.f;
	if (GetAsyncKeyState((unsigned short)'D') & 0x8000) sign = 1.f;

	fPlayerA += sign * (fSpeed * 0.75f) * fElapsedTime;
}

bool Dungeon::GetOutOfDungeon() // to get out of dungeon press Q
{
	return (GetAsyncKeyState((unsigned short)'Q'));
}

void Dungeon::Movements(Map map, float fElapsedTime) // moving and collision processing: W- forward, S - bckward
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
	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight]; // buffer array
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // Áóôåð ýêðàíà
	SetConsoleActiveScreenBuffer(hConsole); // console setup
	DWORD dwBytesWritten = 0; // debug
	Map map(number);
	// elapsed time count
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
			float fRayAngle = (fPlayerA - fViewAngle / 2.0f) + ((float)x / (float)nScreenWidth) * fViewAngle; // ray direction

			float fStepSize = 0.1f;		  // ray step										
			float fDistanceToWall = 0.0f; // distance to obstacle in direction fRayAngle

			bool bHitWall = false;		// ray hits a wall block
			bool bBoundary = false;		// ray hits between a wall blocks

			float fEyeX = sinf(fRayAngle); // X coordinate of the unit vector fRayAngle
			float fEyeY = cosf(fRayAngle); // Y coordinate of the unit vector fRayAngle

			// throwing the ray until it hits the wall or goes out of the map
			while (!bHitWall && fDistanceToWall < fDepth)
			{
				fDistanceToWall += fStepSize;
				int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
				int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

				// checking if the ray went outside the map
				if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
				{
					bHitWall = true;			// if ray went out of the map, recording a collision at a distance of visibility
					fDistanceToWall = fDepth;
				}
				else
				{
					// ray inside the map, checking if the hitting point is a wall block
					if (map.field.c_str()[nTestX * nMapWidth + nTestY] == '#')
					{
						// ray hitted the wall block
						bHitWall = true;

						// display edges
						vector<pair<float, float>> p;

						for (int tx = 0; tx < 2; tx++)
							for (int ty = 0; ty < 2; ty++)
							{
								float vy = (float)nTestY + ty - fPlayerY; //Y coordinate of the vector going from the observer to the edge
								float vx = (float)nTestX + tx - fPlayerX; //X coordinate of the vector going from the observer to the edge
								float d = sqrt(vx*vx + vy * vy); // The length of the vector from the observer to the edge
								float dot = (fEyeX * vx / d) + (fEyeY * vy / d); // Scalar product of unit vectors v and fRayAngle
								p.push_back(make_pair(d, dot)); // saving result to array
							}

						// Sort edges from nearest to farhtest
						sort(p.begin(), p.end(), [](const pair<float, float> &left, const pair<float, float> &right) 
						{return left.first < right.first; });

						// display 2 or 3 edges
						float fBound = 0.01; // angle when we begin to see the edge
						if (acos(p.at(0).second) < fBound) bBoundary = true;
						if (acos(p.at(1).second) < fBound) bBoundary = true;
						if (acos(p.at(2).second) < fBound) bBoundary = true;
					}
				}
			}

			// сalculating the distance to the floor and ceiling
			int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
			int nFloor = nScreenHeight - nCeiling;

			// Display walls by distance to them
			short nShade = ' ';
			if (fDistanceToWall <= fDepth / 4.0f)			nShade = 0x2588; // nearest	
			else if (fDistanceToWall < fDepth / 3.0f)		nShade = 0x2593;
			else if (fDistanceToWall < fDepth / 2.0f)		nShade = 0x2592;
			else if (fDistanceToWall < fDepth)			nShade = 0x2591;
			else							nShade = ' ';	 // farthest

			if (bBoundary)		nShade = '|'; // edges

			for (int y = 0; y < nScreenHeight; y++)
			{
				// For each console line
				if (y <= nCeiling) // celling
					screen[y*nScreenWidth + x] = ' ';
				else if (y > nCeiling && y <= nFloor)
					screen[y*nScreenWidth + x] = nShade;
				else // floor
				{
					float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
					if (b < 0.75)		nShade = '.';
					else if (b < 0.9)	nShade = '-';
					else			nShade = ' ';
					screen[y*nScreenWidth + x] = nShade;
				}
			}
		}
		DisplayStats(fElapsedTime, screen);
		DisplayMap(screen, map);
		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten); //display dungeoun
		out = GetOutOfDungeon();
	}
	delete[] screen;
	return out;
}
