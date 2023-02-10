#pragma once
#include <iostream>
#include <SDL.h>

#include "Number.h"

namespace Renderer {
	bool InitializeRenderer();
	void UninitalizeRenderer();

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();
	SDL_Surface* GetScreen();

	void DrawPixel(int x, int y, Uint32 pixel);
	void RenderNumber(Number* num, int size = 10);
} // namespace Renderer