#include <iostream>
#include <thread>
#include <time.h>
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
int turn = 0;

void GameStart(void)
{
	while (1)
	{
		if (isAlive)
		{
			FinishedDraw(finished, buffer);
			CarsMove(cars);
			CarsDraw(cars, buffer);
			PeopleDraw(people, buffer);

			if (people.position.Y == 1)
			{
				PeopleFinised(people, finished);
				PeopleDraw(people, buffer);
			}

			BufferPrint(buffer);
			Sleep(50);

			if (Impact(people, cars, finished))
			{
				GameOver(isAlive);
			}
		}
	}
}

void GameControl(void)
{
	srand((unsigned int)(time(NULL)));
	thread GameThread;
	if (turn == 1)
	{
		GameThread = thread(GameStart);
		GameThread.detach();
	}
	else
	{
		ResumeThread((HANDLE)GameThread.native_handle());
	}
	int pause = 0;
	while (1)
	{
		int key = tolower(_getch());
		if (isAlive)
		{
			if (key == 27)
			{
				GamePause(GameThread.native_handle());
				return;
			}
			else if (key == 32 && pause == 0)
			{
				GamePause(GameThread.native_handle());
				pause = (pause + 1) % 2;
			}
			else if (key == 32 && pause == 1)
			{
				ResumeThread((HANDLE)(GameThread.native_handle()));
				pause = (pause + 1) % 2;
			}
			else
			{
				PeopleMove(people, key);
			}
		}
		else
		{
			if (key == 13)
			{
				GamePause(GameThread.native_handle());
				return;
			}
			else if (key == 'n')
			{
				GameInit(people, finished, cars, buffer, isAlive);
			}
		}
	}
}

int main(void)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	BufferInit(buffer);
	

newgame :

	BufferPrint(buffer);
	Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 - 1);
	cout << "1 - New game";
	Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2);
	cout << "2 - Load game";
	Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 1);
	cout << "3 - Exit";
	Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 2);
	cout << "Your choice: ";
	CursorStatus(1, TRUE);

	char k;
	cin >> k;
	rewind(stdin);
	if (k == '1')
	{
		turn++;
		GameInit(people, finished, cars, buffer, isAlive);
		GameControl();
		goto newgame;
	}
	else if (k == '2')
	{
		BufferPrint(buffer);
		DeleteLine(3 * consoleWidth / 4 - 10, consoleHeight / 2 - 1);
		DeleteLine(3 * consoleWidth / 4 - 10, consoleHeight / 2);
		DeleteLine(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 1);
		DeleteLine(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 2);
		Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2);
		cout << "Enter filename (ex. your-file.bin) to load: ";
		Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 1);
		char s[100];
		rewind(stdin);
		gets_s(s, 100);
		if (LoadData(s, people, finished, cars, buffer, isAlive))
		{
			GameControl();
			goto newgame;
		}
		else
		{
			DeleteLine(3 * consoleWidth / 4 - 20, consoleHeight / 2);
			Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2);
			cout << "File does not exist! Press any to continue.";
			_getch();
			DeleteLine(3 * consoleWidth / 4 - 20, consoleHeight / 2);
			goto newgame;
		}
	}
	else if (k == '3')
	{
		BufferPrint(buffer);
		DeleteLine(3 * consoleWidth / 4 - 10, consoleHeight / 2 - 1);
		DeleteLine(3 * consoleWidth / 4 - 10, consoleHeight / 2);
		DeleteLine(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 1);
		DeleteLine(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 2);
		Goto(3 * consoleWidth / 4 - 5, consoleHeight / 2);
		cout << "Good bye!";
		_getch();
		return 0;
	}
	else
	{
		BufferPrint(buffer);
		Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 2);
		cout << "You must type a number from 1 to 3.";
		_getch();
		DeleteLine(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 2);
		goto newgame;
	}

	return 0;
}