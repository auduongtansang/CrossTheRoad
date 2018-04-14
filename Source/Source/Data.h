#ifndef _data_h_
#define _data_h_

#include <fstream>
#include "Console.h"
#include "People.h"
#include "Cars.h"

bool SaveData(char *s, People people, Peoples finished, Cars cars, Buffer buffer, bool isAlive, int level);
bool LoadData(char *s, People &people, Peoples &finished, Cars &cars, Buffer &buffer, bool &isAlive, int &level);

#endif // !_data_h_
