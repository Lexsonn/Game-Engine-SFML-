#include "AI.h"

using namespace sf;

AI::~AI() { }
AI::AI() { }

void AI::generateRND(unsigned int seed, int maxRange) {
	srand(seed);
	decisionRange = std::uniform_int_distribution<int>(0, maxRange);
	//randomNumbers = std::mt19937(rd());
}

int AI::getDecision() {
	return decisionRange(rd);
}

void AI::setBounds(int x, int y, int mX, int mY) {
	int minX, maxX, minY, maxY;

	minX = x; maxX = mX;
	minY = y; maxY = mY;

	if (x > mX) {
		minX = mX;
		maxX = x;
	}
	if (y > mY) {
		minY = mY;
		maxY = y;
	}

	bound = Vector2i(minX, minY);
	maxBound = Vector2i(maxX, maxY);

	if (x == mX && y == mY)
		moves = false;
	else
		moves = true;
}

void AI::setDestination() {
	if (!moves)
		return;
	int x, y;

	x = (maxBound.x - rand()%maxBound.x) + bound.x;
	y = (maxBound.y - rand()%maxBound.y) + bound.y;

	destination = Vector2i(x, y);
}

void AI::decideDirection() { }