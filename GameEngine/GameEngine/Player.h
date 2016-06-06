#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Controllable.h"

using namespace sf;

class Player : public Entity, public Controllable {
public:
	~Player();
	Player(ResourceManager *rm);
	Player(float startX, float startY, ResourceManager *rm);

	virtual void keyHeld(Keyboard::Key key);
	virtual void keyPress(Keyboard::Key key);
	virtual void keyRelease(Keyboard::Key key);

	virtual void update();
	virtual void render(RenderWindow *window);
private:
	bool shiftHeld, dashU, dashL, dashD, dashR, playerHit;
	short int attackType, maxAttacks;
	float flashDmg;

	void walk();
	void idle();
	void run();
	void abs();
	void attack();
	void attRec();
	void dash();

	void flashCurrentSprite(animList oldAnimation);

	virtual void init();
	virtual void updateState();
	//virtual void updatePosition();
};
#endif