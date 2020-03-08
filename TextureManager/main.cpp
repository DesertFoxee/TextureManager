#include <SFML/Graphics.hpp>

#include "ImageFunc.h"
#include "TextureManager.h"
#include "Collision.h"
#include <iostream>
#include "xml/tinyxml.h"

using namespace sf;
using namespace std;

sf::RenderWindow window;

string title = "Animation";
const unsigned int screen_width = 900;
const unsigned int screen_height = 500;
const unsigned int FPS = 60;


bool showfps = false;
Clock clockfps;
Clock clock1;
Clock time_refes_title;


float accumulator = 0;
const float timestep = 1.0f / FPS;
float game_speed = 100.f;


Sprite human;
Sprite monster;
Sprite ball;
Sprite ball2;

Vector2f loc;
Vector2f vec;

TextureManager textures;

/*
	texturemanager
	move sprite animation
*/

CircleShape shape;




void drawRectangle(Vector2f pos, float width, float height) {
	RectangleShape shape;

	shape.setFillColor(Color::Transparent);
	shape.setPosition(pos);

	shape.setOutlineThickness(1);
	shape.setOutlineColor(Color::Red);
	shape.setSize({ width , height });

	window.draw(shape);
}


void setup() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.create(sf::VideoMode(screen_width, screen_height), title, sf::Style::Default, settings);

	textures.loadTextureFromXML("assets/d_texture.xml");
	textures.loadSpriteSheet();


	human.setTexture(*textures.getTexture("human"));
	monster.setTexture(*textures.getTexture("monster"));

	loc = { 100 ,100 };
	vec = { 0 ,0 };

	human.setPosition(loc);

	human.setScale({ 0.2 ,0.2 });


	monster.setPosition({ 200 ,100 });
	monster.setScale({ 0.2 ,0.2 });

	shape.setRadius(10);
	shape.setPosition(200, 200);


	ball.setPosition({ 100, 100 });
	ball2.setPosition({ 500, 100 });

}

void process(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		vec.x = -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		vec.x = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		vec.y = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		vec.y = -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::F)) {
		human.setRotation(15);
	}
}

void update(float dt) {

	loc += vec * dt;



	human.setPosition(loc);

	if (Collision::perfect(textures.getBitmask() , &human, &monster)) {
		cout << "Collision" << endl;
	}
	else {
		cout << endl;
	}
	vec *= 0.f;
}

void draw() {
	auto h = human.getGlobalBounds();
	drawRectangle({ h.left , h.top }, h.width, h.height);
	window.draw(human);

	auto m = monster.getGlobalBounds();
	window.draw(monster);
	drawRectangle({ m.left , m.top }, m.width, m.height);

	
	/*auto m = ball.getGlobalBounds();
	window.draw(ball);
	drawRectangle({ m.left , m.top }, m.width, m.height);


	auto h = ball2.getGlobalBounds();
	window.draw(ball2);
	drawRectangle({ h.left , h.top }, h.width, h.height);*/


}

void processOne(sf::Event& event) {
	if (event.type == sf::Event::EventType::Closed) {
		window.close();
	}
}

void clear() {
	window.clear();
}


void display() {
	window.display();
}

void miscellaneous() {
	if (showfps) {
		auto time = clock1.restart().asMilliseconds();
		auto time_refes = time_refes_title.getElapsedTime().asMilliseconds();
		if (time_refes > 100) {
			window.setTitle(title + "- FPS : " + std::to_string(1000 / time));
			time_refes_title.restart();
		}
	}
}



int main() {
	
	setup();

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			processOne(event);
		}

		accumulator = clockfps.restart().asSeconds();


		process(accumulator * 20.f);

		while (accumulator >= timestep) {
			accumulator -= timestep;
			update(timestep * game_speed);
		}
		update(accumulator / timestep);

		clear();
		draw();
		display();
		miscellaneous();

	}
	return 0;
}