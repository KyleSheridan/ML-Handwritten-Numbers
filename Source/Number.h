#pragma once
#include <iostream>

struct Number {
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

class TrainingNumber {
public:
	TrainingNumber(Number* _image, uint8_t* _value) {
		image = _image;
		value = _value;
	}

	Number* image;
	uint8_t* value;
};