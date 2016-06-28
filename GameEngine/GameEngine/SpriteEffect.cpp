#include "SpriteEffect.h"

using namespace sf;

/************************ SPRITE EFFECT TYPE BIT OPERATIONS (32 bits) ***************************\
*																								*
*	Default: Fast fade effect (last 8th of the effect's life is fade)							*
*	(1)		Bit 0 - Fade effect																	*
*	(2)		Bit 1 - Rainbow effect																*
*	(4)		Bit 2 - Shrink/Grow effect. (set -1 for shrink)										*
*	(8)		Bit 3 -	Rotatation effect (negative for counter-clockwise)							*
*	(16)	Bit 4 -																				*
*	(32)	Bit 5 - 																			*
*																								*
\************************************************************************************************/

SpriteEffect::~SpriteEffect() { }
SpriteEffect::SpriteEffect() : currentLife(100), maxLife(100), rotationSpeed(4), finalScale(-1) { }
SpriteEffect::SpriteEffect(Sprite spr, float x, float y, int life, int t) : rotationSpeed(4), finalScale(-1) {
	sprite = spr;
	sprite.setPosition(x, y);
	this->x = x;
	this->y = y;
	currentLife = life + 1;
	maxLife = life;
	type = t;
}

int SpriteEffect::getDrawableType() {
	return DO_SPRITE_EFFECT;
}

/*
 *	Updates the current SpriteEffect.
 *	Returns false if the current SpriteEffect has expired.
 */
bool SpriteEffect::update() {
	if (--currentLife <= 0) 
		return false;

	if (type & 1) fade();			// Bit 0
	else fastFade();				// Default
	if (type & 2) rainbow();		// Bit 1
	if (type & 4) scale();			// Bit 2
	if (type & 8) rotation();		// Bit 3
	if (type & 16) flash();			// Bit 4

	return true;
}

void SpriteEffect::setRotationSpeed(float rotSpeed) {
	rotationSpeed = rotSpeed;
}

void SpriteEffect::setScale(float scale) {
	finalScale = scale;
	if (finalScale < -1.f)
		finalScale = -1.f;
}

void SpriteEffect::fastFade() {
	Color c = sprite.getColor();
	if (currentLife < maxLife / 8) {
		int numSteps = maxLife / 8;
		int currStep = 1 + numSteps - currentLife;
		c.a = 255 - int(255 * (float(currStep) / numSteps));
		sprite.setColor(c);
	}
}

void SpriteEffect::fade() {
	Color c = sprite.getColor();
	c.a = int((float(currentLife) / maxLife) * 255);
	sprite.setColor(c);
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

void SpriteEffect::scale() {
	sprite.setScale(1 + finalScale*float(maxLife - currentLife) / maxLife, 1 + finalScale*float(maxLife - currentLife) / maxLife);
}

void SpriteEffect::rotation() {
	sprite.rotate(rotationSpeed);
}

void SpriteEffect::flash() {
	int alpha = 255;
	Color c = sprite.getColor();
	if ((currentLife / 8) % 2 == 0)
		alpha = 64;
	c.a = alpha;
	sprite.setColor(c);
}
