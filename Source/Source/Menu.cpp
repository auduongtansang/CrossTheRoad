#include "Menu.h"

void MainMenu(void)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
	Goto(3 * consoleWidth / 4 - 6, consoleHeight / 2 - 1);
	cout << "1 - New game";
	Goto(3 * consoleWidth / 4 - 6, consoleHeight / 2);
	cout << "2 - Load game";
	Goto(3 * consoleWidth / 4 - 6, consoleHeight / 2 + 1);
	cout << "3 - Exit";
	Goto(3 * consoleWidth / 4 - 6, consoleHeight / 2 + 2);
	cout << "Your choice: ";
	CursorStatus(1, TRUE);
}

void GameMenu(void)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
	Goto(3 * consoleWidth / 4 - 15, consoleHeight / 2 - 1);
	cout << "W: up, A: left, D: right, S: down.";
	Goto(3 * consoleWidth / 4 - 15, consoleHeight / 2);
	cout << "SPACE to pause/resume.";
	Goto(3 * consoleWidth / 4 - 15, consoleHeight / 2 + 1);
	cout << "ESC + ENTER to return to main menu.";
	Goto(3 * consoleWidth / 4 - 15, consoleHeight / 2 + 2);
	cout << "ESC + S to save game and exit.";
}

void SaveFile(void)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
	Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2);
	cout << "Enter file name (ex. your-file.bin) to save:";
	Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2 + 1);
	CursorStatus(1, TRUE);
}

void LoadFile(void)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
	Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2);
	cout << "Enter filename (ex. your-file.bin) to load: ";
	CursorStatus(1, TRUE);
	Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2 + 1);
}

void ExitMenu(void)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
	Goto(3 * consoleWidth / 4 - 4, consoleHeight / 2);
	cout << "Good bye!";
	_getch();
}

void OverMenu(void)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	DeleteLine(consoleWidth / 2, consoleHeight / 2 - 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 1);
	DeleteLine(consoleWidth / 2, consoleHeight / 2 + 2);
	Goto(3 * consoleWidth / 4 - 4, consoleHeight / 2);
	cout << "Game over!";
	Goto(3 * consoleWidth / 4 - 20, consoleHeight / 2 + 1);
	cout << "Press ENTER to return main menu or S to save file.";
}