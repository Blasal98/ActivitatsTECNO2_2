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

	//-->SDL_Mix
	const Uint8 audFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(audFlags) & audFlags)) throw "Error: SDL_mixer init";

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
		throw "No es pot inicialitzar SDL_Mixer";




	//MOUSE
	VEC2 mouseCoord{ 0,0 };
	bool clicked = false;


	m_renderer->LoadTexture("backGround_Texture", "../../res/img/bg.jpg");
	m_renderer->LoadRect("backGround_Rect", { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT });

	m_renderer->LoadTexture("player_Texture", "../../res/img/kintoun.png");
	m_renderer->LoadRect("player_Rect", { 0,0,CURSOR_CLOUD_WIDTH,CURSOR_CLOUD_HEIGHT });

	//-->Animated Sprite ---

	// --- TEXT ---

	m_renderer->LoadFont({"saiyan_Font","../../res/ttf/saiyan.ttf" ,60});
	m_renderer->LoadTextureText("saiyan_Font", {  "title_Text","MY SDL GAME", {255,255,255,255} });
	m_renderer->LoadRect("title_Rect",{ TITLE_TEXT_X, TITLE_TEXT_Y ,m_renderer->GetTextureSize("title_Text").x, m_renderer->GetTextureSize("title_Text").y});

	//Buttons

	Button playButton(m_renderer, "playButton", "saiyan_Font", PLAY_BUTTON_TEXT,buttonType::PLAY, PLAY_BUTTON_X, PLAY_BUTTON_Y);
	Button soundButton(m_renderer, "soundButton", "saiyan_Font", SOUND_BUTTON_TEXT, buttonType::SOUND, SOUND_BUTTON_X, SOUND_BUTTON_Y);
	Button exitButton(m_renderer, "exitButton", "saiyan_Font", EXIT_BUTTON_TEXT, buttonType::EXIT, EXIT_BUTTON_X, EXIT_BUTTON_Y);


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
		m_renderer->Clear();
		//Background
		m_renderer->PushImage("backGround_Texture","backGround_Rect");
		//Text
		m_renderer->PushImage("title_Text", "title_Rect");
		//Buttons
		playButton.draw(m_renderer);
		exitButton.draw(m_renderer);
		soundButton.draw(m_renderer);


		//Cursor
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