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

int main(int, char*[])
{
	Renderer* m_renderer = new Renderer();
	Aud_Renderer* a_renderer = new Aud_Renderer();

	//DT + FrameControl
	clock_t lastTime = clock();
	float dt = 0;
	Uint32 frameStart, frameTime;
	double totalTime = 0;

	// --- IMAGES ---
	//MOUSE
	VEC2 mouseCoord{ 0,0 };
	bool clicked = false;
	m_renderer->LoadTexture("player_Texture", "../../res/img/kintoun.png");	
	RECT player_Rect = { 0,0,CURSOR_CLOUD_WIDTH,CURSOR_CLOUD_HEIGHT };
	m_renderer->LoadRect("player_Rect", player_Rect);

	//BG
	m_renderer->LoadTexture("backGround_Texture", "../../res/img/bg.jpg");
	m_renderer->LoadRect("backGround_Rect", { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT });

	// --- Animated Sprite ---

	float anim_sprite_timeXsprite = 0.12f;
	float anim_sprite_count = 0;
	int anim_sprite_index = 0;
	float anim_velocity = 150;
	m_renderer->LoadTexture("anim_Texture", "../../res/img/sp01.png");
	RECT rectInSheed = {0,0,ANIM_SHEED_W / ANIM_QUANTITY,ANIM_SHEED_H};
	RECT rectInGame = {0,300,ANIM_SHEED_W / ANIM_QUANTITY,ANIM_SHEED_H};
	m_renderer->LoadRect("anim_RectInSheed", rectInSheed);
	m_renderer->LoadRect("anim_RectInGame", rectInGame);
	


	// --- TEXT ---

	m_renderer->LoadFont({"saiyan_Font","../../res/ttf/saiyan.ttf" ,60});
	m_renderer->LoadTextureText("saiyan_Font", {  "title_Text","MY SDL GAME", {255,255,255,255} });
	m_renderer->LoadRect("title_Rect",{ TITLE_TEXT_X, TITLE_TEXT_Y ,m_renderer->GetTextureSize("title_Text").x, m_renderer->GetTextureSize("title_Text").y});

	//Buttons

	Button playButton(m_renderer, "playButton", "saiyan_Font", PLAY_BUTTON_TEXT,buttonType::PLAY, PLAY_BUTTON_X, PLAY_BUTTON_Y);
	Button soundButton(m_renderer, "soundButton", "saiyan_Font", SOUND_BUTTON_TEXT, buttonType::SOUND, SOUND_BUTTON_X, SOUND_BUTTON_Y);
	Button exitButton(m_renderer, "exitButton", "saiyan_Font", EXIT_BUTTON_TEXT, buttonType::EXIT, EXIT_BUTTON_X, EXIT_BUTTON_Y);



	// --- AUDIO ---

	a_renderer->addTheme("mainTheme","../../res/au/mainTheme.mp3" );
	a_renderer->playTheme("mainTheme",-1);
	





	// --- GAME LOOP ---

	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		//FRAME CONTROL
		frameStart = SDL_GetTicks();

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

		if (playButton.wasButtonClicked(mouseCoord, clicked))
			playButton.activate();
		else if (soundButton.wasButtonClicked(mouseCoord, clicked)) {
			soundButton.activate();
			if (soundButton.active)
				a_renderer->resumeMusic();
			else
				a_renderer->pauseMusic();
		}
		else if (exitButton.wasButtonClicked(mouseCoord, clicked))
			isRunning = false;
		clicked = false;


		//Cursor
		player_Rect.x += (mouseCoord.x - player_Rect.x - player_Rect.w / 2) / 5;
		player_Rect.y += (mouseCoord.y - player_Rect.y - player_Rect.h / 2) / 5;
		m_renderer->LoadRect("player_Rect", player_Rect);
		
		//Hover
		playButton.hoverButton(mouseCoord);
		soundButton.hoverButton(mouseCoord);
		exitButton.hoverButton(mouseCoord);

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


		//animated
		if (anim_sprite_count >= anim_sprite_timeXsprite) {

			if (rectInSheed.x == ANIM_SHEED_W - ANIM_SHEED_H)
				rectInSheed.x = 0;
			else
				rectInSheed.x += ANIM_SHEED_W / ANIM_QUANTITY;
			m_renderer->LoadRect("anim_RectInSheed", rectInSheed);

			anim_sprite_count = 0;
		}
		else {
			anim_sprite_count += dt;
		}

		if (rectInGame.x > SCREEN_WIDTH) {
			rectInGame.x = -ANIM_SHEED_W/ANIM_QUANTITY;
		}
		else {
			rectInGame.x += anim_velocity * dt;
		}
		m_renderer->LoadRect("anim_RectInGame", rectInGame);
		m_renderer->PushSprite("anim_Texture", "anim_RectInSheed", "anim_RectInGame");



		//Cursor
		m_renderer->PushImage("player_Texture", "player_Rect");

		/*SDL_RenderPresent(m_renderer);*/
		m_renderer->Render();

		//dt
		dt = clock() - lastTime;
		lastTime = clock();
		dt /= CLOCKS_PER_SEC;
		totalTime += dt;
		//std::cout << totalTime << std::endl;
		
		//FRAME CONTROL
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
			SDL_Delay((int)(DELAY_TIME-frameTime));
	}


	delete m_renderer;
	delete a_renderer;

	return 0;
}