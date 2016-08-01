#ifndef BABYSLIME_H
#define BABYSLIME_H

#include "Entity.h"
#include "AI.h"

using namespace sf;

class BabySlime : public Entity, public AI {
public:
	BabySlime(ResourceManager *rm);
	BabySlime(float startX, float startY, ResourceManager *rm);

	virtual void update();
private:
	virtual void decideDirection();
	virtual void updateState();
	virtual void setState(stateType newState);

	virtual void init();
	virtual float getSpeed();

	virtual void walk();
	virtual void run();
	virtual void dead();
};
#endif
