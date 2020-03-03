#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


#define PI 3.14159265359


using namespace std;
using namespace sf;

namespace img
{

	static Image Crop(Image* image, Vector2u pos, unsigned int width, unsigned int height);

	static Image Scale(Image* image, unsigned int width, unsigned int height);

	static Image FlipHorizontally(Image* image);

	static Image FlipVertically(Image* image);

	static Image RotateCenter(Image* image, float angle);

};

