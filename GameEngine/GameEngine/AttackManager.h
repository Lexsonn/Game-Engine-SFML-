#ifndef ATTACKMANAGER_H
#define ATTACKMANAGER_H

#include "Attack.h"

struct AttackManager {
public:
	static std::map<unsigned short int, Attack *> attackList;

	static int addAttack(Attack *attack);
	void deleteAttack(unsigned short int _ID);
	void updateAttacks();
	void clearAttacks();
	static std::map<unsigned short int, Attack *> *getAttackList();
private:
	static unsigned short int ID;
};
#endif
