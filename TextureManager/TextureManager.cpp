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

bool TextureManager::createTexture(const string name, const string path, bool creBitmask) {
	Image img;
	if (!img.loadFromFile(path)) {
		return false;
	}

	Texture* texture = new Texture();
	if (!texture->loadFromImage(img)) {
		delete texture;
		return false;
	}

	if (creBitmask) {
		bitmask.createMask(texture, &img);
	}

	textures.insert(std::make_pair(name, texture));
	return true;
}

bool TextureManager::createTexture(const string name, Image& img, bool creBitmask) {
	Texture* texture = new Texture();

	if (!texture->loadFromImage(img)) {
		delete texture;
		return false;
	}
	if (creBitmask) {
		bitmask.createMask(texture, &img);
	}

	textures.insert(std::make_pair(name, texture));

	return true;
}

bool TextureManager::createTexture(const string name, Texture& texture, bool creBitmask) {
	Texture* textu = new Texture(texture);
	Image img = textu->copyToImage();

	if (creBitmask) {
		bitmask.createMask(textu, &img);
	}

	textures.insert(std::make_pair(name, textu));
	return true;
}

const Texture* TextureManager::getTexture(const string name) {
	auto iter_result = textures.find(name);

	if (iter_result == textures.end()) {
		return nullptr;
	}

	return iter_result->second;
}

bool TextureManager::updateTexture(string name, const string path) {

	auto iter_finder = textures.find(name);

	if (iter_finder == textures.end()) {
		return false;
	}

	Image img;
	if (!img.loadFromFile(path)) {
		return false;
	}

	Texture* texture = new Texture();
	if (!texture->loadFromImage(img)) {
		delete texture;
		return false;
	}

	delete iter_finder->second;
	iter_finder->second = texture;
	bitmask.updateMask(texture, &img);

	return true;
}

bool TextureManager::updateTexture(string name, Texture& texture) {
	auto iter_finder = textures.find(name);

	if (iter_finder == textures.end()) {
		return false;
	}
	delete iter_finder->second;

	iter_finder->second = new Texture(texture);

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
