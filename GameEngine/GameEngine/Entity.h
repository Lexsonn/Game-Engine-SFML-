#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System.hpp>
#include "ResourceManager.h"
#include "Collidable.h"
#include "DrawableObject.h"
#include "SpriteEffect.h"
#include "Animation.h"
#include "AnimList.h"
#include "States.h"
#include <iostream>
#include <map>

#define DO_ENTITY 2
#define DIAG_MOD 0.7071

// Faces for 8 Directions
enum dir {
	EAST = 0x0,
	NORTHEAST,
	NORTH,
	NORTHWEST,
	WEST,
	SOUTHWEST,
	SOUTH,
	SOUTHEAST
};

class Entity : public DrawableObject, public Collidable {
public:
	std::string name;
	//float x, y;
	float dx, dy;
	short int maxLife, life, gridPos[4];
	unsigned short int ID;
	dir direction;
	animList currentAnimation;
	stateList state;

	std::multimap<unsigned short int, Entity* > *entityList;
	std::multimap<unsigned short int, Collidable* > *objectList;
	
	~Entity();
	Entity();
	Entity(ResourceManager *rm);
	Entity(float startX, float startY, ResourceManager *rm);
	
	bool isInAnimList(animList name);
	void addAnimation(Animation *anim, animList name);		// May not be needed.
	Animation *getCurrentAnimation();

	void beginUpdate();
	void endUpdate();

	virtual int getDrawableType();
	virtual void render(RenderWindow *window);
	virtual void update();

	void moveOutsideCollidable();
	void moveOutsideCollidable(Collidable *other);
	void moveOutsideEntity(Entity *other);

	virtual bool isEntity();
	virtual bool willCollide(unsigned short int _ID, int _dx, int _dy);
	virtual bool willCollide(Collidable *other, int _dx, int _dy);
	virtual bool insideCollidable(Collidable *other);
	virtual Vector2i getOverlap(Entity *other);
	virtual Vector2i getOverlap(Collidable *other);
protected:
	std::map<animList, Animation*> animationList;
	std::vector<SpriteEffect*> spriteEffectList;
	ResourceManager *rm_master;
	bool up, left, down, right;
	bool invulnerable, absFinished, attFinished, recFinished;

	bool updateDirection();

	virtual void init();
	virtual void updateState();
	virtual void updatePosition();
};
#endif