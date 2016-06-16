#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Controllable.h"

#define SPEED 2.f
#define DASH_TIMER_SPEED 0.05f

using namespace sf;

class Player : public Entity, public Controllable {
public:
	Player(ResourceManager *rm);
	Player(float startX, float startY, ResourceManager *rm);

	virtual void keyHeld(Keyboard::Key key);
	virtual void keyPress(Keyboard::Key key);
	virtual void keyRelease(Keyboard::Key key);

	virtual void update();
	virtual void render(RenderWindow *window);
private:
	bool shiftHeld, dashU, dashL, dashD, dashR;
	short int attackType, maxAttacks;
	float dashTimer;

	void walk();
	void idle();
	void run();
	void abs();
	void attack();
	void attRec();
	void dash();

	void setState(stateType type);
	void setInvulFalse();
	void flashCurrentSprite(animType oldAnimation);
	bool updateDashDirection();

	virtual void init();
	virtual void updateState();
};
#endif