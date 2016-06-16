#include "Collidable.h"
#include <iostream>

Collidable::~Collidable() { }
Collidable::Collidable() { }
Collidable::Collidable(int x, int y, int width, int height) {
	cX = x;
	cY = y;
	cWidth = width;
	cHeight = height;
}

bool Collidable::willCollide(Collidable *other, int _dx, int _dy) {
	if (other == nullptr) return false;
	int otherLeft = other->cX - _dx;						// Left line of rectangle
	int otherRight = other->cX + other->cWidth + _dx;		// Right line of rectangle
	int otherTop = other->cY - _dy;							// Top line of rectangle
	int otherBottom = other->cY + +other->cHeight + _dx;	// Bottom line of rectangle

	return !((cY > otherBottom) || (cX > otherRight) || (cY + cHeight < otherTop) || (cX + cWidth < otherLeft));
}

bool Collidable::insideCollidable(Collidable *other) { 
	if (other == nullptr) return false;
	int otherLeft = other->cX;						// Left line of rectangle
	int otherRight = other->cX + other->cWidth;		// Right line of rectangle
	int otherTop = other->cY;						// Top line of rectangle
	int otherBottom = other->cY + +other->cHeight;	// Bottom line of rectangle

	return !((cY > otherBottom) || (cX > otherRight) || (cY + cHeight < otherTop) || (cX + cWidth < otherLeft));
}
Vector2f Collidable::getStaticOverlap(Collidable *other) { 
	int _x = 0, _y = 0;
	int otherLeft = other->cX - 1;						// Left line of rectangle
	int otherRight = other->cX + other->cWidth + 1;		// Right line of rectangle
	int otherTop = other->cY - 1;						// Top line of rectangle
	int otherBottom = other->cY + +other->cHeight + 1;	// Bottom line of rectangle

	Vector2f center = Vector2f((cX + cWidth / 2)*1.f, (cY + cHeight / 2)*1.f);
	Vector2f otherCenter = Vector2f((other->cX + other->cWidth / 2)*1.f, (other->cY + other->cHeight / 2)*1.f);
	Vector2f diff = center - otherCenter;

	float xOverlap = cWidth / 2 + other->cWidth / 2 - abs(diff.x);
	float yOverlap = cHeight / 2 + other->cHeight / 2 - abs(diff.y);

	if (xOverlap < 0 || yOverlap < 0) // No overlap. Collidables do not touch.
		return Vector2f(0.f, 0.f);

	if (xOverlap < yOverlap) {
		if (diff.x > 0) _x -= cX - otherRight;
		else _x -= cX + cWidth - otherLeft;
	}
	else {
		if (diff.y > 0) _y -= cY - otherBottom;
		else _y -= cY + cHeight - otherTop;
	}

	return Vector2f(_x*1.f, _y*1.f);
}

bool Collidable::hasCollidedN(Collidable *other) {
	int otherBottom = other->cY + +other->cHeight;

	if (cY < otherBottom) return false;
	return true;
}

bool Collidable::hasCollidedW(Collidable *other) {
	int otherRight = other->cX + other->cWidth;	

	if (cX < otherRight) return false;
	return true;
}

bool Collidable::hasCollidedS(Collidable *other) {
	int otherTop = other->cY;	

	if (cY + cHeight > otherTop) return false;
	return true;
}

bool Collidable::hasCollidedE(Collidable *other) {
	int otherLeft = other->cX;

	if (cX + cWidth > otherLeft) return false;
	return true;
}

bool Collidable::intersectsLine(std::pair<Vector2f, Vector2f> line) {
	return lineIntersectsRect(float(cX), float(cY), float(cWidth), float(cHeight), line);
}