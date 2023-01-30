#pragma once
#include <iostream>
#include <SDL.h>

namespace Renderer {

	bool InitializeRenderer();
	void UninitalizeRenderer();

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();
	SDL_Surface* GetScreen();
} // namespace Renderer