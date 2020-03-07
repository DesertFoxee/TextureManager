#include "TextureManager.h"

TextureManager::~TextureManager() {
	for (auto iter = textures.begin(); iter != textures.end(); iter++) {
		if (iter->second != nullptr) {
			delete iter->second;
		}
	}
}

BitmaskManager* TextureManager::getBitmask() {
	return &bitmask;
}

string TextureManager::getPathSpriteSheet(const string name) const {
	auto iter_finder = textures.find(name);

	if (iter_finder != textures.end()) {
		return iter_finder->second->p_spritesheet;
	}
	return "";
}


#ifdef TINYXML_INCLUDED
bool TextureManager::loadTextureFromXML(const char* pathXML) {

	TiXmlDocument doc(pathXML);
	if (!doc.LoadFile()) {
		cout << doc.ErrorDesc() << endl;
		return false;
	}

	TiXmlHandle docHandle(&doc);

	TiXmlElement* xml_texture = docHandle.FirstChildElement().FirstChildElement("texture").ToElement();

	for (xml_texture; xml_texture; xml_texture = xml_texture->NextSiblingElement()) {

		const char* name = xml_texture->Attribute("name");
		const char* path = xml_texture->Attribute("path");
		const char* path_sheet = xml_texture->Attribute("spritesheet");
		const char* create_mask = xml_texture->Attribute("createmask");

		if (name == NULL || path == NULL) {
			cout << "Error <= Load data xml faild ! : Name = " << name << "| Path : " << path << endl;
		}
		else {
			bool cre_mask = false;
			if (path_sheet == NULL)
				path_sheet = "";
			if (create_mask == "true")
				cre_mask = true;
			createTexture(name, path, path_sheet, cre_mask);
		}
	}

}
#endif 


bool TextureManager::createTexture(const string name, const string path, const string spri_sheet_path, bool creBitmask) {
	Image img;
	if (!img.loadFromFile(path)) {
		return false;
	}

	u_texture* utexture = new u_texture();

	if (!utexture->texture.loadFromImage(img)) {
		cout << "Error <= Load image faild ! : Name = " << name << "| Path : " << path << endl;
		delete utexture;
		return false;
	}
	utexture->p_spritesheet = spri_sheet_path;

	if (creBitmask) {
		bitmask.createMask(&utexture->texture, &img);
	}

	textures.insert(std::make_pair(name, utexture));
	return true;
}

bool TextureManager::createTexture(const string name, Image& img, const string spri_sheet_path, bool creBitmask) {

	u_texture* utexture = new u_texture();

	if (!utexture->texture.loadFromImage(img)) {

		delete utexture;
		return false;
	}

	utexture->p_spritesheet = spri_sheet_path;
	if (creBitmask) {
		bitmask.createMask(&utexture->texture, &img);
	}

	textures.insert(std::make_pair(name, utexture));

	return true;
}

bool TextureManager::createTexture(const string name, Texture& texture, const string spri_sheet_path, bool creBitmask) {
	u_texture* utexture = new u_texture();

	utexture->texture = texture;

	Image img = texture.copyToImage();

	if (creBitmask) {
		bitmask.createMask(&utexture->texture, &img);
	}

	textures.insert(std::make_pair(name, utexture));
	return true;
}

const Texture* TextureManager::getTexture(const string name) const {
	auto iter_result = textures.find(name);

	if (iter_result == textures.end()) {
		return nullptr;
	}

	return &iter_result->second->texture;
}

bool TextureManager::updateTexture(string name, const string path, const string spri_sheet_path) {

	auto iter_finder = textures.find(name);

	if (iter_finder == textures.end()) {
		return false;
	}

	Image img;
	if (!img.loadFromFile(path)) {
		return false;
	}
	u_texture* utexture = new u_texture();
	if (!utexture->texture.loadFromImage(img)) {
		delete utexture;
		return false;
	}
	utexture->p_spritesheet = spri_sheet_path;

	delete iter_finder->second;

	iter_finder->second = utexture;
	bitmask.updateMask(&utexture->texture, &img);

	return true;
}

bool TextureManager::updateTexture(string name, Texture& texture, const string spri_sheet_path) {
	auto iter_finder = textures.find(name);

	if (iter_finder == textures.end()) {
		return false;
	}
	delete iter_finder->second;

	u_texture* utexture = new u_texture();
	utexture->texture = texture;
	utexture->p_spritesheet = spri_sheet_path;

	iter_finder->second = utexture;

	bitmask.updateMask(&texture, &texture.copyToImage());

	return true;
}

void TextureManager::removeTexture(string name) {
	auto iter_result = textures.find(name);

	if (iter_result != textures.end()) {
		delete iter_result->second;

		textures.erase(iter_result);
	}
}
