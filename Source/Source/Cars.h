#ifndef _cars_h_
#define _cars_h_

#include <Windows.h>
#include <vector>
#include "Console.h"

using namespace std;

struct Car
{
	vector<COORD> node;
	char character;
	int speed;
};

typedef vector<Car> Cars;

void CarsInit(Cars &cars);
void CarsMove(Cars &cars);
void CarsDraw(Cars cars, Buffer &buffer);

#endif // !_cars_h_
