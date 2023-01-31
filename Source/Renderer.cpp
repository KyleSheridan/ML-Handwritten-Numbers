#include "Renderer.h"

namespace Renderer {
	namespace {
		extern SDL_Window* g_Window = nullptr;
		extern SDL_Renderer* g_Renderer = nullptr;
		extern SDL_Surface* g_Screen = nullptr;
	}

	bool InitializeRenderer() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cout << "Could not initialise SDL: " << SDL_GetError();
			return false;
		}

		// initialise ttf  if (TTF_Init() < 0)

		//create window
		g_Window = SDL_CreateWindow("ML- Handwritten Numbers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 280, 280, SDL_WINDOW_SHOWN);

		if (!g_Window) {
			std::cout << "Could not create window: " << SDL_GetError();
			return false;
		}

		//create renderer
		g_Renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);

		if (!g_Renderer) {
			std::cout << "Could not create renderer: " << SDL_GetError();
		}

		g_Screen = SDL_GetWindowSurface(g_Window);

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

	SDL_Surface* GetScreen()
	{
		return g_Screen;
	}

	void DrawPixel(int x, int y, Uint32 pixel) {
		int bpp = g_Screen->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to set */
		Uint8* p = (Uint8*)g_Screen->pixels + y * g_Screen->pitch + x * bpp;

		switch (bpp) {
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16*)p = pixel;
			break;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32*)p = pixel;
			break;
		}
	}

	void RenderNumber(Number num, int size) {
		for (int i = 0; i < 28; i++)
		{
			for (int j = 0; j < 28; j++)
			{
				Uint32 colour = SDL_MapRGB(g_Screen->format, num.pixels[(28 - 1) - i][j], num.pixels[(28 - 1) - i][j], num.pixels[(28 - 1) - i][j]);
				//DrawPixel(Renderer::GetScreen(), j + 100, i + 100, colour);
				for (int x = 0; x < size; x++)
				{
					for (int y = 0; y < size; y++)
					{
						DrawPixel((j * size) + x, (i * size) + y, colour);
					}
				}
			}
		}
	}
}