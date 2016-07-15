#ifndef STATES_H
#define STATES_H

enum stateType {
	UNKNOWN_STATE = -1
	, IDLE
	, WALK
	, RUN
	, ATTACK_BACKSWING
	, ATTACK_SWING
	, ATTACK_RECOVER
	, DAMAGED
	, DASH
	, DEAD
	, SPECIAL
};
#endif
