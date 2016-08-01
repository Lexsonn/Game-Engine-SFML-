#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Controllable.h"

using namespace sf;

class Player : public Entity, public Controllable {
public:
	Player(ResourceManager *rm);
	Player(float startX, float startY, ResourceManager *rm);

	virtual void update();

	virtual void keyHeld(Keyboard::Key key);
	virtual void keyPress(Keyboard::Key key);
	virtual void keyRelease(Keyboard::Key key);

	virtual void render(RenderWindow *window);

	const static unsigned int entityType;
	virtual unsigned int getType();
private:
	short int attackType, maxAttacks;
	float dashTimer;

	virtual void setInvulFalse();

	void generateAttack();

	virtual void init();
	virtual float getSpeed();
	virtual float getFlashTimer();
	virtual void updateState();
	virtual void setState(stateType newState);

	virtual void dash();
};
#endif
