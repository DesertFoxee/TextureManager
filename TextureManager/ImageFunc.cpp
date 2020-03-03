#include "ImageFunc.h"

namespace img
{
	Image Crop(Image* image, Vector2u pos, unsigned int width, unsigned int height) {
		if (width != 0 && height != 0) {

			sf::Uint8* pixels = new Uint8[width * height * 4];

			for (unsigned int i = pos.x; i < pos.x + width; i++) {

				for (unsigned int j = pos.y; j < pos.y + height; j++) {
					auto color_pixel = image->getPixel(i, j);

					auto x = i - pos.x;
					auto y = j - pos.y;

					pixels[4 * (x + y * width) + 3] = color_pixel.a;
					pixels[4 * (x + y * width) + 2] = color_pixel.b;
					pixels[4 * (x + y * width) + 1] = color_pixel.g;
					pixels[4 * (x + y * width)] = color_pixel.r;

				}
			}

			Image img;
			img.create(width, height, pixels);

			delete[] pixels;
			return img;
		}
		return *image;
	}

	static Image Scale(Image* image, unsigned int width, unsigned int height) {

		auto img_size = image->getSize();
		auto x_scale = float(img_size.x / width);
		auto y_scale = float(img_size.y / height);

		sf::Uint8* pixels = new Uint8[width * height * 4];

		for (unsigned int x = 0; x < width; x++) {
			for (unsigned int y = 0; y < height; y++) {

				auto i = int(x * x_scale);
				auto j = int(y * y_scale);

				auto color_pixel = image->getPixel(i, j);

				pixels[4 * (x + y * width)] = color_pixel.r;
				pixels[4 * (x + y * width) + 1] = color_pixel.g;
				pixels[4 * (x + y * width) + 2] = color_pixel.b;
				pixels[4 * (x + y * width) + 3] = color_pixel.a;
			}
		}
		Image img;
		img.create(width, height, pixels);
		delete[] pixels;

		return img;
	}


	Image FlipHorizontally(Image* image) {

		auto img_size = image->getSize();
		auto width = img_size.x;
		auto height = img_size.y;

		sf::Uint8* pixels = new Uint8[width * height * 4];

		for (unsigned int x = 0; x < width; x++) {
			for (unsigned int y = 0; y < height; y++) {

				auto color_pixel = image->getPixel(x, y);
				auto xp = width - x - 1;

				pixels[4 * (xp + y * width)] = color_pixel.r;
				pixels[4 * (xp + y * width) + 1] = color_pixel.g;
				pixels[4 * (xp + y * width) + 2] = color_pixel.b;
				pixels[4 * (xp + y * width) + 3] = color_pixel.a;
			}
		}
		Image img;
		img.create(width, height, pixels);
		delete[] pixels;
		return img;
	}


	Image FlipVertically(Image* image) {

		auto img_size = image->getSize();
		auto width = img_size.x;
		auto height = img_size.y;

		sf::Uint8* pixels = new Uint8[width * height * 4];

		for (unsigned int x = 0; x < width; x++) {
			for (unsigned int y = 0; y < height; y++) {

				auto color_pixel = image->getPixel(x, y);
				auto yp = height - y - 1;

				pixels[4 * (x + yp * width)] = color_pixel.r;
				pixels[4 * (x + yp * width) + 1] = color_pixel.g;
				pixels[4 * (x + yp * width) + 2] = color_pixel.b;
				pixels[4 * (x + yp * width) + 3] = color_pixel.a;
			}
		}
		Image img;
		img.create(width, height, pixels);
		delete[] pixels;
		return img;
	}


	Image RotateCenter(Image* image, float angle) {

		angle = angle * float(PI / 180);

		auto img_size = image->getSize();
		auto width = img_size.x;
		auto height = img_size.y;

		auto x_center = width / 2;
		auto y_center = height / 2;

		Image img;
		img.create(width, height, Color::Transparent);

		for (unsigned int x = 0; x < width; x++) {
			for (unsigned int y = 0; y < height; y++) {


				auto xp = int((x - x_center) * cos(angle) + (y - y_center) * sin(angle) + x_center);
				auto yp = int((y - y_center) * cos(angle) - (x - x_center) * sin(angle) + y_center);

				if (xp >= 0 && xp < width && yp >= 0 && yp < height) {
					auto color_pixel = image->getPixel(xp, yp);
					img.setPixel(x, y, color_pixel);
				}
			}
		}
		return img;
	}

}
