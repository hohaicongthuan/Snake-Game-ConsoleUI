#include "../include/Snake.h"

int main() {
	bool quitGame = false;
	
	Init();
	while (!quitGame) {
		BoxRender();
		InputHandler();
	}
	
	//system("pause");
}