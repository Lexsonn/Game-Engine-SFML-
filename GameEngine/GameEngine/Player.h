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
	bool dashU, dashL, dashD, dashR;
	short int attackType, maxAttacks;
	float dashTimer;

	//virtual void walk();
	//virtual void idle();
	//virtual void run();
	//virtual void abs();
	//virtual void attack();
	//virtual void attRec();
	//virtual void damaged();
	virtual void dash();

	void setInvulFalse();
	bool updateDashDirection();

	std::pair<Vector2f, Vector2f> getAccessorLineFromDirection();
	Entity *getEntityAt(std::pair<Vector2f, Vector2f> line);

	virtual void init();
	virtual float getSpeed();
	virtual float getFlashTimer();
	virtual void updateState();
};
#endif