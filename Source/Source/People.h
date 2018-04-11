#ifndef _people_h_
#define _people_h_

#include <Windows.h>
#include <vector>
#include "Console.h"

struct People
{
	COORD position;
	char character;
};

typedef vector<People> Peoples;

void PeopleInit(People &people);
void PeopleMove(People &people, int key);
void PeopleDraw(People people, Buffer &buffer);
void FinishedDraw(Peoples finished, Buffer &buffer);
void PeopleFinised(People &people, Peoples &finished);

#endif // !_people_h_
