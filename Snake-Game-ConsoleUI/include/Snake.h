#pragma once

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <iterator>

using namespace std;

//============================================================
// "extern" keyword is used to avoid multiple definitions
// it makes variables visible to other source files that want
// to use them but variables are only defined in one place
// In this case, these variables are defined in Snake.cpp

extern const int	KEY_ESC;
extern const int	KEY_UP[];
extern const int	KEY_DOWN[];
extern const int	KEY_LEFT[];
extern const int	KEY_RIGHT[];
extern const int	KEY_SELECT[];

// Functions define

// Checks if a given x is in KEY_UP[]
bool isUpKey(int x);
// Checks if a given x is in KEY_DOWN[]
bool isDownKey(int x);
// Checks if a given x is in KEY_LEFT[]
bool isLeftKey(int x);
// Checks if a given x is in KEY_RIGHT[]
bool isRightKey(int x);
// Checks if a given x is in KEY_SELECT[]
bool isSelectKey(int x);
int Random(int n);
void Colour(int n);
void GotoXY(int x, int y);
void NoCursorType();