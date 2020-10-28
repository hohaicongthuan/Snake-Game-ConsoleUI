#pragma once

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <iterator>

// Define the size of the box in which
// the snake lives
#define BOX_SIZE_X 20
#define BOX_SIZE_Y 20

#define DIRECTION_UP    1
#define DIRECTION_DOWN  2
#define DIRECTION_LEFT  3
#define DIRECTION_RIGHT 4

#define SNAKE_PIXEL char(178)
#define FOOD_PIXEL char(176)
#define BLANK_PIXEL char(32)

// How long it takes for the snake to move without
// user's inputsS
#define SNAKE_DELAY 30

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
extern const int	KEY_PAUSE;

extern int SnakeDirection;
extern bool quitGame;
extern bool pauseGame;
extern bool GameOver;
extern int Score;
extern bool DebugMode;

struct Coordinate {
	int x, y;
};

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
void BorderRender();
void Init();
Coordinate SpawnFood();
void InputHandler();
bool CanMoveUpDown();
bool CanMoveLeftRight();
void MoveSnake(int Direction);
void BoxRender();
bool isFoodPosition(Coordinate x);
void PrintScore();
void PrintDebugInfo();