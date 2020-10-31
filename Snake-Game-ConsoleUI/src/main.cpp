#include "../include/Snake.h"

int main() {
	int Delay = 0;
	
	Init();
	while (!quitGame) {
		if (!GameOver) {
			// Reset delay if some key is hit
			if (_kbhit()) Delay = 0;

			InputHandler();

			if (!pauseGame) {
				Delay++;

				BoxRender();
				if (DebugMode) PrintDebugInfo();
				if (Delay >= SNAKE_DELAY) {
					MoveSnake(SnakeDirection);
					BoxRender();
					if (DebugMode) PrintDebugInfo();
					Delay = 0;
				}
			}
		}
		else {
			if (_kbhit()) {
				system("cls");
				Init();
				PrintGameOver(0);
				GameOver = false;
			}
		}
	}
	
	//system("pause");
}