#ifndef _console_h_
#define _console_h_

#include <Windows.h>
#include <vector>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

typedef vector< vector<char> > Buffer;

void BufferSize(int &width, int &height);
void Goto(int x, int y);
void DeleteLine(int pos, int line);
void CursorStatus(DWORD size, BOOL visible);
void ResizingOff(void);
void BufferInit(Buffer &buffer);
void BufferPrint(Buffer &buffer);

#endif // !_console_h_
