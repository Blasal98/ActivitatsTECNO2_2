#pragma once
#include "Renderer.h"
#include "Utils.h"

struct Button {
	buttonType type;
	enum buttonState{DEFAULT,ACTIVE,HOVER};
	buttonState state;

	std::string buttonId;
	std::string defaultId = "default";
	std::string activeId = "active";
	std::string hoverId = "hover";
	std::string actualId;

	std::string rectId;
	RECT rect;
	int x, y;
	std::string text;

	bool active;

	Button(Renderer *_renderer,std::string button_id, std::string font_id, std::string _text, buttonType _type, int _x, int _y) {
		
		buttonId = button_id;


		defaultId.append(button_id);
		activeId.append(button_id);
		hoverId.append(button_id);

		actualId = defaultId;
		state = buttonState::DEFAULT;

		_renderer->LoadTextureText(font_id, { defaultId,_text, BUTTON_DEFAULT_COLOR });
		_renderer->LoadTextureText(font_id, { activeId,_text, BUTTON_ACTIVE_COLOR });
		_renderer->LoadTextureText(font_id, { hoverId,_text, BUTTON_HOVER_COLOR });

		x = _x;
		y = _y;
		rect = { x, y, _renderer->GetTextureSize(defaultId).x, _renderer->GetTextureSize(defaultId).y };

		rectId = buttonId.append("rect");
		_renderer->LoadRect(rectId, rect);


		text = _text;
		type = _type;
		if (type == SOUND) {
			state = buttonState::ACTIVE;
			actualId = activeId;
			active = true;
		}
		else {
			active = false;
		}
		

	}

	~Button() {

	}

	void draw(Renderer* _renderer) {
		_renderer->PushImage(actualId, rectId);
	}

	void hoverButton(VEC2 _mouseCoord) {

		if (colCursorVsRect(_mouseCoord, rect)) {
			if (state != buttonState::HOVER) {
				actualId = hoverId;
				state = buttonState::HOVER;
			}
		}
		else {
			if (active) {
				if (state != buttonState::ACTIVE) {
					state = buttonState::ACTIVE;
					actualId = activeId;
				}
			}
			else {
				if (state != buttonState::DEFAULT) {
					state = buttonState::DEFAULT;
					actualId = defaultId;
				}
			}
		}
	}

	void activate() {
		if (!active) {
			active = true;
			actualId = activeId;
		}
		else {
			active = false;
			actualId = defaultId;;
		}
	}

	bool wasButtonClicked(VEC2 _mouseCoord, bool _clicked) {
		return (colCursorVsRect(_mouseCoord, rect) && _clicked);
	}
};