#include "Slime.h"

#define SPEED 0.5

void Slime::init() {
	// AI vars
	generateRND(time(NULL), 99);
	destination.x = x;
	destination.y = y;
	setBounds(120, 120, 240, 240);	// Temporary
	decisionMake = 0;
	decisionSpeed = 0.05;
	// Entity vars
	name = "Slime";
	cWidth = 20;
	cHeight = 20;
	life = 100;
	currentAnimation = idleE;
	weight = 10;
	Entity::init();
}

Slime::~Slime() { }
Slime::Slime(ResourceManager *rm) { 
	rm_master = rm;
	init();
}

Slime::Slime(float startX, float startY, ResourceManager *rm) { 
	rm_master = rm;
	x = startX;
	y = startY;
	init();
}
/*
void Slime::updatePosition() { 
	Entity::updatePosition();
	moveOutsideCollidable();	// Allow for pushing by other Entities being pushed
}
*/

void Slime::update() { 
	int decision = 100;
	decisionMake += decisionSpeed;
	
	if (decisionMake >= 1) {
		decision = getDecision();
		decisionMake -= 1;
	}

	if (decision <= 8)
		setDestination();

	if (x == destination.x && y == destination.y)
		return;

	decideDirection();

	if (updateDirection()) {
		switch (direction) {
		case EAST: dx = SPEED; dy = 0; break;
		case NORTHEAST: dx = SPEED * DIAG_MOD; dy = -SPEED * DIAG_MOD; break;
		case NORTH: dx = 0; dy = -SPEED; break;
		case NORTHWEST: dx = -SPEED * DIAG_MOD; dy = -SPEED * DIAG_MOD; break;
		case WEST: dx = -SPEED; dy = 0; break;
		case SOUTHWEST: dx = -SPEED * DIAG_MOD; dy = SPEED * DIAG_MOD; break;
		case SOUTH: dx = 0; dy = SPEED; break;
		case SOUTHEAST: dx = SPEED * DIAG_MOD; dy = SPEED * DIAG_MOD; break;
		}
		updatePosition();
	}
	else {
		dx = 0;
		dy = 0;
	}
}

void Slime::updateState() { 
	switch (state) {
	case IDLE:
	case WALK:
	case RUN:
		if (up || left || down || right) {
				state = WALK;
		}
		else
			state = IDLE;
		break;
	default: std::cout << "What did you do now?\n";
	}
}

void Slime::decideDirection() {
	left = false;
	right = false;
	up = false;
	down = false;

	if (abs(x - destination.x) != 0) {
		if (abs(int(x - destination.x)) <= SPEED)
			x = destination.x;
		else {
			if (x < destination.x) right = true;
			else left = true;
		}
	}

	if (abs(int(y - destination.y)) != 0) {
		if (abs(y - destination.y) <= SPEED)
			y = destination.y;
		else {
			if (y < destination.y) down = true;
			else up = true;
		}
	}
}