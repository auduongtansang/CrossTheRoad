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
int delay = 3;
int gamerate = 0;
int turn = 0;

thread GameThread;
HANDLE GameID, dupGameID;

void GameStart(void)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	while (1)
	{
		if (isAlive)
		{
			gamerate++;
			if (gamerate > 3)
			{
				gamerate = 0;
			}
			FinishedDraw(finished, buffer);
			if (gamerate % delay == 0)
			{
				CarsMove(cars);
			}
			CarsDraw(cars, buffer);
			PeopleDraw(people, buffer);

			if (people.position.Y == 7)
			{
				PeopleFinised(people, finished);
				PeopleDraw(people, buffer);
				delay--;
				if (delay < 1)
				{
					delay = 3;
				}
			}

			BufferPrint(buffer);
			Sleep(25);

			if (Impact(people, cars, finished))
			{
				GameOver(isAlive);
				DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
				DeleteLine(consoleWidth / 2, consoleHeight / 2);
				DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
				DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
				Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2);
				cout << "Game over! Press ENTER to continue.";
			}
		}
	}
}

void GameControl(void)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	if (turn == 1)
	{
		GameThread = thread(GameStart);
		GameID = GameThread.native_handle();
		DuplicateHandle(GetCurrentProcess(), GameID, GetCurrentProcess(), &dupGameID, DUPLICATE_SAME_ACCESS, 1, 0);
		GameThread.detach();
	}
	else
	{
		ResumeThread(dupGameID);
	}
	int pause = 0;

	int key;
	while (1)
	{
		if (isAlive)
		{
			key = _getch();
			if (!isAlive)
			{
				continue;
			}

			if (key == 27)
			{
				isAlive = false;
			}
			else if (key == 32 && pause == 0)
			{
				GamePause(dupGameID);
				pause = (pause + 1) % 2;
			}
			else if (key == 32 && pause == 1)
			{
				ResumeThread(dupGameID);
				pause = (pause + 1) % 2;
			}
			else
			{
				PeopleMove(people, key);
			}
		}
		else
		{
			turn = 0;

			key = _getch();
			if (key == 13)
			{
				GamePause(dupGameID);
				return;
			}
			else if (key == 's')
			{
				GamePause(dupGameID);
				DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
				DeleteLine(consoleWidth / 2, consoleHeight / 2);
				DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
				DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
				Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2);
				cout << "Enter file name (ex. your-file.bin) to save:";
				Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2 + 1);
				CursorStatus(1, TRUE);
				char s[100];
				gets_s(s, 100);
				SaveData(s, people, finished, cars, buffer, isAlive);
				return;
			}
		}
	}
}

int main(void)
{
	srand((unsigned int)(time(NULL)));
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

newgame :

	BufferInit(buffer);
	BufferPrint(buffer);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
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
		DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
		DeleteLine(consoleWidth / 2, consoleHeight / 2);
		DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
		DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
		Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 - 1);
		cout << "W: up, A: left, D: right, S: down.";
		Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2);
		cout << "SPACE to pause/resume.";
		Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 1);
		cout << "ESC + ENTER to return to main menu.";
		Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 2);
		cout << "ESC + S to save game and exit.";

		turn++;
		GameInit(people, finished, cars, buffer, isAlive);
		GameControl();
		goto newgame;
	}
	else if (k == '2')
	{
		CursorStatus(1, FALSE);
		BufferPrint(buffer);
		DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
		DeleteLine(consoleWidth / 2, consoleHeight / 2);
		DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
		DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
		Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2);
		cout << "Enter filename (ex. your-file.bin) to load: ";
		CursorStatus(1, TRUE);
		Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2 + 1);
		char s[100];
		rewind(stdin);
		gets_s(s, 100);
		if (LoadData(s, people, finished, cars, buffer, isAlive))
		{
			DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
			DeleteLine(consoleWidth / 2, consoleHeight / 2);
			DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
			DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
			Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 - 1);
			cout << "W: up, A: left, D: right, S: down.";
			Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2);
			cout << "SPACE to pause/resume.";
			Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 1);
			cout << "ESC + ENTER to return to main menu.";
			Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 2);
			cout << "ESC + S to save game and exit.";

			isAlive = true;
			people.character = 'Y';
			CursorStatus(1, FALSE);
			turn++;
			GameControl();
			goto newgame;
		}
		else
		{
			DeleteLine(consoleWidth / 2, consoleHeight / 2);
			Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2);
			cout << "File does not exist! Press any to continue.";
			_getch();
			DeleteLine(consoleWidth / 2, consoleHeight / 2);
			CursorStatus(1, FALSE);
			goto newgame;
		}
	}
	else if (k == '3')
	{
		CursorStatus(1, FALSE);
		BufferPrint(buffer);
		DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
		DeleteLine(consoleWidth / 2, consoleHeight / 2);
		DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
		DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
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
		DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
		goto newgame;
	}

	return 0;
}