#ifndef ATTACK_H
#define ATTACK_H

#include <SFML/System.hpp>
#include "DrawableObject.h"
#include "Calculations.h"
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

	~Attack();
	Attack();
	Attack(unsigned short int _ID, unsigned short int parentID, unsigned short int _type, 
		   short int life, short int str, std::vector<std::pair<Vector2f, Vector2f>> lineList);

	void update();
	Sprite &getSprite();
private:
	Animation *animation;

	void generateGridPos();
	bool validGridPos(int x, int y);
	bool gridIntersects(int x, int y, std::pair<Vector2f, Vector2f> line);
};
#endif
