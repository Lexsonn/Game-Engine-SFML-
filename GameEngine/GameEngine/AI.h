#ifndef AI_H
#define AI_H

#include <SFML/System.hpp>
#include <random>
#include <cmath>

using namespace sf;

class AI {
public:
	~AI();
	AI();

	void generateRND(int seed, int maxRange);
	int getDecision();

	void setBounds(int x, int y, int mX, int mY);
	void setDestination();

	virtual void decideDirection();
protected:
	Vector2i destination, bound, maxBound;
	float decisionSpeed, decisionMake;
	
	std::uniform_int_distribution<int> decisionRange;
	std::random_device rd;

	bool moves;
	//std::mt19937 randomNumbers;
};
#endif