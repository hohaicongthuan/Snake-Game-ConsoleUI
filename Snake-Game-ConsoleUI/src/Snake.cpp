#include "../include/Snake.h"

bool DebugMode = 0;

// Define input keys here
const int	KEY_ESC = 27;
const int	KEY_UP[] = { 72, 119 };
const int	KEY_DOWN[] = { 80, 115 };
const int	KEY_LEFT[] = { 75, 97 };
const int	KEY_RIGHT[] = { 77, 100 };
const int	KEY_SELECT[] = { 13, 102 };
const int   KEY_PAUSE = 32;

// The array SnakeCoord saves the coordinates of every
// parts of the snake
Coordinate SnakeCoord[BOX_SIZE_X * BOX_SIZE_Y];

// Snake's head and tail and food coordinates
Coordinate SnakeHead, SnakeTail, Food;

// Stores the most recent snake's direction
int SnakeDirection = DIRECTION_UP;

// The box in which the snake lives
int Box[BOX_SIZE_X][BOX_SIZE_Y];

bool quitGame = false;
bool pauseGame = false;
bool GameOver = false;
int Score = 0;

// This variable keeps track of the snake's length
// Default value is 1;
int SnakeSize = 1;

bool isUpKey(int x) {
    auto ArraySize = std::size(KEY_UP);

    for (int i = 0; i < ArraySize; i++) {
        if (KEY_UP[i] == x) return true;
    }

    return false;
}

bool isDownKey(int x) {
    auto ArraySize = std::size(KEY_DOWN);

    for (int i = 0; i < ArraySize; i++) {
        if (KEY_DOWN[i] == x) return true;
    }

    return false;
}

bool isLeftKey(int x) {
    auto ArraySize = std::size(KEY_LEFT);

    for (int i = 0; i < ArraySize; i++) {
        if (KEY_LEFT[i] == x) return true;
    }

    return false;
}

bool isRightKey(int x) {
    auto ArraySize = std::size(KEY_RIGHT);

    for (int i = 0; i < ArraySize; i++) {
        if (KEY_RIGHT[i] == x) return true;
    }

    return false;
}

