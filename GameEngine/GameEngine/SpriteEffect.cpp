#include "SpriteEffect.h"

using namespace sf;

SpriteEffect::~SpriteEffect() { }
SpriteEffect::SpriteEffect() { }
SpriteEffect::SpriteEffect(Sprite spr, float x, float y, int life, int t) {
	sprite = spr;
	sprite.setPosition(x, y);
	currentLife = life + 1;
	maxLife = life;
	type = t;
}

/*
 *	Updates the current SpriteEffect.
 *	Returns false if the current SpriteEffect has expired.
 */
bool SpriteEffect::update() {
	currentLife--;
	if (currentLife <= 0) 
		return false;

	if (type & 1) fade();			// Bit 0
	else fastFade();				// Default
	if (type & 2) rainbow();		// Bit 1
	if (type & 4) shrink();			// Bit 2
	if (type & 8) grow();			// Bit 3
	if (type & 16) rotation();		// Bit 4
	// if (type & 32) 		// Bit 5
	
	return true;
}

void SpriteEffect::setRotationSpeed(float rotSpeed) {
	rotationSpeed = rotSpeed;
}

void SpriteEffect::fade() {
	sprite.setColor(Color(255, 255, 255, int((float(currentLife) / maxLife) * 255)));
}

void SpriteEffect::rainbow() {
	Color c = sprite.getColor();
	if (currentLife == maxLife) { // Start color at RED (255, 0, 0)
		c.r = 255;
		c.g = 0;
		c.b = 0;
	}
	else if (currentLife > (maxLife * 5)/6) {			// RED 255, 0, 0 to ORANGE 255, 128, 0
		int numSteps = maxLife - (maxLife*5)/6;
		int currStep = 1 + numSteps - currentLife + (maxLife * 5) / 6;
		c.g = int(128 * (float(currStep) / numSteps));
	}
	else if (currentLife > (maxLife * 4) / 6) {		// ORANGE 255, 128, 0 to YELLOW 255, 255, 0
		int numSteps = (maxLife*5)/6 - (maxLife * 4) / 6;
		int currStep = 1 + numSteps - currentLife + (maxLife*4)/6;
		c.g = 127 + int(128 * (float(currStep) / numSteps));
	}
	else if (currentLife > (maxLife * 3) / 6) {		// YELLOW 255, 255, 0 to GREEN 0, 255, 0
		int numSteps = (maxLife * 4) / 6 - (maxLife * 3) / 6;
		int currStep = 1 + numSteps - currentLife + (maxLife * 3) / 6;
		c.r = 255 - int(255 * (float(currStep) / numSteps));
	}
	else if(currentLife > (maxLife * 2) / 6) {		// GREEN 0 255, 0 to BLUE 0, 0, 255
		int numSteps = (maxLife * 3) / 6 - (maxLife * 2) / 6;
		int currStep = 1 + numSteps - currentLife + (maxLife * 2) / 6;
		c.g = 255 - int(255 * (float(currStep) / numSteps));
		c.b = int(255 * (float(currStep) / numSteps));
	}
	else if (currentLife > (maxLife) / 6) {			// BLUE 0, 0, 255 to PURPLE 255, 0, 255
		int numSteps = (maxLife * 2)/6 - maxLife/6;
		int currStep = 1 + numSteps - currentLife + maxLife/ 6;
		c.r = int(255 * (float(currStep) / numSteps));
	}
	else {											// PURPLE 255, 0, 255 to RED 255, 0, 0
		int numSteps = (maxLife) / 6;
		int currStep = 1 + numSteps - currentLife;
		c.b = 255 - int(255 * (float(currStep) / numSteps));
	}

	sprite.setColor(c);
}

void SpriteEffect::shrink() {
	sprite.setScale(float(currentLife) / maxLife, float(currentLife) / maxLife);
}

void SpriteEffect::fastFade() {
	Color c = sprite.getColor();
	if (currentLife < maxLife / 8) {
		int numSteps = maxLife / 8;
		int currStep = 1 + numSteps - currentLife;
		c.a = 255 - int(255 * (float(currStep)/numSteps));
		sprite.setColor(c);
	}
}

void SpriteEffect::grow() {
	sprite.setScale(1 + float(currentLife) / maxLife, 1 + float(currentLife) / maxLife);
}

void SpriteEffect::rotation() {
	sprite.rotate(rotationSpeed);
}