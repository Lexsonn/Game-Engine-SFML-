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
#include <map>

#define DO_ENTITY 1
#define DIAG_MOD 0.7071f

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
	float dx, dy;
	short int maxLife, life, gridPos[4];
	unsigned short int ID;
	dir direction;

	std::multimap<unsigned short int, Entity *> *entityList;
	std::multimap<unsigned short int, Collidable *> *objectList;
	
	~Entity();
	Entity();
	Entity(ResourceManager *rm);
	Entity(float startX, float startY, ResourceManager *rm);
	
	Animation *getCurrentAnimation();

	void beginUpdate();
	void endUpdate();

	virtual int getDrawableType();
	virtual void render(RenderWindow *window);
	virtual void update();

	void moveOutsideCollidable();
	void moveOutsideCollidable(Collidable *other);
	void moveOutsideEntity(Entity *other);
	bool willEntityCollide(unsigned short int _ID, int _dx, int _dy);
	Vector2f getEntityOverlap(Entity *other);
	//virtual bool willCollide(Collidable *other, int _dx, int _dy);
	//virtual bool insideCollidable(Collidable *other);
	//virtual Vector2f getStaticOverlap(Collidable *other);
protected:
	std::map<animType, Animation *> animationList;
	std::vector<SpriteEffect *> spriteEffectList;
	ResourceManager *rm_master;
	animType currentAnimation;
	stateType state;
	bool up, left, down, right;
	bool invulnerable, absFinished, attFinished, recFinished;

	bool isInAnimList(animType name);
	void addAnimation(Animation *anim, animType name);

	bool updateDirection();
	std::pair<Vector2f, Vector2f> getAccessorLineFromDirection();
	Entity *getEntityAt(std::pair<Vector2f, Vector2f> line);

	virtual void init();
	virtual void updateState();
	virtual void updatePosition();
	virtual void updatePosition(Vector2f v);
};
#endif