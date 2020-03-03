#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>

using namespace sf;
using namespace std;


class BitmaskManager
{
private:
	unordered_map<const Texture*, Uint8*> masks;

public:
	~BitmaskManager();

	/*
		Get the value anpha form bitmask [x , y]
		- return : Uint8 (color)
	*/
	Uint8 getPixel(const Texture* texture, const Uint8* bitmask, unsigned int x, unsigned int y) const;

	/*
		Create the array Uint8 * anpha form image
		- return : Uint8 *
	*/
	Uint8* createMask(const Texture* texture, const Image* img);
	/*
		Update the array Uint8 * anpha form image
		- return : Uint8 *
	*/
	bool updateMask(const Texture* texture, const Image* img);
	/*
		Create the array Uint8 * anpha form image
		- return : Uint8 *
	*/
	Uint8* createMask(const Texture* texture);
	/*
		Get the value anpha form bitmask [x , y]
		- return : Uint8 (color)
	*/
	Uint8* getMask(const Texture* texture);

};


