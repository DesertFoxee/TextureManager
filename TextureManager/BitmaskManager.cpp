#include "BitmaskManager.h"


BitmaskManager::~BitmaskManager() {
	for (auto iter = masks.begin(); iter != masks.end(); iter++) {
		if (iter->second != nullptr)
			delete[] iter->second;
	}
}


Uint8 BitmaskManager::getPixel(const Texture* texture, const Uint8* mask, unsigned int x, unsigned int y) const {
	if (x > texture->getSize().x || y > texture->getSize().y)
		return 0;

	return mask[x + y * texture->getSize().x];
}

Uint8* BitmaskManager::createMask(const Texture* texture, const Image* img){

	unsigned int width = img->getSize().x;
	unsigned int height = img->getSize().y;
	Uint8* mask = new Uint8[width * height];

	const Uint8* bit_pixel = img->getPixelsPtr();

	for (unsigned int x = 0; x < width; x++) {

		for (unsigned int y = 0; y < height; y++) {

			mask[x + y * width] = img->getPixel(x, y).a;
		}
	}
	masks.insert(std::make_pair(texture, mask));

	return mask;
}

bool BitmaskManager::updateMask(const Texture* texture, const Image* img) {
	auto iter_finder = masks.find(texture);

	if (iter_finder != masks.end()) {

		delete[] iter_finder->second;

		unsigned int width = img->getSize().x;
		unsigned int height = img->getSize().y;
		Uint8* mask = new Uint8[width * height];

		const Uint8* bit_pixel = img->getPixelsPtr();

		for (unsigned int x = 0; x < width; x++) {

			for (unsigned int y = 0; y < height; y++) {

				mask[x + y * width] = img->getPixel(x, y).a;
			}
		}
		iter_finder->second = mask;
		return true;
	}
	return false;
}

Uint8* BitmaskManager::createMask(const Texture* texture) {

	Image img = texture->copyToImage();

	unsigned int width = img.getSize().x;
	unsigned int height = img.getSize().y;
	Uint8* mask = new Uint8[width * height];

	const Uint8* bit_pixel = img.getPixelsPtr();

	for (unsigned int x = 0; x < width; x++) {

		for (unsigned int y = 0; y < height; y++) {

			mask[x + y * width] = img.getPixel(x, y).a;
		}
	}
	masks.insert(std::make_pair(texture, mask));

	return mask;
}


Uint8* BitmaskManager::getMask(const Texture* texture){
	Uint8* mask;

	auto iter_mask = masks.find(texture);

	if (iter_mask == masks.end()) {
		Image img = texture->copyToImage();
		mask = createMask(texture, &img);
	}
	else {
		mask = iter_mask->second;
	}
	return mask;
}