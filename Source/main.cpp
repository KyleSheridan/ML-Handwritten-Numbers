#define SDL_MAIN_HANDLED
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SDL.h>

#include "Renderer.h"

int reverseInt(int i)
{
	unsigned char c1, c2, c3, c4;

	c1 = i & 255;
	c2 = (i >> 8) & 255;
	c3 = (i >> 16) & 255;
	c4 = (i >> 24) & 255;

	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

struct Number {
public:
	uint8_t pixels[28][28];

	void format_pixels() {
		for (short i = 0; i < 28; i++)
		{
			for (short y = 0; y < 28; y++)
			{
				std::cout << (int)pixels[i][y] << ", ";
			}
			std::cout << "\n";
		}
	}
};

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 pixel) {
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

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

void RenderNumber(Number num, int size = 10) {
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			Uint32 colour = SDL_MapRGB(Renderer::GetScreen()->format, num.pixels[(28 - 1) - i][j], num.pixels[(28 - 1) - i][j], num.pixels[(28 - 1) - i][j]);
			//DrawPixel(Renderer::GetScreen(), j + 100, i + 100, colour);
			for (int x = 0; x < size; x++)
			{
				for (int y = 0; y < size; y++)
				{
					DrawPixel(Renderer::GetScreen(), (j*size) + x, (i*size) + y, colour);
				}
			}
		}
	}
}

int main(int argc, char* args[]) {
	if (!Renderer::InitializeRenderer()) {
		return 1;
	}
	Number num1;
	Number num2;

	std::string filepath = std::string("../DataSets/t10k-images.idx3-ubyte");
	std::ifstream file(filepath.c_str());

	if (file.is_open()) {
		int32_t magic_number = 0;
		int32_t number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = reverseInt(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = reverseInt(number_of_images);
		file.read((char*)&n_rows, sizeof(n_rows));
		n_rows = reverseInt(n_rows);
		file.read((char*)&n_cols, sizeof(n_cols));
		n_cols = reverseInt(n_cols);

		Number temp{};
		file.read((char*)&temp, sizeof(Number));
		num1 = temp;

		num1.format_pixels();

		file.read((char*)&temp, sizeof(Number));
		num2 = temp;

		num2.format_pixels();
	}


	SDL_Event e;
	bool running = true;
	while (running) {

		RenderNumber(num1);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), Renderer::GetScreen());
		if (texture == nullptr) {
			fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
			exit(1);
		}
		SDL_FreeSurface(Renderer::GetScreen());
		SDL_RenderCopyEx(Renderer::GetRenderer(), texture, nullptr, nullptr, 0, 0, SDL_FLIP_VERTICAL);
		SDL_RenderPresent(Renderer::GetRenderer());

		SDL_DestroyTexture(texture);

		while (SDL_PollEvent(&e) != 0) {
			switch (e.type)
			{
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = false;
					break;
				}
			}
		}

		SDL_Delay(16);
	}

	Renderer::UninitalizeRenderer();

	return 0;
}