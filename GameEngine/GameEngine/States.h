#ifndef STATES_H
#define STATES_H

enum stateType {
	UNKNOWN_STATE = -1,
	IDLE = 0,
	WALK,
	RUN,
	ATTACK_BACKSWING,
	ATTACK_SWING,
	ATTACK_RECOVER,
	DAMAGED,
	DASH,
	SPECIAL
};
#endif
