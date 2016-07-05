#include "Attack.h"

extern int WWIDTH;
extern int WHEIGHT;

Attack::~Attack() {}
Attack::Attack() : ID(0), parent(0), type(0), currentLife(0), strength(0), force(Vector2f(0,0)), formed(true) { }
Attack::Attack(unsigned short int parentID, unsigned short int _type, short int life, short int str, 
			   std::vector<std::pair<Vector2f, Vector2f>> lineList, Animation *anim) : ID(0), force(Vector2f(0, 0)), formed(true) {
	formAt = 0;
	parent = parentID;
	type = _type;
	currentLife = life;
	strength = str;
	attackLines = lineList;
	animation = anim;
}

void Attack::update() {
	if (currentLife-- <= 0)
		return;
	if (currentLife == formAt)
		formed = true;

	animation->beginUpdate();

	animation->endUpdate();
}

void Attack::setFormed(int formAt) {
	this->formAt = formAt;
	formed = false;
}

void Attack::setPosition(float _x, float _y) {
	x = _x;
	y = _y;
	animation->updatePosition(x, y);
}

void Attack::setPosition(Vector2f position) {
	x = position.x;
	y = position.y;
	animation->updatePosition(x, y);
}

void Attack::setRotation(float angle) {
	animation->setRotation(angle);
}

void Attack::setForce(float dx, float dy) {
	force = Vector2f(dx, dy);
}

Sprite &Attack::getSprite() {
	return animation->sprite;
}
