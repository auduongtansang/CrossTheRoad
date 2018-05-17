#include "Cars.h"

void CarsInit(Cars &cars)
{
	int consoleHeight, consoleWidth;
	BufferSize(consoleWidth, consoleHeight);

	int max_car = consoleHeight - 16;
	int max_len = consoleWidth / 5;

	cars.resize(max_car);
	for (int i = 0; i < max_car; i++)
	{
		cars[i].character = (char)(254);
		cars[i].speed = 1;
		int random_pos = rand() % (consoleWidth / 2 - max_len - 2) + 1;
		cars[i].node.resize(max_len);
		for (int j = 0; j < max_len; j++)
		{
			cars[i].node[j].X = random_pos + j;
			cars[i].node[j].Y = i + 8;
		}
	}
}

void CarsMove(Cars &cars)
{
	int consoleWidth, consoleHeight;
	BufferSize(consoleWidth, consoleHeight);

	for (int i = 0; i < (int)(cars.size()); i += 2)
	{
		for (int j = 0; j < (int)(cars[i].node.size()); j++)
		{
			cars[i].node[j].X += cars[i].speed;
			if (cars[i].node[j].X >= consoleWidth / 2 - 1)
			{
				cars[i].node[j].X = cars[i].node[j].X - consoleWidth / 2 + 2;
			}
		}
	}

	for (int i = 1; i < (int)(cars.size()); i += 2)
	{
		for (int j = (int)(cars[i].node.size()) - 1; j >= 0; j--)
		{
			cars[i].node[j].X -= cars[i].speed;
			if (cars[i].node[j].X <= 0)
			{
				cars[i].node[j].X = consoleWidth / 2 + cars[i].node[j].X - 2;
			}
		}
	}
}

void CarsDraw(Cars cars, Buffer &buffer)
{
	for (int i = 0; i < (int)(cars.size()); i++)
	{
		for (int j = 0; j < (int)(cars[i].node.size()); j++)
		{
			buffer[cars[i].node[j].X][cars[i].node[j].Y] = cars[i].character;
		}
	}
}