#include "AttackManager.h"

AttackManager::~AttackManager() { }
AttackManager::AttackManager() { 
	ID = 0;
}

AttackManager::AttackManager(ResourceManager *rm) {
	ID = 0;
	rm_master = rm;
}

void AttackManager::setResourceManager(ResourceManager *rm) {
	rm_master = rm;
}

void AttackManager::addAttack(unsigned short int parentID, unsigned short int type, short int life, 
							  short int str, std::vector<std::pair<Vector2f, Vector2f>> lineList) {
	Attack *attack = new Attack(ID, parentID, type, life, str, lineList);
	attackList.insert(std::pair<unsigned short int, Attack *>(ID++, attack));
}

void AttackManager::deleteAttack(unsigned short int _ID) {
	std::map<unsigned short int, Attack *>::iterator it = attackList.find(_ID);
	if (it == attackList.end())
		return;
	delete it->second;
	attackList.erase(it);
}

void AttackManager::deleteAttack(std::map<unsigned short int, Attack *>::iterator it) {
	delete it->second;
	attackList.erase(it);
}

void AttackManager::updateAttacks() {
	for (std::map<unsigned short int, Attack *>::iterator it = attackList.begin(); it != attackList.end(); it++) {
		it->second->update();
		if (it->second->currentLife < 1)
			deleteAttack(it);
		else {
			Sprite &spr = it->second->getSprite();
			rm_master->addSprite(int(it->second->z), spr);
		}
	}
}
