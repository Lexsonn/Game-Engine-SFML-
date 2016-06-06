#ifndef ANIMLIST_H
#define ANIMLIST_H

enum animList {
	UNKNOWN_a = -1,
	idleE = 0,		// IDLE ANIMATION
	idleNE,
	idleN,
	idleNW,
	idleW,
	idleSW,
	idleS,
	idleSE,
	walkE,			// WALK ANIMATION
	walkNE,
	walkN,
	walkNW,
	walkW,
	walkSW,
	walkS,
	walkSE,
	runE,			// RUN ANIMATION
	runNE,
	runN,
	runNW,
	runW,
	runSW,
	runS,
	runSE,
	ABSE,			// ATTACK BACK SWING ANIMATION
	ABSNE,
	ABSN,
	ABSNW,
	ABSW,
	ABSSW,
	ABSS,
	ABSSE,
	attack1E,		// ATTACK 1 ANIMATION
	attack1NE,
	attack1N,
	attack1NW,
	attack1W,
	attack1SW,
	attack1S,
	attack1SE,
	attack2E,		// ATTACK 2 ANIMATION
	attack2NE,
	attack2N,
	attack2NW,
	attack2W,
	attack2SW,
	attack2S,
	attack2SE,
	attack3E,		// ATTACK 3 ANIMATION
	attack3NE,
	attack3N,
	attack3NW,
	attack3W,
	attack3SW,
	attack3S,
	attack3SE,
	attack4E,		// ATTACK 4 ANIMATION
	attack4NE,
	attack4N,
	attack4NW,
	attack4W,
	attack4SW,
	attack4S,
	attack4SE,
	attRecE,		// ATTACK AFTER SWING
	attRecNE,
	attRecN,
	attRecNW,
	attRecW,
	attRecSW,
	attRecS,
	attRecSE,
	damageE,		// DAMAGE ANIMATION
	damageNE,
	damageN,		
	damageNW,
	damageW,
	damageSW,
	damageS,
	damageSE
};
#endif