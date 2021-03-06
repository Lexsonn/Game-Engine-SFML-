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
#define ENTITY_SPEED 1.f
#define ENTITY_FLASHTIMER 3.f
#define FLASHTIMER_SPEED 0.12f

#define WALK_ANIM 8
#define RUN_ANIM 16
#define ABS_ANIM 24
#define ATT1_ANIM 32
#define ATT2_ANIM 40
#define ATT3_ANIM 48
#define ATT4_ANIM 56
#define AREC_ANIM 64
#define DAMG_ANIM 72
#define DASH_ANIM 8 //80
#define DEAD_ANIM 88

// Faces for 8 Directions
enum dir {
	EAST = 0x0
	, NORTHEAST
	, NORTH
	, NORTHWEST
	, WEST
	, SOUTHWEST
	, SOUTH
	, SOUTHEAST
};

class Entity : public DrawableObject, public Collidable {
public:
	std::string name;
	Vector2f v;
	short int maxLife, life, gridPos[4];
	bool invulnerable, isDead;
	dir direction;

	~Entity();
	Entity();
	Entity(ResourceManager *rm);
	Entity(float startX, float startY, ResourceManager *rm);
	
	Animation *getCurrentAnimation();
	void addAnimation(Animation *anim, animType name);
	virtual void flashCurrentSprite(animType oldAnimation);
	virtual Sprite &getSprite();

	void beginUpdate();
	void endUpdate();
	void damage(int dmg);
	void recover(int heal);

	virtual void update();

	void applyForce(Vector2f f);
	void updatePosition(Vector2f v);
	void moveOutsideCollidable(Collidable *other);
	Vector2f getEntityOverlap(Entity *other);

	virtual void render(RenderWindow *window);

	const static unsigned int entityType;
	virtual unsigned int getType();
protected:
	std::map<animType, Animation *> animationList;
	ResourceManager *rm_master;
	animType currentAnimation;
	stateType state;
	float flashDmg;
	bool up, left, down, right;
	bool dashU, dashL, dashD, dashR;
	bool running, animFinished, hit;

	bool isInAnimList(animType name);

	bool issuedDash();
	bool issuedMove();
	bool updateDirection();
	bool updateDashDirection();
	void updatePosition();
	void createNewEntity(std::string entityName, Vector2f pos);
	void createSpriteEffect(SpriteEffect *sprEffect);

	virtual void init();
	virtual float getSpeed();
	virtual float getFlashTimer();
	virtual void updateState();
	virtual void setState(stateType type);
	virtual void setInvulFalse();

	int createAttack(Vector2f pos, int type, int life, int str, Vector2f force, std::vector<std::pair<Vector2f, Vector2f>> attackLines, Animation *anim);
	Vector2f generateForceFromDirection(float strength);
	std::pair<Vector2f, Vector2f> createNormalLine(float length, float distance);
	std::pair<Vector2f, Vector2f> createNormalLineFromAngle(float length, float distance, float angle);

	Entity *getEntityAt(std::pair<Vector2f, Vector2f> line);
	Entity *getEntityById(unsigned short int id);

	virtual void idle();
	virtual void walk();
	virtual void run();
	virtual void abs();
	virtual void attack();
	virtual void attRec();
	virtual void damaged();
	virtual void dash();
	virtual void dead();
};
#endif
