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

	void generateRND(unsigned int seed, int maxRange);
	int getDecision();

	void setBounds(int x, int y, unsigned int w, unsigned int h);
	void setDestination();

	virtual void decideDirection();
	static float decisionSpeed;
protected:
	Vector2i destination, bound, maxBound;
	float decisionMake;
	
	std::uniform_int_distribution<int> decisionRange;
	std::random_device rd;

	bool moves;
	//std::mt19937 randomNumbers;
};
#endif
