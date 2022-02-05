#include "Dungeon.h"
#include <stdlib.h>


int main()
{
	srand(time(NULL));
	int number = rand() % 7 + 1;
	Dungeon dung;
	dung.GoToDungeon(number);
	return 1;
}