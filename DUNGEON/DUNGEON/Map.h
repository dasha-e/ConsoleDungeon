#pragma once
#ifndef MAP_H
#include <iostream>
using namespace std;

class Map {
public:
	wstring field;

	Map(int number)
	{
		switch (number)
		{
		case 1:
		{
			field += L"#########.......";
			field += L"#...............";
			field += L"#.......########";
			field += L"#..............#";
			field += L"#......##......#";
			field += L"#......##......#";
			field += L"#..............#";
			field += L"###............#";
			field += L"##.............#";
			field += L"#......####..###";
			field += L"#......#.......#";
			field += L"#......#.......#";
			field += L"#..............#";
			field += L"#......#########";
			field += L"#..............#";
			field += L"################";
			break;
		}
		case 2:
		{
			field += L"##############..";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#############..#";
			field += L"#..............#";
			field += L"#..#############";
			field += L"#..............#";
			field += L"#############..#";
			field += L"#..............#";
			field += L"#..#############";
			field += L"#..............#";
			field += L"############...#";
			field += L"#..............#";
			field += L"#..#############";
			field += L"#..............#";
			field += L"################";
			break;
		}
		case 3:
		{
			field += L"############...#";
			field += L"#..............#";
			field += L"#..##..........#";
			field += L"#..##....#######";
			field += L"#........##....#";
			field += L"#........##....#";
			field += L"#..............#";
			field += L"##########...###";
			field += L"#.......##.....#";
			field += L"#...#...##.....#";
			field += L"#...#...##.....#";
			field += L"#...#...##.....#";
			field += L"#...#..........#";
			field += L"#...############";
			field += L"#..............#";
			field += L"################";
			break;
		}
		case 4:
		{
			field += L"########..######";
			field += L"#.........#....#";
			field += L"#....######....#";
			field += L"#....##........#";
			field += L"#....######....#";
			field += L"#....######....#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"##########.....#";
			field += L"#...######.....#";
			field += L"#..............#";
			field += L"#....###########";
			field += L"#.........#....#";
			field += L"#....######....#";
			field += L"#..............#";
			field += L"################";
			break;
		}
		case 5:
		{
			field += L"################";
			field += L"#..............#";
			field += L"#...########...#";
			field += L"#...#......#...#";
			field += L"#...#..#...#...#";
			field += L"#...#..#...#...#";
			field += L"#...#..#...#...#";
			field += L"#...#..#...#...#";
			field += L"#...#..#...#...#";
			field += L"#...#..#...#...#";
			field += L"#...#..#...#...#";
			field += L"#...#..#####...#";
			field += L"#...#..........#";
			field += L"#...############";
			field += L"#..............#";
			field += L"################";
			break;
		}
		case 6:
		{
			field += L"###########....#";
			field += L"########.......#";
			field += L"######........##";
			field += L"####........####";
			field += L"##........######";
			field += L"#.......########";
			field += L"#.....##########";
			field += L"#.......########";
			field += L"#.........######";
			field += L"#...........####";
			field += L"#......##.....##";
			field += L"#.....####.....#";
			field += L"#...########...#";
			field += L"#...########...#";
			field += L"#..............#";
			field += L"################";
			break;
		}

		case 7:
		{
			field += L"#...############";
			field += L"#..............#";
			field += L"###########....#";
			field += L"###########....#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#.....##########";
			field += L"#.....##.......#";
			field += L"#.....##.......#";
			field += L"#.....#####....#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#######........#";
			field += L"#....##........#";
			field += L"#..............#";
			field += L"################";
			break;
		}

		default:
		{
			field += L"################";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"#..............#";
			field += L"################";
			break;
		}
		}
	}
	
};
#endif // !MAP_H

