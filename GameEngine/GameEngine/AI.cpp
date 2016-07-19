#include "AI.h"

using namespace sf;

float AI::decisionSpeed = 0.05f;

AI::~AI() { }
AI::AI() : moves(false) { }

void AI::generateRND(unsigned int seed, int maxRange) {
	srand(seed);
	decisionRange = std::uniform_int_distribution<int>(0, maxRange);
	//randomNumbers = std::mt19937(rd());
}

int AI::getDecision() {
	return decisionRange(rd);
}

void AI::setBounds(int x, int y, unsigned int w, unsigned int h) {
	int minX, maxX, minY, maxY;

	minX = x; maxX = x + w;
	minY = y; maxY = y + h;

	bound = Vector2i(minX, minY);
	maxBound = Vector2i(maxX, maxY);

	if (w != 0 || h != 0)
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
