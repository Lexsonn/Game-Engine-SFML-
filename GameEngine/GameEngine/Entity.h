#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System.hpp>
#include "ResourceManager.h"
#include "AttackManager.h"
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

	~Entity();
	Entity();
	Entity(ResourceManager *rm);
	Entity(float startX, float startY, ResourceManager *rm);
	
	Animation *getCurrentAnimation();

	void beginUpdate();
	void endUpdate();
	void damage(int dmg);
	void recover(int heal);
	void setAttackManager(AttackManager *manager);
	//void setEntityList(std::multimap<unsigned short int, Entity *> *list);
	//void setObjectList(std::multimap<unsigned short int, Collidable *> *list);

	virtual int getDrawableType();
	virtual void flashCurrentSprite(animType oldAnimation);
	virtual void render(RenderWindow *window);
	virtual void update();
	virtual void setState(stateType type);

	void applyForce(Vector2f f);
	void updatePosition(Vector2f v);
	//void moveOutsideCollidable();
	void moveOutsideCollidable(Collidable *other);
	//void moveOutsideEntity(Entity *other);
	//bool willEntityCollide(unsigned short int _ID, int _dx, int _dy);
	Vector2f getEntityOverlap(Entity *other);
protected:
	// std::multimap<unsigned short int, Entity *> *entityList;
	//std::multimap<unsigned short int, Collidable *> *objectList;
	std::map<animType, Animation *> animationList;
	std::vector<SpriteEffect *> spriteEffectList;
	ResourceManager *rm_master;
	AttackManager *at_master;
	animType currentAnimation;
	stateType state;
	float flashDmg;
	bool up, left, down, right;
	bool invulnerable, animFinished, hit;

	bool isInAnimList(animType name);
	void addAnimation(Animation *anim, animType name);

	bool updateDirection();
	void updatePosition();
	// std::pair<Vector2f, Vector2f> getAccessorLineFromDirection();
	// Entity *getEntityAt(std::pair<Vector2f, Vector2f> line);

	virtual void init();
	virtual void updateState();
};
#endif
