/*
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

struct AnimatedSprite {
	int width;
	int height;
	int imgPerRow;
	int numFrames;
	sf::Texture texture;
	sf::IntRect frame;
	sf::Sprite sprite;
};

/*
 *  General purpose sprite animation to be called before drawing sprite
 
void updateSprite (AnimatedSprite &spr) {
	// If the sprite has a full row of images, select the next frame:
	if (spr.frame.top < spr.height * ((spr.numFrames / spr.imgPerRow))) {
		// If the next frame is on the next row:
		if (spr.frame.left == spr.width * (spr.imgPerRow - 1)) {
			// Move the frame down a row and set the current frame to the first image on that row.
			spr.frame.top += spr.height;
			spr.frame.left = 0;
		}
		else // Otherwise the next frame is to the right of the current one.
			spr.frame.left += spr.width;
	}
	// If the sprite has an incomplete row:
	else { 
		// If the current frame is not the last frame:
		if (spr.frame.left < spr.width * (spr.numFrames % spr.imgPerRow - 1)) {
			// the next frame will be to the right of the current frame.
			spr.frame.left += spr.width;
		}
		else {
			// Otherwise the current frame is the last frame and the sprite is reset.
			spr.frame.top = 0;
			spr.frame.left = 0;
		}
	}
	spr.sprite.setTextureRect(spr.frame);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
	window.setFramerateLimit(30);
	sf::Event event;
	sf::Clock clock;
	sf::Color bgColor(100, 200, 125);

	sf::Texture tex;
	tex.loadFromFile("resources/robin.png");

	AnimatedSprite spr;
	spr.width = 240;
	spr.height = 314;
	spr.imgPerRow = 5;
	spr.numFrames = 22;
	spr.texture = tex;
	spr.frame = sf::IntRect(0, 0, spr.width, spr.height);
	spr.sprite = sf::Sprite(spr.texture, spr.frame);

	spr.sprite.setOrigin(spr.width/2, spr.height/2);
	spr.sprite.setPosition(320, 240);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::EventType::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					int temp = bgColor.r;
					bgColor.r = bgColor.g;
					bgColor.g = bgColor.b;
					bgColor.b = temp;
				}
			}
		}

		sf::Vector2f v = spr.sprite.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			spr.sprite.setPosition(v.x - 2, v.y);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			spr.sprite.setPosition(v.x + 2, v.y);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			spr.sprite.setPosition(v.x, v.y - 2);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			spr.sprite.setPosition(v.x, v.y + 2);

		updateSprite(spr);
			
		window.clear(bgColor);
		window.draw(spr.sprite);
		window.display();

		int time = clock.restart().asMilliseconds();
		std::cout << "\rElapsed time (ms): " << time << " FPS: " << (int)(1000.f/time);
		std::cout << std::flush;
	}

	return 0;
}
*/