#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "BitmaskManager.h"


using namespace std;
using namespace sf;


class TextureManager 
{
private:
	unordered_map<string, const Texture* > textures ;
	BitmaskManager bitmask;

public:

	~TextureManager();

	BitmaskManager* getBitmask();

	bool createTexture(const string name, const string path, bool creBitmask = false);

	bool createTexture(const string name, Image& img, bool creBitmask = false);

	bool createTexture(const string name, Texture& texture, bool creBitmask = false);

	const Texture* getTexture(const string name);

	bool updateTexture(string name, const string path);

	bool updateTexture(string name, Texture& texture);

	void removeTexture(string name);

};

