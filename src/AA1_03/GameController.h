#include <SDL.h> //Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h> 

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "Types.h"
#include "Constants.h" 
#include "Utils.h"
#include "Button.h"

#include "Renderer.h"
#include "Aud_Renderer.h"
#include <time.h>


class GameController {


private:
	Renderer* m_renderer;
	Aud_Renderer* a_renderer;
	bool _isRunning;
public:
	GameController();
	~GameController();
	void update();
	bool isRunning() { return _isRunning; }
};