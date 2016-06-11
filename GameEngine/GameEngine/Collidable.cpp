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

	if (xOverlap < 0 || yOverlap < 0) { // No overlap. Collidables do not touch.
		return Vector2f(0.f, 0.f);
		std::cout << "No overlap\n";
	}

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
	float left = float(cX);
	float right = float(cX + cWidth);
	float top = float(cY);
	float bottom = float(cY + cHeight);

	float minX = line.first.x;
	float maxX = line.second.x;

	if (line.first.x > line.second.x) {
		minX = line.second.x;
		maxX = line.first.x;
	}

	if (maxX > right) 
		maxX = right;
	if (minX < left) 
		minX = left;
	if (minX > maxX) 
		return false;

	float minY = line.first.y;
	float maxY = line.second.y;

	float dx = line.second.x - line.first.x;

	if (abs(dx) > 0.00001) {
		float a = (line.second.y - line.first.y) / dx;
		float b = line.first.y - a * line.first.x;
		minY = a * minX + b;
		maxY = a * maxX + b;
	}

	if (minY > maxY) {
		float tmp = maxY;
		maxY = minY;
		minY = tmp;
	}

	if (maxY > bottom)
		maxY = bottom;
	if (minY < top)
		minY = top;
	if (minY > maxY) 
		return false;

	return true;
}
/*
float Collidable::findDistance(Vector2f l1, Vector2f l2, Vector2f point) {
	float diffX = l2.x - l1.x;
	float diffY = l2.y - l1.y;

	if ((diffX == 0) && (diffY == 0)) {
		diffX = point.x - l1.x;
		diffY = point.y - l1.y;
		return sqrt(diffX * diffX + diffY * diffY);
	}

	float t = ((point.x - l1.x) * diffX + (point.y - l1.y) * diffY) / (diffX * diffX + diffY * diffY);

	if (t < 0) {
		diffX = point.x - l1.x;
		diffY = point.y - l1.y;
	}
	else if (t > 1) {
		diffX = point.x - l2.x;
		diffY = point.y - l2.y;
	}
	else {
		diffX = point.x - (l1.x + t * diffX);
		diffY = point.y - (l1.y + t * diffY);
	}

	return sqrt(diffX * diffX + diffY * diffY);
}
//*/