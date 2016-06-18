#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/System.hpp>
#include "Calculations.h"
#include <algorithm>

using namespace sf;

/************************* COLLIDABLE TYPE BIT OPERATIONS (32 bits) *****************************\
*																								*
*	Default: No collision (0)																	*
*	(1)		Bit 0 -	Object Collidable type														*
*	(2)		Bit 1 - Player Collidable type														*
*	(4)		Bit 2 - Entity Collidable type														*
*																								*
\************************************************************************************************/

class Collidable {
public:
	int cX, cY;
	int cWidth, cHeight;
	short int weight;
	bool phased;

	~Collidable();
	Collidable();
	Collidable(int x, int y, int width, int height);

	bool willCollide(Collidable *other, int _dx, int _dy);
	bool insideCollidable(Collidable *other);
	Vector2f getStaticOverlap(Collidable *other);
	
	bool hasCollidedN(Collidable *other);
	bool hasCollidedW(Collidable *other);
	bool hasCollidedS(Collidable *other);
	bool hasCollidedE(Collidable *other);
	
	bool intersectsLine(std::pair<Vector2f, Vector2f> line);
};
#endif