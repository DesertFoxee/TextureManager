#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "BitmaskManager.h"
#include "xml/tinyxml.h"

#ifdef TINYXML_INCLUDED

#include "xml/tinyxml.h"

#endif



using namespace std;
using namespace sf;


class TextureManager
{
private:
	struct u_rect
	{
		float speed;
		IntRect rect;
	};

	struct u_texture
	{
		Texture texture;
		string p_spritesheet;
		unordered_map <string, vector<u_rect>> m_rect;
	};


private:
	unordered_map<string, u_texture* > textures;
	BitmaskManager bitmask;

public:

	~TextureManager();

	BitmaskManager* getBitmask();

	string getPathSpriteSheet(const string name) const;

	unordered_map<string, vector<u_rect>>* getRectTexture(const string name)const;


#ifdef TINYXML_INCLUDED

	void loadSpriteSheet(const string name, const char* path_spritesheet);

	void loadSpriteSheet(const string name);

	void loadSpriteSheet();

	bool loadTextureFromXML(const char* pathXML);
#endif 

	bool createTexture(const string name, const string path, const string spri_sheet_path = "", bool creBitmask = false);

	bool createTexture(const string name, Image& img, const string spri_sheet_path = "", bool creBitmask = false);

	bool createTexture(const string name, Texture& texture, const string spri_sheet_path = "", bool creBitmask = false);

	const Texture* getTexture(const string name) const;

	bool updateTexture(string name, const string path, const string spri_sheet_path = "");

	bool updateTexture(string name, Texture& texture, const string spri_sheet_path = "");

	void removeTexture(string name);

};

