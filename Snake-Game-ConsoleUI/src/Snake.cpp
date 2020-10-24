#include "../include/Snake.h"

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

// Define input keys here
const int	KEY_ESC = 27;
const int	KEY_UP[] = { 72, 119 };
const int	KEY_DOWN[] = { 80, 115 };
const int	KEY_LEFT[] = { 75, 97 };
const int	KEY_RIGHT[] = { 77, 100 };
const int	KEY_SELECT[] = { 13, 102 };

// The array SnakeCoord saves the coordinates of every
// parts of the snake
Coordinate SnakeCoord[BOX_SIZE_X * BOX_SIZE_Y];

// Snake's head and tail coordinates
Coordinate SnakeHead, SnakeTail;

// The box in which the snake lives
int Box[BOX_SIZE_X][BOX_SIZE_Y];

// This variable keeps track of the snake's length
// Default value is 1;
int SnakeSize = 1;

bool isUpKey(int x) {
    auto ArraySize = size(KEY_UP);

    for (int i = 0; i < ArraySize; i++) {
        if (KEY_UP[i] == x) return true;
    }

    return false;
}

bool isDownKey(int x) {
    auto ArraySize = size(KEY_DOWN);

    for (int i = 0; i < ArraySize; i++) {
        if (KEY_DOWN[i] == x) return true;
    }

    return false;
}

bool isLeftKey(int x) {
    auto ArraySize = size(KEY_LEFT);

    for (int i = 0; i < ArraySize; i++) {
        if (KEY_LEFT[i] == x) return true;
    }

    return false;
}

bool isRightKey(int x) {
    auto ArraySize = size(KEY_RIGHT);

    for (int i = 0; i < ArraySize; i++) {
        if (KEY_RIGHT[i] == x) return true;
    }

    return false;
}

bool isSelectKey(int x) {
    auto ArraySize = size(KEY_SELECT);

    for (int i = 0; i < ArraySize; i++) {
        if (KEY_SELECT[i] == x) return true;
    }

    return false;
}

int Random(int n) // Generate a random number
{
    srand((int)time(0));
    int r = (rand() % n);
    return r;
}

void Colour(int n) // Function that changes console text colour
{
    // 1 is bright red		2 is bright green		3 is bright blue
    // 4 is bright pink		5 is bright yellow		6 is white

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (n)
    {
    case 1: { SetConsoleTextAttribute(hConsole, 12); break; }
    case 2: { SetConsoleTextAttribute(hConsole, 10); break; }
    case 3: { SetConsoleTextAttribute(hConsole, 9); break; }
    case 4: { SetConsoleTextAttribute(hConsole, 13); break; }
    case 5: { SetConsoleTextAttribute(hConsole, 14); break; }
    case 6: { SetConsoleTextAttribute(hConsole, 15); break; }
    }

}

void GotoXY(int x, int y) // Hàm di chuyển con trỏ console
{
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void NoCursorType() // Hàm ẩn con trỏ console
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

// This function will print the border
void BorderRender() {
    // First row
    std::cout << char(201);
    for (int i = 0; i < BOX_SIZE_X; i++) {
        std::cout << char(205);
    }
    std::cout << char(187) << "\n";

    for (int i = 0; i < BOX_SIZE_Y; i++) {
        std::cout << char(186);
        for (int j = 0; j < BOX_SIZE_X; j++) {
            std::cout << " ";
        }
        std::cout << char(186) << "\n";
    }

    // Last row
    std::cout << char(200);
    for (int i = 0; i < BOX_SIZE_X; i++) {
        std::cout << char(205);
    }
    std::cout << char(188) << "\n";
}

// This function will print the box and reset
// console cursor to (0, 0)
void BoxRender() {
    GotoXY(1, 1);
    for (int y = 0; y < BOX_SIZE_Y; y++) {
        for (int x = 0; x < BOX_SIZE_X; x++) {
            if (Box[x][y] == 1) std::cout << SNAKE_PIXEL;
            else if (Box[x][y] == 0) std::cout << FOOD_PIXEL;
            else std::cout << BLANK_PIXEL;
        }
        GotoXY(1, y + 1);
    }
    GotoXY(0, 0);
}

void Init() {
    Coordinate temp;
    SnakeSize = 1;
    temp.x = BOX_SIZE_X / 2;
    temp.y = BOX_SIZE_Y / 2;
    SnakeCoord[1] = temp;
    SnakeHead.x = BOX_SIZE_X / 2;
    SnakeHead.y = BOX_SIZE_Y / 2;
    SnakeTail = SnakeHead;

    int x, y;

    // Hide console cursor
    NoCursorType();

    // Reset matrix
    for (y = 0; y < BOX_SIZE_Y; y++) {
        for (x = 0; x < BOX_SIZE_X; x++) {
            Box[x][y] = -1;
        }
    }

    // Spawn random coordinates for the food
    do {
        x = Random(19) + 1;
        y = Random(19) + 1;
        Box[x][y] = 0;
    } while ((x == BOX_SIZE_X / 2) && (y == BOX_SIZE_Y / 2));

    // Set default position for the snake
    // which is at the centre of the box
    Box[BOX_SIZE_X / 2][BOX_SIZE_Y / 2] = 1;

    // Draw
    BorderRender();
    BoxRender();

    GotoXY(0, 22);
}

int StartSnake() {
    Init();

    return 0;
}