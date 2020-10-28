#include "../include/Snake.h"

int main() {
	int Delay = 0;
	
	Init();
	while (!quitGame) {
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
	
	//system("pause");
}