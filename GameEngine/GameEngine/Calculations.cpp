#include "Calculations.h"

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
	float midX = (l.second.x - l.first.x) / 2;
	float midY = (l.second.y - l.first.y) / 2;

	return Vector2f(midX, midY);
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
