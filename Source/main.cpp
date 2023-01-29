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

int main(int argc, char* args[]) {
	if (!Renderer::InitializeRenderer()) {
		return 1;
	}
	Number image;

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
		image = temp;
	
		/*for (int i = 0; i < 28; i++)
		{
			Number temp{};
			for (int j = 0; j < 28; j++)
			{
				file.read((char*)&temp, sizeof(Number));
				image = temp;
			}
		}*/

		image.format_pixels();
	}


	SDL_Event e;
	bool running = true;
	while (running) {

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