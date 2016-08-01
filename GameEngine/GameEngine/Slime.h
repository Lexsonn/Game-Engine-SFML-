#ifndef SLIME_H
#define SLIME_H

#include "Entity.h"
#include "AI.h"

using namespace sf;

class Slime : public Entity, public AI {
public:
	Slime(ResourceManager *rm);
	Slime(float startX, float startY, ResourceManager *rm);

	virtual void update();
private:
	virtual void decideDirection();
	virtual void updateState();
	virtual void setState(stateType newState);

	virtual void init();

	virtual void walk();
	virtual void run();
	virtual void dead();
};
#endif
