#include "Menu.h"

void MainMenu(void)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 - 1);
	cout << "1 - New game";
	Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2);
	cout << "2 - Load game";
	Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 1);
	cout << "3 - Exit";
	Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 2);
	cout << "Your choice: ";
	while (1)
	{
		char k;
		cin >> k;
		if (k == '1')
		{
			//Init
			//Start
		}
		else if (k == '2')
		{
			//Load
			//Start
		}
		else if (k == '3')
		{
			return;
		}
		else
		{
			Goto(3 * consoleWidth / 4 - 10, consoleHeight / 2 + 2);
			cout << "You must type a number from 1 to 3: ";
		}
	}
}