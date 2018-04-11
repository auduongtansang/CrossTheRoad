#include "Console.h"

void BufferSize(int &width, int &height)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	width = csbi.srWindow.Right + 1;
	height = csbi.srWindow.Bottom + 1;
}

void Goto(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void CursorStatus(DWORD size, BOOL visible)
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = size;
	cci.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void ResizingOff(void)
{
	HWND curWindow = GetConsoleWindow();
	LONG style = GetWindowLong(curWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(curWindow, GWL_STYLE, style);
}

void BufferInit(Buffer &buffer)
{
	int consoleHeight, consoleWidth;
	BufferSize(consoleHeight, consoleWidth);

	buffer.resize(consoleWidth);
	for (int x = 0; x < consoleWidth; x++)
	{
		buffer[x].resize(consoleHeight);
		for (int y = 0; y < consoleHeight; y++)
		{
			buffer[x][y] = ' ';
		}
	}

	//Border
	buffer[0][0] = (char)(201);
	buffer[consoleWidth / 2 - 1][0] = (char)(187);
	buffer[0][consoleHeight - 1] = (char)(200);
	buffer[consoleWidth / 2 - 1][consoleHeight - 1] = (char)(188);
	for (int x = 1; x < consoleWidth / 2 - 1; x++)
	{
		buffer[x][0] = buffer[x][consoleHeight - 1] = (char)(205);
	}
	for (int y = 1; y < consoleHeight - 1; y++)
	{
		buffer[0][y] = buffer[consoleWidth / 2 - 1][y] = (char)(186);
	}
}

void BufferPrint(Buffer &buffer)
{
	int consoleHeight, consoleWidth;
	BufferSize(consoleHeight, consoleWidth);

	Goto(0, 0);
	for (int y = 0; y < consoleHeight; y++)
	{
		for (int x = 0; x < consoleWidth / 2; x++)
		{
			putchar(buffer[x][y]);	//Print
			if (x != 0 && x != consoleWidth / 2 - 1 && y != 0 && y != consoleHeight - 1)
			{
				buffer[x][y] = ' ';		//Reset
			}
		}
		if (y < consoleHeight - 1)
			putchar('\n');
	}
}