bool isSelectKey(int x) {
    auto ArraySize = std::size(KEY_SELECT);

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

// This function will randomly generate and return
// the position of the food
Coordinate SpawnFood() {
    Coordinate temp;
    bool isValidCoord = true;
    
    // Spawn random coordinates for the food
    // Food cannot be spawned on occupied slot
    // of the snake
    do {
        isValidCoord = true;
        temp.x = Random(19) + 1;
        temp.y = Random(19) + 1;

        // Check if the spawned position is occupied
        for (int i = 1; i <= SnakeSize; i++) {
            if (SnakeCoord[i].x == temp.x &&
                SnakeCoord[i].y == temp.y ||
                Food.x == temp.x &&
                Food.y == temp.y) {
                isValidCoord = false;
                break;
            }
        }
    } while (!isValidCoord);

    return temp;
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
    // Reset matrix
    for (int y = 0; y < BOX_SIZE_Y; y++) {
        for (int x = 0; x < BOX_SIZE_X; x++) {
            Box[x][y] = -1;
        }
    }
    
    // Set snake's position on the box
    for (int i = 1; i <= SnakeSize; i++) {
        Box[SnakeCoord[i].x][SnakeCoord[i].y] = 1;
    }

    // Set food's position on the box
    Box[Food.x][Food.y] = 0;
    
    // Print the matrix
    for (int y = 0; y < BOX_SIZE_Y; y++) {
        GotoXY(1, y + 1);
        for (int x = 0; x < BOX_SIZE_X; x++) {
            if (Box[x][y] == 1) std::cout << SNAKE_PIXEL;
            else if (Box[x][y] == 0) std::cout << FOOD_PIXEL;
            else std::cout << BLANK_PIXEL;
        }
    }
    GotoXY(0, 23);
}

void Init() {
    Coordinate temp;
    SnakeSize = 2;
    temp.x = BOX_SIZE_X / 2;
    temp.y = BOX_SIZE_Y / 2;
    SnakeCoord[1] = temp;
    temp.y = temp.y + 1;
    SnakeCoord[2] = temp;
    SnakeHead = SnakeCoord[1];
    SnakeTail = SnakeCoord[2];
    SnakeDirection = DIRECTION_UP;

    quitGame = false;
    pauseGame = false;
    GameOver = false;
    Score = 0;

    // Hide console cursor
    NoCursorType();

    // Spawn random coordinates for the food
    Food = SpawnFood();

    // Draw
    BorderRender();
    BoxRender();
    PrintScore();

    GotoXY(0, 22);
}

// Checks if the snake can move up/down
bool CanMoveUpDown() {
    Coordinate HeadMinusOne = SnakeCoord[2];
    if (SnakeHead.y == HeadMinusOne.y) return true;
    else return false;
}

// Checks if the snake can move left/right
bool CanMoveLeftRight() {
    Coordinate HeadMinusOne = SnakeCoord[2];
    if (SnakeHead.x == HeadMinusOne.x) return true;
    else return false;
}

// Check if a position is the same as food's position
bool isFoodPosition(Coordinate x) {
    if (Food.x == x.x && Food.y == x.y) return true;
    else return false;
}

void PrintScore() {
    GotoXY(23, 0);
    std::cout << "Score: " << Score;
    GotoXY(0, 23);
}

void PrintDebugInfo() {
    GotoXY(35, 0);
    std::cout << "\t" << "SnakeSize = " << SnakeSize << "\n";
    for (int i = 0; i < SnakeSize; i++) {
        GotoXY(35, i + 2);
        std::cout << "\t" << "SnakeCoord[" << i + 1 << "]:" << "\t"
            << "X = " << SnakeCoord[i + 1].x << " "
            << "Y = " << SnakeCoord[i + 1].y << "          " << "\n";
    }
    GotoXY(0, 23);
}

// This function will move the snake in a direction
// Consume food if it's in the way
void MoveSnake(int Direction) {
    Coordinate temp;
    
    switch (Direction) {
    case DIRECTION_UP:
        temp = SnakeCoord[1];
        temp.y = temp.y - 1;
        
        if (isFoodPosition(temp)) {
            SnakeSize++;
            Food = SpawnFood();
            Score += 5;
            PrintScore();
        }

        // Shift a the snake's pixel up
        // (lower part's coordinates = upper part's coordinates)
        for (int i = SnakeSize; i > 1; i--) {
            SnakeCoord[i] = SnakeCoord[i - 1];
        }

        // Set new head coordinates
        // Set head and tail coordinates
        SnakeHead = temp;
        SnakeTail = SnakeCoord[SnakeSize];
        SnakeCoord[1] = temp;

        // Set snake's direction
        SnakeDirection = DIRECTION_UP;

        break;
    case DIRECTION_DOWN:
        temp = SnakeCoord[1];
        temp.y = temp.y + 1;

        if (isFoodPosition(temp)) {
            SnakeSize++;
            Food = SpawnFood();
            Score += 5;
            PrintScore();
        }

        // Shift a the snake's pixel up
        // (lower part's coordinates = upper part's coordinates)
        for (int i = SnakeSize; i > 1; i--) {
            SnakeCoord[i] = SnakeCoord[i - 1];
        }

        // Set new head coordinates
        // Set head and tail coordinates
        SnakeHead = temp;
        SnakeTail = SnakeCoord[SnakeSize];
        SnakeCoord[1] = temp;

        // Set snake's direction
        SnakeDirection = DIRECTION_DOWN;

        break;
    case DIRECTION_LEFT:
        temp = SnakeCoord[1];
        temp.x = temp.x - 1;

        if (isFoodPosition(temp)) {
            SnakeSize++;
            Food = SpawnFood();
            Score += 5;
            PrintScore();
        }

        // Shift a the snake's pixel up
        // (lower part's coordinates = upper part's coordinates)
        for (int i = SnakeSize; i > 1; i--) {
            SnakeCoord[i] = SnakeCoord[i - 1];
        }

        // Set new head coordinates
        // Set head and tail coordinates
        SnakeHead = temp;
        SnakeTail = SnakeCoord[SnakeSize];
        SnakeCoord[1] = temp;

        // Set snake's direction
        SnakeDirection = DIRECTION_LEFT;

        break;
    case DIRECTION_RIGHT:
        temp = SnakeCoord[1];
        temp.x = temp.x + 1;

        if (isFoodPosition(temp)) {
            SnakeSize++;
            Food = SpawnFood();
            Score += 5;
            PrintScore();
        }

        // Shift a the snake's pixel up
        // (lower part's coordinates = upper part's coordinates)
        for (int i = SnakeSize; i > 1; i--) {
            SnakeCoord[i] = SnakeCoord[i - 1];
        }

        // Set new head coordinates
        // Set head and tail coordinates
        SnakeHead = temp;
        SnakeTail = SnakeCoord[SnakeSize];
        SnakeCoord[1] = temp;

        // Set snake's direction
        SnakeDirection = DIRECTION_RIGHT;

        break;
    }
}

void InputHandler() {
    if (_kbhit()) {
        char key = _getch();
        if (isUpKey(key) && CanMoveUpDown()) MoveSnake(DIRECTION_UP);
        if (isDownKey(key) && CanMoveUpDown()) MoveSnake(DIRECTION_DOWN);
        if (isLeftKey(key) && CanMoveLeftRight()) MoveSnake(DIRECTION_LEFT);
        if (isRightKey(key) && CanMoveLeftRight()) MoveSnake(DIRECTION_RIGHT);
        if (key == KEY_PAUSE)
            if (pauseGame) pauseGame = false;
            else pauseGame = true;
        if (key == KEY_ESC) quitGame = true;
    }
}