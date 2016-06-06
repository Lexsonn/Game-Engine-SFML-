#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/System.hpp>
#include <algorithm>

/************************* COLLIDABLE TYPE BIT OPERATIONS (32 bits) *****************************\
*																								*
*	Default: No collision (0)																	*
*	(1)		Bit 0 -	Object Collidable type														*
*	(2)		Bit 1 - Player Collidable type														*
*	(4)		Bit 2 - Entity Collidable type														*
*																								*
\************************************************************************************************/

using namespace sf;

class Collidable {
public:
	int cX, cY;
	int cWidth, cHeight;
	short int weight;

	~Collidable();
	Collidable();
	Collidable(int x, int y, int width, int height);

	virtual bool isEntity();
	virtual bool willCollide(Collidable *other, int _dx, int _dy);
	virtual bool insideCollidable(Collidable *other);
	virtual Vector2i getOverlap(Collidable *other);
	
	bool hasCollidedN(Collidable *other);
	bool hasCollidedW(Collidable *other);
	bool hasCollidedS(Collidable *other);
	bool hasCollidedE(Collidable *other);
	
	bool intersectsLine(std::pair<Vector2i, Vector2i> point);
protected:
	float findDistance(Vector2i l1, Vector2i l2, Vector2i point);
};
#endif