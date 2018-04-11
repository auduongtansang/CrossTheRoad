#ifndef _game_h
#define _game_h_

#include <Windows.h>
#include <thread>
#include "People.h"
#include "Cars.h"

void GameInit(People &people, Peoples &finished, Cars &cars, Buffer &buffer, bool &isAlive);
void GamePause(HANDLE thread);
void GameEnd(HANDLE thread);
void GameOver(bool &isAlive);
bool Impact(People people, Cars cars, Peoples finished);

#endif // !_game_h
