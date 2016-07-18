#ifndef ATTACKMANAGER_H
#define ATTACKMANAGER_H

#include <SFML/System.hpp>
#include "ResourceManager.h"
#include "Attack.h"

struct AttackManager {
public:
	static std::map<unsigned short int, Attack *> attackList;
	//~AttackManager();
	//AttackManager();

	int addAttack(unsigned short int parentID, unsigned short int _type, short int life, short int str, 
				   std::vector<std::pair<Vector2f, Vector2f>> lineList, Animation *animation);
	int addAttack(Attack *attack);
	void deleteAttack(unsigned short int _ID);
	void updateAttacks();
	static std::map<unsigned short int, Attack *> *getAttackList();
	void clearAttacks();
private:
	static unsigned short int ID;
};
#endif
