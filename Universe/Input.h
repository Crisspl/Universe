#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

#include <FHL/Maths/Vec2.h>

class Input
{
	Input() = delete;

public:
	static fhl::Vec2i getMousePosition()
	{
		fhl::Vec2i pos;
		SDL_GetMouseState(&pos.x, &pos.y);
		return pos;
	}
};

#endif