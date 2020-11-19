//std Libs
#include <iostream>
#include <exception>

//Custom Libs
#include "GameController.h"

int main(int, char*[]) {
	
	std::cout << "-START-" << std::endl;
	GameController gameController;

	while (gameController.isRunning()) {
		gameController.update();
	}
	std::cout << "-END-" << std::endl;
	return 0;
}