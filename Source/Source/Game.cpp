#include "Game.h"

void GameInit(People &people, Peoples &finished, Cars &cars, Buffer &buffer, bool &isAlive)
{
	PeopleInit(people);
	finished.resize(0);
	CarsInit(cars);
	BufferInit(buffer);
	isAlive = true;

	CursorStatus(100, FALSE);
	ResizingOff();
}

void GamePause(HANDLE thread)
{
	SuspendThread(thread);
}

void GameOver(bool &isAlive)
{
	isAlive = false;
}

void GameEnd(HANDLE thread)
{
	TerminateThread(thread, 0);
}

bool Impact(People people, Cars cars, Peoples finished)
{
	for (int i = 0; i < (int)(cars.size()); i++)
	{
		for (int j = 0; j < (int)(cars[i].node.size()); j++)
		{
			if (people.position.X == cars[i].node[j].X &&
				people.position.Y == cars[i].node[j].Y)
			{
				return true;
			}
		}
	}

	for (int i = 0; i < (int)(finished.size()); i++)
	{
		if (people.position.X == finished[i].position.X &&
			people.position.Y == finished[i].position.Y)
		{
			return true;
		}
	}

	return false;
}