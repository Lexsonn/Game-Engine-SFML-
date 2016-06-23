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

	virtual void update();

	virtual void keyHeld(Keyboard::Key key);
	virtual void keyPress(Keyboard::Key key);
	virtual void keyRelease(Keyboard::Key key);

	virtual void render(RenderWindow *window);
private:
	std::multimap<unsigned short int, Entity *> *entityList;
	short int attackType, maxAttacks;
	float dashTimer;

	virtual void dash();

	void setInvulFalse();

	void generateAttack();

	std::pair<Vector2f, Vector2f> getAccessorLineFromDirection();
	Entity *getEntityAt(std::pair<Vector2f, Vector2f> line);

	virtual void init();
	virtual float getSpeed();
	virtual float getFlashTimer();
	virtual void updateState();
	virtual void setState(stateType newState);
};
#endif
