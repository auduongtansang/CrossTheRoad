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
int level = 1;
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
				level++;
				char s[3];
				strcpy_s(s, 3, "00");
				s[1] = (level % 10) + 48;
				s[0] = (level / 10) + 48;
				Goto(3 * consoleWidth / 4 - 4, consoleHeight / 2 - 3);
				cout << "Level: " << s;
			}

			if (Impact(people, cars, finished))
			{
				OverMenu();
				GameOver(isAlive);
			}

			BufferPrint(buffer);
			Sleep(25);

		}
	}
}

void GameControl(void)
{
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
		key = _getch();
		if (isAlive)
		{
			if (!isAlive)
			{
				continue;
			}

			if (key == 27)
			{
				GameOver(isAlive);
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
			GamePause(dupGameID);

			if (key == 13)
			{
				int consoleWidth, consoleHeight;
				BufferSize(consoleWidth, consoleHeight);
				GamePause(dupGameID);
				int rate = 0;
				DeleteLine(consoleWidth / 2, consoleHeight / 2 - 3);
				DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
				DeleteLine(consoleWidth / 2, consoleHeight / 2);
				DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
				DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
				Goto(3 * consoleWidth / 4 - 12, consoleHeight / 2);
				cout << "Press any key to continue.";

				while (1)
				{
					rate = (rate + 1) % 2;
					if (rate)
					{
						Goto(people.position.X, people.position.Y);
						putchar(177);
					}
					else
					{
						Goto(people.position.X, people.position.Y);
						putchar(people.character);
					}
					Sleep(110);
					if (_kbhit())
					{
						key = _getch();
						break;
					}
				}
				return;
			}
			else if (key == 's')
			{
				int consoleWidth, consoleHeight;
				BufferSize(consoleWidth, consoleHeight);

				DeleteLine(consoleWidth / 2, consoleHeight / 2 - 3);
				SaveFile();
				char s[100];
				gets_s(s, 100);
				SaveData(s, people, finished, cars, buffer, isAlive, level);
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

newgame:

	BufferInit(buffer);
	BufferPrint(buffer);

	MainMenu();

	char k;
	cin >> k;
	rewind(stdin);
	if (k == '1')
	{
		GameMenu();
		Goto(3 * consoleWidth / 4 - 4, consoleHeight / 2 - 3);
		cout << "Level: 01";
		turn++;
		GameInit(people, finished, cars, buffer, isAlive, level);
		GameControl();
		goto newgame;
	}
	else if (k == '2')
	{
		CursorStatus(1, FALSE);
		BufferPrint(buffer);
		LoadFile();
		char s[100];
		rewind(stdin);
		gets_s(s, 100);
		if (LoadData(s, people, finished, cars, buffer, isAlive, level))
		{
			GameMenu();
			char s[3];
			strcpy_s(s, 3, "00");
			s[1] = (level % 10) + 48;
			s[0] = (level / 10) + 48;
			Goto(3 * consoleWidth / 4 - 4, consoleHeight / 2 - 3);
			cout << "Level: " << s;
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
		ExitMenu();
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
