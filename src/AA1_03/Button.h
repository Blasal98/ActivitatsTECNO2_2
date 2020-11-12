#pragma once

struct Button {
	buttonType type;

	SDL_Texture *texture = nullptr;
	SDL_Texture *defaultTexture = nullptr;
	SDL_Texture *activeTexture = nullptr;
	SDL_Texture *hoverTexture = nullptr;

	SDL_Color color;
	SDL_Color defaultColor;
	SDL_Color activeColor;
	SDL_Color hoverColor;

	Rectangle2 rect;
	int x, y;
	std::string text;

	bool activated;


	Button(SDL_Renderer *_renderer, SDL_Surface *_surface, TTF_Font *font, int _x, int _y, std::string _text, SDL_Color _defaultColor, SDL_Color _activeColor, SDL_Color _hoverColor, buttonType _type) {
		
		color = _defaultColor;
		defaultColor = _defaultColor;
		activeColor = _activeColor;
		hoverColor = _hoverColor;
		
		_surface = { TTF_RenderText_Blended(font,_text.c_str(),_defaultColor) };
		defaultTexture = { SDL_CreateTextureFromSurface(_renderer,_surface) };
		if (defaultTexture == nullptr) throw "Error: Default texture init";

		_surface = { TTF_RenderText_Blended(font,_text.c_str(),_activeColor) };
		activeTexture = { SDL_CreateTextureFromSurface(_renderer,_surface) };
		if (activeTexture == nullptr) throw "Error: Active texture init";

		_surface = { TTF_RenderText_Blended(font,_text.c_str(),_hoverColor) };
		hoverTexture = { SDL_CreateTextureFromSurface(_renderer,_surface) };
		if (hoverTexture == nullptr) throw "Error: Hover texture init";
		texture = defaultTexture;

		x = _x;
		y = _y;
		rect = { x, y, _surface->w, _surface->h };
		text = _text;
		type = _type;
		if (type == SOUND) activated = true;
		else activated = false;

	}

	~Button() {
		SDL_DestroyTexture(texture);
		SDL_DestroyTexture(defaultTexture);
		SDL_DestroyTexture(hoverTexture);
		SDL_DestroyTexture(activeTexture);
	}



	//void colorChange(SDL_Renderer *_renderer, TTF_Font *_font, SDL_Surface *_surface, SDL_Color _newColor) {
	//	_font = { TTF_OpenFont("../../res/ttf/saiyan.ttf",60) };
	//	if (_font == nullptr) throw "No es pot inicialitzar el TTF_Font";
	//	color = _newColor;
	//	_surface = { TTF_RenderText_Blended(_font,text.c_str(),color) };
	//	texture = { SDL_CreateTextureFromSurface(_renderer,_surface) };
	//	SDL_FreeSurface(_surface);
	//	TTF_CloseFont(_font);
	//}

	void hoverButton(Vector2 _mouseCoord, SDL_Renderer *_renderer, TTF_Font *_font, SDL_Surface *_surface) {

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

	bool wasButtonClicked(Vector2 _mouseCoord, bool _clicked) {
		return (colCursorVsRect(_mouseCoord, rect) && _clicked);
	}
};