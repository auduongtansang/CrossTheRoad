#include <iostream>
#include <thread>
#include "Console.h"
#include "People.h"
#include "Cars.h"
#include "Game.h"
#include "Data.h"
#include "Menu.h"

using namespace std;

People people;
Peoples finished;
Cars cars;
Buffer buffer;
bool isAlive;

void GameStart(void)
{
	GameInit(people, finished, cars, buffer, isAlive);
	while (1)
	{
		if (isAlive)
		{
			FinishedDraw(finished, buffer);
			CarsDraw(cars, buffer);
			PeopleDraw(people, buffer);


		}
	}
}

int main(void)
{
	return 0;
}