#include "UIKit.h"
#define VERSION_CPP 20191123
#if VERSION_CPP != VERSION_H
#error "different versions"
#endif

#include <windows.h>
#include <iostream>
using namespace std;

HANDLE UIKit::handle = GetStdHandle(STD_OUTPUT_HANDLE);
bool UIKit::isPaletteReset = false;

void UIKit::resetPalette() {
	isPaletteReset = true;

	const short value[3] = { 0, 128, 255 };

	CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
	csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(handle, &csbiex);

	for (int index = 0; index < 16; index++) {
		int r = (index & FOREGROUND_RED) >> 2, g = (index & FOREGROUND_GREEN) >> 1, b = (index & FOREGROUND_BLUE);
		if (index & FOREGROUND_INTENSITY) { r <<= 1; g <<= 1; b <<= 1; }
		csbiex.ColorTable[index] = RGB(value[r], value[g], value[b]);
	}

	SetConsoleScreenBufferInfoEx(handle, &csbiex);
}

/**************************
set the text color
***************************/
void UIKit::color(unsigned short theColor)
{
	if (!isPaletteReset) {
		resetPalette();
	}
	SetConsoleTextAttribute(handle, theColor);
}

//positions the cursor on screen
// x= column, y=row : position 0,0 is the top left corner
void UIKit::gotoXY(int x, int y)
{
	cout.flush();	//	displays pending characters in the stream
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(handle, position);
}

//  returns the character found at column x, row y
char UIKit::getCharXY(int x, int y)
{
	CHAR_INFO buffer;
	COORD dwBufferSize = { 1, 1 };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT readRegion;

	readRegion.Top = readRegion.Bottom = y;
	readRegion.Left = readRegion.Right = x;

	if (!ReadConsoleOutput(handle, &buffer, dwBufferSize, dwBufferCoord, &readRegion))
	{
		printf("ReadConsoleOutput failed - (%d)\n", GetLastError());
		return 1;
	}

	return buffer.Char.AsciiChar;
}

/*************************
set the console window dimensions relative to the default settings
**************************/
void UIKit::setWindowDimensions(int x1, int y1, int x2, int y2)
{
	COORD position, max;
	position.X = x2 + 1;
	position.Y = y2 + 1;

	//verify the max possible size
	//clip requested dimensions if larger
	max = GetLargestConsoleWindowSize(handle);
	if (position.X > max.X)
	{
		position.X = max.X;
		x2 = max.X - 1;
	}
	if (position.Y > max.Y)
	{
		position.Y = max.Y;
		y2 = max.Y - 1;
	}
	SetConsoleScreenBufferSize(handle, position);

	const SMALL_RECT window = { x1, y1, x2, y2 };
	SetConsoleWindowInfo(handle, true, &window);
}

//draws a rectangular frame on the screen
// x1,y1 upper left corner
// x2,y2 lower right corner
// color the color of the frame, see color codes aboves
void UIKit::frame(int cd, int ld, int cf, int lf, int set_color)
{
	color(set_color);  //defines the frame color

	gotoXY(cd, ld);
	cout << (char)201;  //upper left corner
	for (int i = cd + 1; i < cf; i++)
		cout << (char)205; //upper horizontal line
	cout << (char)187;  //upper right corner
	for (int i = ld + 1; i < lf; i++)
	{
		gotoXY(cd, i);
		cout << (char)186;  //left vertical line
		gotoXY(cf, i);
		cout << (char)186;  //right vertical line
	}
	gotoXY(cd, lf);
	cout << (char)200;  //lower left corner
	for (int i = cd + 1; i < cf; i++)
		cout << (char)205;  //lower horizontal line
	cout << (char)188;  //lower right corner
}

/* returns the current cursor horizontal position X (column)*/
int UIKit::whereX()
{
	cout.flush();
	CONSOLE_SCREEN_BUFFER_INFO buffer;
	GetConsoleScreenBufferInfo(handle, &buffer);
	return buffer.dwCursorPosition.X;
}

/* returns the current cursor vertical position Y (row)*/
int UIKit::whereY()
{
	cout.flush();
	CONSOLE_SCREEN_BUFFER_INFO buffer;
	GetConsoleScreenBufferInfo(handle, &buffer);
	return buffer.dwCursorPosition.Y;
}

/*
	Makes the cursor visible or invisible
	Input: visible = the cursor should be set to visible (true ou false)
*/
void UIKit::visibleCursor(bool visible)
{
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(handle, &cursor);
	cursor.bVisible = visible;
	SetConsoleCursorInfo(handle, &cursor);
}
