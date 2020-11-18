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

	std::string rectId;
	RECT rect;
	int x, y;
	std::string text;

	bool activated;


	Button(Renderer *_renderer,std::string button_id, std::string font_id, std::string _text, buttonType _type, int _x, int _y) {
		
		buttonId = button_id;

		defaultColor = { 255,255,255,255 };
		activeColor = { 255,255,0,255 };
		hoverColor = { 255,0,0,255 };

		defaultId.append(button_id);
		activeId.append(button_id);
		hoverId.append(button_id);

		actualId = defaultId;

		_renderer->LoadTextureText(font_id, { defaultId,_text, defaultColor });
		_renderer->LoadTextureText(font_id, { activeId,_text, activeColor });
		_renderer->LoadTextureText(font_id, { hoverId,_text, hoverColor });

		x = _x;
		y = _y;
		rect = { x, y, _renderer->GetTextureSize(defaultId).x, _renderer->GetTextureSize(defaultId).y };

		rectId = buttonId.append("rect");
		_renderer->LoadRect(rectId, rect);


		text = _text;
		type = _type;
		if (type == SOUND) activated = true;
		else activated = false;

	}

	~Button() {

	}
	void draw(Renderer* _renderer) {
		_renderer->PushImage(defaultId, rectId);
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