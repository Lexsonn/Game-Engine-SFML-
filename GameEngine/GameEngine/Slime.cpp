#include "Slime.h"
#include <iostream>

void Slime::init() {
	// AI vars
	generateRND(int(time(NULL)), 99);
	destination.x = int(x);
	destination.y = int(y);
	setBounds(40, 40, 240, 240);	// Temporary
	decisionMake = 0;
	// Entity vars
	name = "Slime";
	cWidth = 20;
	cHeight = 20;
	life = 100;
	currentAnimation = idleE;
	weight = 10;

	Texture *tx0 = rm_master->getTexture("playerIdle.png");
	Texture *tx1 = rm_master->getTexture("playerAttRec.png");
	Texture *tx2 = rm_master->getTexture("playerDeath.png");

	animationList[idleE] = new Animation(tx0, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[idleE]->setScale(0.75, 0.75);
	animationList[damageE] = new Animation(tx1, 0.f, 0.f, 50, 50, 6, 0.1f, true); animationList[damageE]->setScale(0.75, 0.75);
	animationList[deathE] = new Animation(tx2, 0.f, 0.f, 50, 50, 8, 0.1f, true); animationList[deathE]->setScale(0.75, 0.75);
}

Slime::~Slime() { }
Slime::Slime() { std::cout << "en tity init\n"; Entity::init(); init(); }
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

void Slime::update() { 
	// AI decision making
	decisionMake += decisionSpeed;
	if (decisionMake >= 1) {
		decisionMake -= 1;
		if (getDecision() <= 8)
			setDestination();
	}
	decideDirection();

	// Typical Entity update
	animType oldAnimation = currentAnimation;

	updateState();
	switch (state) {
	case IDLE: idle(); break;
	case WALK: walk(); break;
	case RUN: run(); break;
	case DAMAGED: damaged(); break;
	case DEAD: dead(); break;
	}

	// If the Slime has been hit, flash the current sprite.
	flashCurrentSprite(oldAnimation);

	updatePosition();
}

void Slime::updateState() { 
	switch (state) {
	case IDLE:
	case WALK:
	case RUN:
		if (issuedMove()) {
			if (running) setState(RUN);
			else setState(WALK);
		}
		else
			setState(IDLE);
		break;
	case DAMAGED:
		if (animFinished)
			setState(IDLE);
		break;
	case DEAD:
		if (animFinished && !isDead) {
			createNewEntity("BabySlime", Vector2f(x - 5, y));
			createNewEntity("BabySlime", Vector2f(x + 5, y));
			isDead = true;
		}
		break;
	default: std::cout << "What did you do now?\n";
	}
}
void Slime::setState(stateType newState) {
	if (state == newState)
		return;

	animationList[currentAnimation]->restart();

	switch (newState) {
	case IDLE:
		v = Vector2f(0.f, 0.f);
		currentAnimation = idleE;
		break;
	case DAMAGED:
		animFinished = false;
		hit = true;
		currentAnimation = damageE;
		break;
	case DEAD:
		animFinished = false;
		phased = true;
		invulnerable = true;
		hit = false;
		currentAnimation = deathE;
		break;
	}
	state = newState;
}

void Slime::decideDirection() {
	left = false;
	right = false;
	up = false;
	down = false;

	if (std::abs(int(x - destination.x)) > std::max(getSpeed() / 2, std::abs(v.x))) {
		if (x < destination.x) right = true;
		else left = true;
	}

	if (std::abs(y - destination.y) > std::max(getSpeed() / 2, std::abs(v.y))) {
		if (y < destination.y) down = true;
		else up = true;
	}
}

void Slime::walk() {
	if (updateDirection()) {
		switch (direction) {
		case EAST: v = Vector2f(getSpeed() / 2, 0); break;
		case NORTHEAST: v = Vector2f(getSpeed() / 2 * DIAG_MOD, -getSpeed() / 2 * DIAG_MOD); break;
		case NORTH: v = Vector2f(0, -getSpeed() / 2); break;
		case NORTHWEST: v = Vector2f(-getSpeed() / 2 * DIAG_MOD, -getSpeed() / 2 * DIAG_MOD); break;
		case WEST: v = Vector2f(-getSpeed() / 2, 0); break;
		case SOUTHWEST: v = Vector2f(-getSpeed() / 2 * DIAG_MOD, getSpeed() / 2 * DIAG_MOD); break;
		case SOUTH: v = Vector2f(0, getSpeed() / 2); break;
		case SOUTHEAST: v = Vector2f(getSpeed() / 2 * DIAG_MOD, getSpeed() / 2 * DIAG_MOD); break;
		default: std::cout << "You've done the impossible... You're facing a direction I've never seen before!\n";
		}
		// currentAnimation = animType(direction + WALK_ANIM);
	}
	else setState(IDLE); // Idle animation if currently not moving.
}

void Slime::run() {
	if (updateDirection()) {
		switch (direction) {
		case EAST: v = Vector2f(getSpeed(), 0); break;
		case NORTHEAST: v = Vector2f(getSpeed() * DIAG_MOD, -getSpeed() * DIAG_MOD); break;
		case NORTH: v = Vector2f(0, -getSpeed()); break;
		case NORTHWEST: v = Vector2f(-getSpeed() * DIAG_MOD, -getSpeed() * DIAG_MOD); break;
		case WEST: v = Vector2f(-getSpeed(), 0); break;
		case SOUTHWEST: v = Vector2f(-getSpeed() * DIAG_MOD, getSpeed() * DIAG_MOD); break;
		case SOUTH: Vector2f(0, getSpeed()); break;
		case SOUTHEAST: Vector2f(getSpeed() * DIAG_MOD, getSpeed() * DIAG_MOD); break;
		default: std::cout << "You've done the impossible... You're facing a direction I've never seen before!\n";
		}
		// currentAnimation = animType(direction + RUN_ANIM);
	}
	else setState(IDLE); // Idle animation if currently not moving.
}

void Slime::dead() {
	v *= 0.95f;
	animFinished = animationList[currentAnimation]->isLastFrame();
}

