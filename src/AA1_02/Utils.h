#pragma once

SDL_Rect myRectangle2ToSDL_Rect(Rectangle2 _rect) {
	SDL_Rect tmpRect{ _rect.x,_rect.y,_rect.w,_rect.h };
	return tmpRect;
}


