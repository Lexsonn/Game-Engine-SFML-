#ifndef SLIME_H
#define SLIME_H

#include "Entity.h"
#include "AI.h"

using namespace sf;

class Slime : public Entity, public AI {
public:
	~Slime();
	Slime(ResourceManager *rm);
	Slime(float startX, float startY, ResourceManager *rm);

	virtual void update();

	//virtual void render(RenderWindow *window);
private:
	void init();

	virtual void decideDirection();
	virtual void updateState();
	//virtual void updatePosition();
};
#endif