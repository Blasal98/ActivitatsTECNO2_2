#pragma once
#include "Renderer.h"

struct Button {
	buttonType type;

	std::string buttonId;
	std::string defaultId = "default";
	std::string activeId = "active";
	std::string hoverId = "hover";
	std::string actualId;

	Color defaultColor;
	Color activeColor;
	Color hoverColor;

	RECT rect;
	int x, y;
	std::string text;

	bool activated;


	Button(Renderer *_renderer,std::string button_id, std::string font_id, std::string _text, buttonType _type, int _x, int _y) {
		
		buttonId = button_id;
		actualId = defaultId;

		defaultColor = { 255,255,255,255 };
		activeColor = { 255,255,0,255 };
		hoverColor = { 255,0,0,255 };

		_renderer->LoadTextureText(font_id, { buttonId + defaultId,_text, defaultColor });
		_renderer->LoadTextureText(font_id, { buttonId + activeId,_text, activeColor });
		_renderer->LoadTextureText(font_id, { buttonId + hoverId,_text, hoverColor });

		_renderer->LoadRect(buttonId + "rect", rect);

		
		x = _x;
		y = _y;
		rect = { x, y, _renderer->GetTextureSize(buttonId + defaultId).x, _renderer->GetTextureSize(buttonId + defaultId).y };

		text = _text;
		type = _type;
		if (type == SOUND) activated = true;
		else activated = false;

	}

	~Button() {

	}
	void draw(Renderer* _renderer) {
		_renderer->PushImage(buttonId + defaultId, buttonId + "rect");
		std::cout << "Gola";
	}

	/*void hoverButton(VEC2 _mouseCoord, SDL_Renderer *_renderer, TTF_Font *_font, SDL_Surface *_surface) {

		if (colCursorVsRect(_mouseCoord, rect)) {
			if (color.a != hoverColor.a) {
				texture = hoverTexture;
				color = hoverColor;
			}
		}
		else {
			if (activated) {
				if (color.a != activeColor.a) {
					texture = activeTexture;
					color = activeColor;
				}
			}
			else {
				if (color.a != defaultColor.a) {
					texture = defaultTexture;
					color = defaultColor;
				}
			}
		}
	}

	void activate(SDL_Renderer *_renderer, TTF_Font *_font, SDL_Surface *_surface) {
		if (!activated) {
			texture = activeTexture;
			color = activeColor;
			activated = true;
		}
		else {
			texture = defaultTexture;
			color = defaultColor;
			activated = false;
		}
	}
*/
	bool wasButtonClicked(VEC2 _mouseCoord, bool _clicked) {
		return (colCursorVsRect(_mouseCoord, rect) && _clicked);
	}
};