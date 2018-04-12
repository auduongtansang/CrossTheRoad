#include "People.h"

void PeopleInit(People &people)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	people.position.X = consoleWidth / 4 - 2;
	people.position.Y = consoleHeight - 5;
	people.character = 'X';
}

void PeopleMove(People &people, int key)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	if (key == 'w' && people.position.Y > 1)
	{
		people.position.Y--;
	}
	else if (key == 'a' && people.position.X > 1)
	{
		people.position.X--;
	}
	else if (key == 'd' && people.position.X < consoleWidth / 2 - 2)
	{
		people.position.X++;
	}
	else if (key == 's' && people.position.Y < consoleHeight - 2)
	{
		people.position.Y++;
	}
}

void PeopleDraw(People people, Buffer &buffer)
{
	buffer[people.position.X][people.position.Y] = people.character;
}

void FinishedDraw(Peoples finished, Buffer &buffer)
{
	for (int i = 0; i < (int)(finished.size()); i++)
	{
		PeopleDraw(finished[i], buffer);
	}
}

void PeopleFinised(People &people, Peoples &finished)
{
	finished.push_back(people);
	PeopleInit(people);
}