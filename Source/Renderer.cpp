#include "Renderer.h"

namespace Renderer {
	namespace {
		extern SDL_Window* g_Window = nullptr;
		extern SDL_Renderer* g_Renderer = nullptr;
	}

	bool InitializeRenderer() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cout << "Could not initialise SDL: " << SDL_GetError();
			return false;
		}

		// initialise ttf  if (TTF_Init() < 0)

		//create window
		g_Window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 280, 280, SDL_WINDOW_SHOWN);

		if (!g_Window) {
			std::cout << "Could not create window: " << SDL_GetError();
			return false;
		}

		//create renderer
		g_Renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);

		if (!g_Renderer) {
			std::cout << "Could not create renderer: " << SDL_GetError();
		}

		std::cout << "Renderer Initialized!\n";

		return true;
	}

	void UninitalizeRenderer()
	{
		SDL_DestroyRenderer(g_Renderer);
		g_Renderer = nullptr;
		SDL_DestroyWindow(g_Window);
		g_Window = nullptr;
		SDL_Quit();
	}

	SDL_Renderer* GetRenderer()
	{
		return g_Renderer;
	}

	SDL_Window* GetWindow()
	{
		return g_Window;
	}
}