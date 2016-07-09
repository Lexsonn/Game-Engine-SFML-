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

void AttackManager::addAttack(unsigned short int parentID, unsigned short int type, short int life, short int str, 
							  std::vector<std::pair<Vector2f, Vector2f>> lineList, Animation *animation) {
	Attack *attack = new Attack(ID, parentID, type, life, str, lineList, animation);
	attackList.insert(std::pair<unsigned short int, Attack *>(ID++, attack));
}

void AttackManager::addAttack(Attack *attack) {
	attack->ID = ID;
	attackList.insert(std::pair<unsigned short int, Attack *>(ID++, attack));
}

void AttackManager::deleteAttack(unsigned short int _ID) {
	std::map<unsigned short int, Attack *>::iterator it = attackList.find(_ID);
	if (it == attackList.end())
		return;
	delete it->second;
	attackList.erase(it);
}

void AttackManager::updateAttacks() {
	std::map<unsigned short int, Attack *>::iterator it = attackList.begin();
	while (it != attackList.end()) {
		it->second->update();
		if (it->second->currentLife < 1) {
			delete it->second;
			it = attackList.erase(it);
		}
		else if (it->second->isVisible()) {
			rm_master->addSprite(int(it->second->y), it->second->getSprite());
			it++;
		}
	}
}
