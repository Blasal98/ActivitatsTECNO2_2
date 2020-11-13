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

#include "Renderer.h"

int main(int, char*[])
{
	Renderer* m_renderer = new Renderer();

	//// --- INIT SDL ---
	//if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	//	throw "No es pot inicialitzar SDL subsystems";

	//// --- WINDOW ---
	//SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	//if (m_window == nullptr)
	//	throw "No es pot inicialitzar SDL_Window";

	//// --- RENDERER ---
	//SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	//if (m_renderer == nullptr)
	//	throw "No es pot inicialitzar SDL_Renderer";

	////-->SDL_Image 
	//const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	//if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	////-->SDL_TTF
	//if (TTF_Init() != 0) throw "No es pot inicialitzar el TTF_Init";

	//-->SDL_Mix
	const Uint8 audFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(audFlags) & audFlags)) throw "Error: SDL_mixer init";

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
		throw "No es pot inicialitzar SDL_Mixer";




	//MOUSE
	VEC2 mouseCoord{ 0,0 };
	bool clicked = false;

	// --- SPRITES ---
		//Background
	/*SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	RECT bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };*/
	m_renderer->LoadTexture("backGround_Texture", "../../res/img/bg.jpg");
	m_renderer->LoadRect("backGround_Rect", { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT });

	//Cursor
	/*SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	if (playerTexture == nullptr) throw "Error: playerTexture init";
	RECT playerRect{ 0,0,CURSOR_CLOUD_WIDTH,CURSOR_CLOUD_HEIGHT };*/
	m_renderer->LoadTexture("player_Texture", "../../res/img/kintoun.png");
	m_renderer->LoadRect("player_Rect", { 0,0,CURSOR_CLOUD_WIDTH,CURSOR_CLOUD_HEIGHT });

	//-->Animated Sprite ---

	// --- TEXT ---
		//Font
	//TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",60) };
	//if (font == nullptr) throw "No es pot inicialitzar el TTF_Font";
	////Surface
	//SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font,TITLE_TEXT,TITTLE_TEXT_COLOR) };
	////Title

	//SDL_Texture *textTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	//if (textTexture == nullptr) throw "Error: textTexture init";
	//RECT textRect{ TITLE_TEXT_X, TITLE_TEXT_Y,tmpSurf->w,tmpSurf->h };

	m_renderer->LoadFont({"saiyan_Font","../../res/ttf/saiyan.ttf" ,60});
	m_renderer->LoadTextureText("saiyan_Font", { "MY SDL GAME", "title_Text", {255,255,255,255} });
	m_renderer->LoadRect("title_Text",{ TITLE_TEXT_X, TITLE_TEXT_Y ,m_renderer->GetTextureSize("Title_Text").x, m_renderer->GetTextureSize("Title_Text").y});

	//Buttons

	/*Button playButton(m_renderer, tmpSurf, font, PLAY_BUTTON_X, PLAY_BUTTON_Y, PLAY_BUTTON_TEXT, BUTTON_DEFAULT_COLOR, BUTTON_ACTIVE_COLOR, BUTTON_HOVER_COLOR, buttonType::PLAY);
	Button soundButton(m_renderer, tmpSurf, font, SOUND_BUTTON_X, SOUND_BUTTON_Y, SOUND_BUTTON_TEXT, BUTTON_DEFAULT_COLOR, BUTTON_ACTIVE_COLOR, BUTTON_HOVER_COLOR, buttonType::SOUND);
	Button exitButton(m_renderer, tmpSurf, font, EXIT_BUTTON_X, EXIT_BUTTON_Y, EXIT_BUTTON_TEXT, BUTTON_DEFAULT_COLOR, BUTTON_ACTIVE_COLOR, BUTTON_HOVER_COLOR, buttonType::EXIT);*/


	//Close
	//SDL_FreeSurface(tmpSurf);
	//TTF_CloseFont(font);

	// --- AUDIO ---

	Mix_Music *soundTrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (soundTrack == nullptr) throw "Error: soundTrack load";

	Mix_VolumeMusic(MIX_MAX_VOLUME);
	Mix_PlayMusic(soundTrack, -1);





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
			//buttonClicks

		/*if (playButton.wasButtonClicked(mouseCoord, clicked))
			playButton.activate(m_renderer, font, tmpSurf);
		else if (soundButton.wasButtonClicked(mouseCoord, clicked)) {
			soundButton.activate(m_renderer, font, tmpSurf);
			if (soundButton.activated)
				Mix_ResumeMusic();
			else
				Mix_PauseMusic();
		}
		else if (exitButton.wasButtonClicked(mouseCoord, clicked))
			isRunning = false;
		clicked = false;*/


		//Cursor
		/*playerRect.x += (mouseCoord.x - playerRect.x - playerRect.w / 2) / 5;
		playerRect.y += (mouseCoord.y - playerRect.y - playerRect.h / 2) / 5;*/
		//Hover
		/*playButton.hoverButton(mouseCoord, m_renderer, font, tmpSurf);
		soundButton.hoverButton(mouseCoord, m_renderer, font, tmpSurf);
		exitButton.hoverButton(mouseCoord, m_renderer, font, tmpSurf);*/

		// DRAW
		/*SDL_RenderClear(m_renderer);*/
		m_renderer->Clear();
		//Background
		//SDL_RenderCopy(m_renderer, bgTexture, nullptr, &myRectangle2ToSDL_Rect(bgRect));
		m_renderer->PushImage("backGround_Texture","backGround_Rect");

		//Text
		/*SDL_RenderCopy(m_renderer, textTexture, nullptr, &myRectangle2ToSDL_Rect(textRect));
		SDL_RenderCopy(m_renderer, playButton.texture, nullptr, &myRectangle2ToSDL_Rect(playButton.rect));
		SDL_RenderCopy(m_renderer, soundButton.texture, nullptr, &myRectangle2ToSDL_Rect(soundButton.rect));
		SDL_RenderCopy(m_renderer, exitButton.texture, nullptr, &myRectangle2ToSDL_Rect(exitButton.rect));*/
		//Cursor
		//SDL_RenderCopy(m_renderer, playerTexture, nullptr, &myRectangle2ToSDL_Rect(playerRect));
		m_renderer->PushImage("player_Texture", "player_Rect");

		/*SDL_RenderPresent(m_renderer);*/
		m_renderer->Render();

	}

	// --- DESTROY ---
	/*SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(playerTexture);

	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);*/
	Mix_CloseAudio();
	Mix_Quit();

	delete m_renderer;

	//// --- QUIT ---
	//SDL_Quit();

	return 0;
}