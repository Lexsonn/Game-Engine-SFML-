#include "AI.h"

using namespace sf;

extern int globalSeed;

std::mt19937 AI::mt(globalSeed);
float AI::decisionSpeed = 0.05f;

AI::~AI() { }
AI::AI() : moves(false) { }

void AI::generateRND(unsigned int seed, int maxRange) {
	mt_local = std::mt19937(seed);
	decisionRange = std::uniform_int_distribution<int>(0, maxRange);
}

int AI::getDecision() {
	return decisionRange(mt);
}

int AI::getSiblingDecision() {
	return decisionRange(mt_local);
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
