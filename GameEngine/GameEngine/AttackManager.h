#ifndef ATTACK_MANAGER_H
#define ATTACK_MANAGER_H

#include <SFML/System.hpp>
#include "ResourceManager.h"
#include "Attack.h"

class AttackManager {
public:
	std::map<unsigned short int, Attack *> attackList;

	~AttackManager();
	AttackManager();
	AttackManager(ResourceManager *rm);

	void setResourceManager(ResourceManager *rm);

	void addAttack(unsigned short int parentID, unsigned short int _type, short int life, short int str, 
				   std::vector<std::pair<Vector2f, Vector2f>> lineList, Animation *animation);
	void addAttack(Attack *attack);
	void deleteAttack(unsigned short int _ID);
	void updateAttacks();
private:
	unsigned short int ID;
	ResourceManager *rm_master;
};
#endif
