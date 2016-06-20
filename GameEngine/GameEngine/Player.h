#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Controllable.h"

using namespace sf;

class Player : public Entity, public Controllable {
public:
	Player(ResourceManager *rm);
	Player(float startX, float startY, ResourceManager *rm);

	void setEntityList(std::multimap<unsigned short int, Entity *> *list);

	virtual void keyHeld(Keyboard::Key key);
	virtual void keyPress(Keyboard::Key key);
	virtual void keyRelease(Keyboard::Key key);

	virtual void update();
	virtual void setState(stateType newState);
	virtual void render(RenderWindow *window);
private:
	std::multimap<unsigned short int, Entity *> *entityList;
	bool shiftHeld, dashU, dashL, dashD, dashR;
	short int attackType, maxAttacks;
	float dashTimer;

	void walk();
	void idle();
	void run();
	void abs();
	void attack();
	void attRec();
	void damaged();
	void dash();

	void setInvulFalse();
	void flashCurrentSprite(animType oldAnimation);
	bool updateDashDirection();

	std::pair<Vector2f, Vector2f> getAccessorLineFromDirection();
	Entity *getEntityAt(std::pair<Vector2f, Vector2f> line);

	virtual void init();
	virtual void updateState();
};
#endif