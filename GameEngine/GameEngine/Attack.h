#ifndef ATTACK_H
#define ATTACK_H

#include <SFML/System.hpp>
#include "DrawableObject.h"
#include "Animation.h"
#include <vector>
#include <map>

using namespace sf;

class Attack : public DrawableObject {
public:
	float z;
	std::vector<std::pair<Vector2f, Vector2f>> attackLines;
	std::map<short int, unsigned short int> gridPos;
	unsigned short int parent, ID, type;
	short int currentLife, strength;
	Vector2f force;

	~Attack();
	Attack();
	Attack(unsigned short int parentID, unsigned short int _type, short int life, short int str, 
		   std::vector<std::pair<Vector2f, Vector2f>> lineList, Animation *anim);

	bool update();
	void setFormed(int formAt);
	void setPosition(float _x, float _y);
	void setPosition(Vector2f position);
	void setRotation(float angle);
	void setForce(float dx, float dy);
	void setForce(Vector2f f);

	virtual Sprite &getSprite();
private:
	Animation *animation;
	int formAt;
	bool formed;
};
#endif
