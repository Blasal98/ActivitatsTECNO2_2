#include <SDL.h> //Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h> 

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "Types.h"
#include "Constants.h" 
#include "Utils.h"
#include "Button.h"



int main(int, char *[])
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	if (TTF_Init()) throw "No es pot inicialitzar SDL_ttf";

	//-->SDL_Mix
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error: SDL_Mixer init";


	//MOUSE
	Vector2 mouseCoord{ 0,0 };
	bool clicked = false;

	// --- SPRITES ---
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	Rectangle2 bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };


	//Cursor
	SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	if (playerTexture == nullptr) throw "Error: playerTexture init";
	Rectangle2 playerRect{ 0,0,CURSOR_CLOUD_WIDTH,CURSOR_CLOUD_HEIGHT };


	//-->Animated Sprite ---

	// --- TEXT ---
#pragma region Text
	TTF_Font* font = TTF_OpenFont("../../res/ttf/saiyan.ttf", 80);
	if (!font) throw "No s'ha pogut crear la font.";

	SDL_Surface* tmpSurf{ TTF_RenderText_Blended(font, "My first SDL game", SDL_Color{255,150,2,255}) };
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	Rectangle2 textRect{ 100, 50, tmpSurf->w, tmpSurf->h };

	SDL_Texture* textNormal = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);

	tmpSurf = TTF_RenderText_Blended(font, "My first SDL game", SDL_Color{ 0,255,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";

	SDL_Texture* textHover = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);

	SDL_Texture* textTexture = textNormal;
	TTF_CloseFont(font);

#pragma endregion

	// --- AUDIO ---
#pragma region Audio
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) 
		throw "No s'ha pogut inicialitzar SDL_Mixer";
	

	Mix_Music* soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "No s'ha pogut carregar l'audio";
	Mix_PlayMusic(soundtrack, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	bool music_playing = true;
#pragma endregion



	// --- GAME LOOP ---

	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
				break;
			case SDL_MOUSEMOTION:
				mouseCoord.x = event.motion.x;
				mouseCoord.y = event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				clicked = true;

				break;
			default:;
			}
		}

		// UPDATE
		playerRect.x += (mouseCoord.x - playerRect.x - playerRect.w / 2) / 5;
		playerRect.y += (mouseCoord.y - playerRect.y - playerRect.h / 2) / 5;
		//Hover
		if ((textRect.x< mouseCoord.x && (textRect.x + textRect.w)>mouseCoord.x) &&
			textRect.y < mouseCoord.y && (textRect.y + textRect.h)>mouseCoord.y)
		{
			textTexture = textHover;
			if (clicked) {
				if (!music_playing) {
					Mix_ResumeMusic();
					music_playing = true;
				}
				else {
					Mix_PauseMusic();
					music_playing = false;
				}
					
			}
			clicked = false;
		}
		else {
			textTexture = textNormal;
		}
			
		
		// DRAW
		SDL_RenderClear(m_renderer);
		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &myRectangle2ToSDL_Rect(bgRect));
		//Cursor
		SDL_RenderCopy(m_renderer, playerTexture, nullptr, &myRectangle2ToSDL_Rect(playerRect));
		//Text
		SDL_RenderCopy(m_renderer, textTexture, nullptr, &myRectangle2ToSDL_Rect(textRect));


		SDL_RenderPresent(m_renderer);

	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(playerTexture);
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}