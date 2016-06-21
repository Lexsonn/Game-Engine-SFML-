#include "Calculations.h"
#include <iostream>
extern int WWIDTH;
extern int WHEIGHT;

bool lineIntersectsRect(float x, float y, float w, float h, std::pair<Vector2f, Vector2f> l) {
	float left = x;
	float right = x + w;
	float top = y;
	float bottom = y + h;

	float minX = l.first.x;
	float maxX = l.second.x;

	if (l.first.x > l.second.x) {
		minX = l.second.x;
		maxX = l.first.x;
	}

	if (maxX > right)
		maxX = right;
	if (minX < left)
		minX = left;
	if (minX > maxX)
		return false;

	float minY = l.first.y;
	float maxY = l.second.y;

	float dx = l.second.x - l.first.x;

	if (abs(dx) > 0.00001f) {
		float a = (l.second.y - l.first.y) / dx;
		float b = l.first.y - a * l.first.x;
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

float findDistancePointToLine(Vector2f l1, Vector2f l2, Vector2f p) {
	float diffX = l2.x - l1.x;
	float diffY = l2.y - l1.y;

	if ((diffX == 0) && (diffY == 0)) {
		diffX = p.x - l1.x;
		diffY = p.y - l1.y;
		return sqrt(diffX * diffX + diffY * diffY);
	}

	float t = ((p.x - l1.x) * diffX + (p.y - l1.y) * diffY) / (diffX * diffX + diffY * diffY);

	if (t < 0) {
		diffX = p.x - l1.x;
		diffY = p.y - l1.y;
	}
	else if (t > 1) {
		diffX = p.x - l2.x;
		diffY = p.y - l2.y;
	}
	else {
		diffX = p.x - (l1.x + t * diffX);
		diffY = p.y - (l1.y + t * diffY);
	}

	return sqrt(diffX * diffX + diffY * diffY);
}

Vector2f findMidpointOfLine(std::pair<Vector2f, Vector2f> l) {
	float midX = (l.second.x + l.first.x) / 2;
	float midY = (l.second.y + l.first.y) / 2;

	return Vector2f(midX, midY);
}

std::pair<Vector2f, Vector2f> rotateLineAboutPoint(std::pair<Vector2f, Vector2f> l, Vector2f p, float angle) {
	float x1, x2, y1, y2;
	x1 = l.first.x - p.x; y1 = l.first.y - p.y;
	x2 = l.second.x - p.x; y2 = l.second.y - p.y;

	float tempX1 = x1, tempX2 = x2;
	x1 = x1*cos(angle) + y1*sin(angle);
	y1 = y1*cos(angle) - tempX1*sin(angle);
	x2 = x2*cos(angle) + y2*sin(angle);
	y2 = y2*cos(angle) - tempX2*sin(angle);

	return std::pair<Vector2f, Vector2f>(Vector2f(x1 + p.x, y1 + p.y), Vector2f(x2 + p.x, y2 + p.y));
}

int getGrid(unsigned int x, unsigned int y) {
	int posX = x / GRID_WIDTH;
	int posY = y / GRID_HEIGHT;
	unsigned int width = (WWIDTH - 1) / GRID_WIDTH;
	unsigned int height = (WHEIGHT - 1) / GRID_WIDTH;

	int i = -1;
	if (posX <= width && posY <= height)
		i = posX * (height + 1) + posY;

	return i;
}

Vector2i getCoords(int gridPos) {
	unsigned int height = (WHEIGHT - 1) / GRID_WIDTH;
	int x = gridPos / (height + 1);
	int y = gridPos % (height + 1);

	return Vector2i(x, y);
}
