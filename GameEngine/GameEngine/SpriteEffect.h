#ifndef SPRITEEFFECT_H
#define SPRITEEFFECT_H

#include "SFML/Graphics.hpp"
#include "DrawableObject.h"
#include <iostream>

#define DO_SPRITE_EFFECT 2

using namespace sf;

/************************ SPRITE EFFECT TYPE BIT OPERATIONS (32 bits) ***************************\
 *																								*
 *	Default: Fast fade effect (last 8th of the effect's life is fade)							*
 *	(1)		Bit 0 - Fade effect																	*
 *	(2)		Bit 1 - Rainbow effect																*
 *	(4)		Bit 2 - Shrink/Grow effect. (set -1 for shrink)										*
 *	(8)		Bit 3 -	Rotatation effect (negative for counter-clockwise)							*
 *	(16)	Bit 4 -	Flash Effect																*
 *	(32)	Bit 5 - 																			*
 *																								*
\************************************************************************************************/

class SpriteEffect : public DrawableObject {
public:
	Sprite sprite;

	~SpriteEffect();
	SpriteEffect();
	SpriteEffect(Sprite spr, float x, float y, int life, int t);

	virtual int getDrawableType();

	bool update();
	void setRotationSpeed(float rotSpeed);
	void setScale(float scale);
protected:
	unsigned int type;
	int currentLife = 100, maxLife = 100;
	float rotationSpeed = 4, finalScale = -1;

	void fastFade();	// Default
	void fade();		// bit 0
	void rainbow();		// bit 1
	void scale();		// bit 2
	void rotation();	// bit 3
	void flash();		// bit 4
};
#endif