#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/System.hpp>
#include "Calculations.h"


using namespace sf;

/************************* COLLIDABLE TYPE BIT OPERATIONS (32 bits) *****************************\
 *																								*
 *	Default: No collision (0)																	*
 *	(1)		Bit 0 -	Collidable with static Objects												*
 *	(2)		Bit 1 - Collidable with Player														*
 *	(4)		Bit 2 - Collidable with basic Entity												*
 *																								*
\************************************************************************************************/

class Collidable {
public:
	int cX, cY;
	int cWidth, cHeight;
	unsigned short int ID;
	short int weight;
	bool phased;

	~Collidable();
	Collidable();
	Collidable(int x, int y, int width, int height);

	bool willCollide(Collidable *other, int _dx, int _dy);
	bool insideCollidable(Collidable *other);
	Vector2f getStaticOverlap(Collidable *other);
	
	bool intersectsLine(std::pair<Vector2f, Vector2f> line);
};
#endif
