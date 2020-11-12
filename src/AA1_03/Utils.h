#pragma once

SDL_Rect myRectangle2ToSDL_Rect(RECT _rect) {
	SDL_Rect tmpRect{ _rect.x,_rect.y,_rect.w,_rect.h };
	return tmpRect;
}

bool colCursorVsRect(VEC2 _mouseCoord, RECT _rect) {
	return ((_mouseCoord.x >= _rect.x && _mouseCoord.x <= _rect.x + _rect.w) && (_mouseCoord.y >= _rect.y && _mouseCoord.y <= _rect.y + _rect.h));
}

