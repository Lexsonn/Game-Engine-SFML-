#include "AttackManager.h"

unsigned short int AttackManager::ID = 0;
std::map<unsigned short int, Attack *> AttackManager::attackList;

int AttackManager::addAttack(Attack *attack) {
	attack->ID = ID;
	attackList.insert(std::pair<unsigned short int, Attack *>(ID, attack));
	return ID++;
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
			it->second->addToRenderer(int(it->second->y));
			it++;
		}
	}
}

std::map<unsigned short int, Attack *> *AttackManager::getAttackList() {
	return &attackList;
}

void AttackManager::clearAttacks() {
	while (!attackList.empty()) {
		std::map<unsigned short int, Attack *>::iterator it = attackList.begin();
		deleteAttack(it->first);
	}
}
