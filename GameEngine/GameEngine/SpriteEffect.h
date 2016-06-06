#ifndef SPRITEEFFECT_H
#define SPRITEEFFECT_H

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

/******************************* TYPE BIT OPERATIONS (32 bits) **********************************\
 *																								*
 *	Default: Fast fade effect (last 8th of the effect's life is fade)							*
 *	(1)		Bit 0 - Fade effect																	*
 *	(2)		Bit 1 - Rainbow effect																*
 *	(4)		Bit 2 - Shrink effect																*
 *	(8)		Bit 3 - Grow effect																	*
 *	(16)	Bit 4 -	rotatation effect (negative for counter-clockwise)							*
 *	(32)	Bit 5 -																				*
 *	(64)	Bit 6 - Flash effect																*
 *																								*
\************************************************************************************************/

class SpriteEffect {
public:
	Sprite sprite;

	~SpriteEffect();
	SpriteEffect();
	SpriteEffect(Sprite spr, float x, float y, int life, int t);
	bool update();
	void setRotationSpeed(int rotSpeed);
protected:
	unsigned int type;
	int currentLife = 100, maxLife = 100;
	int rotationSpeed = 4;

	void fastFade();	// Default
	void fade();		// bit 0
	void rainbow();		// bit 1
	void shrink();		// bit 2
	void grow();		// bit 3
	void rotation();	// bit 4
};
#endif