#include "Player.h"
#include <iostream>

#define SPEED 2.f
#define DASH_TIMER_SPEED 0.05f
#define PLAYER_FLASHTIMER 9.f;

#define LENGTH 28.f
#define DISTANCE 17.f
#define ATT_FORCE 2.f
#define ATT_BASE_STR 10

const unsigned int Player::entityType = 0x80000001;

void Player::init() {
	// Initialize inherited variables
	name = "El";
	cWidth = 16;
	cHeight = 20;
	life = 100;
	maxLife = life;
	maxAttacks = 2;
	currentAnimation = idleE;
	weight = 8;
	// Get spritesheet memory locations from Resource Manager for every texture used by sprites
	Texture *tx0 = rm_master->getTexture("playerIdle.png");
	Texture *tx1 = rm_master->getTexture("playerWalk.png");
	Texture *tx2 = rm_master->getTexture("playerRun.png");
	Texture *tx3 = rm_master->getTexture("playerABS.png");
	Texture *tx4 = rm_master->getTexture("playerAtt1.png");
	Texture *tx5 = rm_master->getTexture("playerAtt2.png");
	Texture *tx6 = rm_master->getTexture("playerAttRec.png");
	Texture *tx7 = rm_master->getTexture("playerHit.png");
	Texture *tx8 = rm_master->getTexture("playerDeath.png");
	// IDLE ANIMATIONS //////////////////////////////////////////////////////
	animationList[idleE] = new Animation(tx0, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[idleE]->setRotation(270); 
	animationList[idleNE] = new Animation(tx0, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[idleNE]->setRotation(315);
	animationList[idleN] = new Animation(tx0, 0.f, 0.f, 50, 50, 4, 0.2f, true);
	animationList[idleNW] = new Animation(tx0, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[idleNW]->setRotation(45);
	animationList[idleW] = new Animation(tx0, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[idleW]->setRotation(90);
	animationList[idleSW] = new Animation(tx0, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[idleSW]->setRotation(135);
	animationList[idleS] = new Animation(tx0, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[idleS]->setRotation(180);
	animationList[idleSE] = new Animation(tx0, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[idleSE]->setRotation(225);
	// WALKING ANIMATIONS ///////////////////////////////////////////////////
	animationList[walkE] = new Animation(tx1, 0.f, 0.f, 48, 48, 8, 0.2f, true); animationList[walkE]->moveOrigin(0, 7);
	animationList[walkNE] = new Animation(tx1, 0.f, 96.f, 48, 48, 8, 0.2f, true); animationList[walkNE]->moveOrigin(0, 7);
	animationList[walkN] = new Animation(tx1, 0.f, 48.f, 48, 48, 8, 0.2f, true); animationList[walkN]->moveOrigin(0, 7);
	animationList[walkNW] = new Animation(tx1, 0.f, 144.f, 48, 48, 8, 0.2f, true); animationList[walkNW]->moveOrigin(0, 7);
	animationList[walkW] = new Animation(tx1, 0.f, 336.f, 48, 48, 8, 0.2f, true); animationList[walkW]->moveOrigin(0, 7);
	animationList[walkSW] = new Animation(tx1, 0.f, 288.f, 48, 48, 8, 0.2f, true); animationList[walkSW]->moveOrigin(0, 7);
	animationList[walkS] = new Animation(tx1, 0.f, 192.f, 48, 48, 8, 0.2f, false); animationList[walkS]->moveOrigin(0, 7);
	animationList[walkSE] = new Animation(tx1, 0.f, 240.f, 48, 48, 8, 0.2f, true); animationList[walkSE]->moveOrigin(0, 7);
	// RUNING ANIMATIONS ////////////////////////////////////////////////////
	animationList[runE] = new Animation(tx2, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[runE]->setRotation(270);
	animationList[runNE] = new Animation(tx2, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[runNE]->setRotation(315);
	animationList[runN] = new Animation(tx2, 0.f, 0.f, 50, 50, 4, 0.2f, true);
	animationList[runNW] = new Animation(tx2, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[runNW]->setRotation(45);
	animationList[runW] = new Animation(tx2, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[runW]->setRotation(90);
	animationList[runSW] = new Animation(tx2, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[runSW]->setRotation(135);
	animationList[runS] = new Animation(tx2, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[runS]->setRotation(180);
	animationList[runSE] = new Animation(tx2, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[runSE]->setRotation(225);
	// ATTACK BACKSWING ANIMATION ///////////////////////////////////////////
	animationList[ABSE] = new Animation(tx3, 0.f, 0.f, 50, 50, 5, 0.2f, false); animationList[ABSE]->setRotation(270);
	animationList[ABSNE] = new Animation(tx3, 0.f, 0.f, 50, 50, 5, 0.2f, false); animationList[ABSNE]->setRotation(315);
	animationList[ABSN] = new Animation(tx3, 0.f, 0.f, 50, 50, 5, 0.2f, false);
	animationList[ABSNW] = new Animation(tx3, 0.f, 0.f, 50, 50, 5, 0.2f, false); animationList[ABSNW]->setRotation(45);
	animationList[ABSW] = new Animation(tx3, 0.f, 0.f, 50, 50, 5, 0.2f, false); animationList[ABSW]->setRotation(90);
	animationList[ABSSW] = new Animation(tx3, 0.f, 0.f, 50, 50, 5, 0.2f, false); animationList[ABSSW]->setRotation(135);
	animationList[ABSS] = new Animation(tx3, 0.f, 0.f, 50, 50, 5, 0.2f, false); animationList[ABSS]->setRotation(180);
	animationList[ABSSE] = new Animation(tx3, 0.f, 0.f, 50, 50, 5, 0.2f, false); animationList[ABSSE]->setRotation(225);
	// ATTACK 1 ANIMATIONS //////////////////////////////////////////////////
	animationList[attack1E] = new Animation(tx4, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attack1E]->setRotation(270);
	animationList[attack1NE] = new Animation(tx4, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attack1NE]->setRotation(315);
	animationList[attack1N] = new Animation(tx4, 0.f, 0.f, 50, 50, 6, 0.2f, false);
	animationList[attack1NW] = new Animation(tx4, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attack1NW]->setRotation(45);
	animationList[attack1W] = new Animation(tx4, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attack1W]->setRotation(90);
	animationList[attack1SW] = new Animation(tx4, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attack1SW]->setRotation(135);
	animationList[attack1S] = new Animation(tx4, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attack1S]->setRotation(180);
	animationList[attack1SE] = new Animation(tx4, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attack1SE]->setRotation(225);
	// ATTACK 2 ANIMATIONS //////////////////////////////////////////////////
	// ATTACK RECOVER ANIMATIONS ////////////////////////////////////////////
	animationList[attRecE] = new Animation(tx6, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attRecE]->setRotation(270);
	animationList[attRecNE] = new Animation(tx6, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attRecNE]->setRotation(315);
	animationList[attRecN] = new Animation(tx6, 0.f, 0.f, 50, 50, 6, 0.2f, false);
	animationList[attRecNW] = new Animation(tx6, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attRecNW]->setRotation(45);
	animationList[attRecW] = new Animation(tx6, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attRecW]->setRotation(90);
	animationList[attRecSW] = new Animation(tx6, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attRecSW]->setRotation(135);
	animationList[attRecS] = new Animation(tx6, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attRecS]->setRotation(180);
	animationList[attRecSE] = new Animation(tx6, 0.f, 0.f, 50, 50, 6, 0.2f, false); animationList[attRecSE]->setRotation(225);
	// DAMAGED ANIMATIONS ///////////////////////////////////////////////////
	// DEATH ANIMATIONS /////////////////////////////////////////////////////
	animationList[deathE] = new Animation(tx8, 0.f, 0.f, 50, 50, 8, 0.2f, false); animationList[deathE]->setRotation(270);
	animationList[deathNE] = new Animation(tx8, 0.f, 0.f, 50, 50, 8, 0.2f, false); animationList[deathNE]->setRotation(315);
	animationList[deathN] = new Animation(tx8, 0.f, 0.f, 50, 50, 8, 0.2f, false);
	animationList[deathNW] = new Animation(tx8, 0.f, 0.f, 50, 50, 8, 0.2f, false); animationList[deathNW]->setRotation(45);
	animationList[deathW] = new Animation(tx8, 0.f, 0.f, 50, 50, 8, 0.2f, false); animationList[deathW]->setRotation(90);
	animationList[deathSW] = new Animation(tx8, 0.f, 0.f, 50, 50, 8, 0.2f, false); animationList[deathSW]->setRotation(135);
	animationList[deathS] = new Animation(tx8, 0.f, 0.f, 50, 50, 8, 0.2f, false); animationList[deathS]->setRotation(180);
	animationList[deathSE] = new Animation(tx8, 0.f, 0.f, 50, 50, 8, 0.2f, false); animationList[deathSE]->setRotation(225);
	// List of keys used by Player
	keyWatchlist.push_back((int)Keyboard::W);		// Player movement (WASD)
	keyWatchlist.push_back((int)Keyboard::A);
	keyWatchlist.push_back((int)Keyboard::S);
	keyWatchlist.push_back((int)Keyboard::D);
	keyWatchlist.push_back((int)Keyboard::Up);		// Dash movement (Arrow keys)
	keyWatchlist.push_back((int)Keyboard::Left);
	keyWatchlist.push_back((int)Keyboard::Down);
	keyWatchlist.push_back((int)Keyboard::Right);
	keyWatchlist.push_back((int)Keyboard::LShift);	// Run modifier
	keyWatchlist.push_back((int)Keyboard::Space);	// Attack button
	// TEMP KEYS ///////////////////////////////////////////////////////////
	keyWatchlist.push_back((int)Keyboard::LControl);
	keyWatchlist.push_back((int)Keyboard::RControl);
	keyWatchlist.push_back((int)Keyboard::RShift);
	keyWatchlist.push_back((int)Keyboard::Q);
	
	std::cout << "Player initialized\n";
}

Player::Player(ResourceManager *rm) {
	rm_master = rm;
	init();
}

Player::Player(float startX, float startY, ResourceManager *rm) {
	rm_master = rm;
	x = startX;
	y = startY;
	init();
}

unsigned int Player::getType() {
	return Player::entityType;
}

float Player::getSpeed() {
	return SPEED;
}

float Player::getFlashTimer() {
	return PLAYER_FLASHTIMER;
}

void Player::update() {
	animType oldAnimation = currentAnimation;
	// Update the player state
	updateState();
	// Perform the correct update depending on the state
	switch (state) {
	case IDLE: idle(); break;
	case WALK: walk(); break;
	case RUN: run(); break;
	case ATTACK_BACKSWING: abs();  break;
	case ATTACK_SWING: attack();  break;
	case ATTACK_RECOVER: attRec();  break;
	case DAMAGED: damaged(); break;
	case DASH: dash(); break;
	case DEAD: dead(); break;
	default: std::cout << "wat\n";
	}
	// If the Player has been hit, flash the current sprite.
	flashCurrentSprite(oldAnimation);

	updatePosition();
}

/*
 *	Switch states depending on the current state and what actions the player wants
 *	to perform.
 */
void Player::updateState() {
	switch (state) {
	case IDLE:
	case WALK:
	case RUN:
		if (issuedDash())
			setState(DASH);
		else if (issuedMove()) {
			if (running) setState(RUN);
			else setState(WALK);
		}
		else setState(IDLE);
		break;
	case ATTACK_BACKSWING: 
		if (issuedDash()) 
			setState(DASH);
		else if (animFinished) 
			setState(ATTACK_SWING);
		break;
	case ATTACK_SWING: 
		if (animFinished) 
			setState(ATTACK_RECOVER);
		break;
	case ATTACK_RECOVER: 
		if (issuedDash()) 
			setState(DASH);
		else if (animFinished)
			setState(IDLE);
		break;
	case DAMAGED:
		if (animFinished)
			setState(IDLE);
		break;
	case DASH:
		dashTimer += DASH_TIMER_SPEED;
		if (dashTimer > 1) { 
			dashTimer = 0; 
			setState(IDLE);
			setInvulFalse();
		}
		break;
	case DEAD: 
		if (issuedDash()) // REVIVE!!!! for testing purposes of course.
			setState(DASH);
		break;
	default: std::cout << "What did you do now?\n";
	}
}

/*
 *	Set Player properties to correct values when switching states
 */
void Player::setState(stateType newState) {
	if (state == newState)
		return;

	animationList[currentAnimation]->restart();

	switch (newState) {
	case IDLE:
		v = Vector2f(0.f, 0.f);
		attackType = 0;
		phased = false;
		dashU = false; dashL = false; dashD = false; dashR = false;
		currentAnimation = animType(direction);
		break;
	case ATTACK_BACKSWING:
		animFinished = false;
		if (attackType <= maxAttacks) 
			v = Vector2f(0.f, 0.f);
		currentAnimation = animType(direction + ABS_ANIM);
		break;
	case ATTACK_SWING:
		animFinished = false;
		v = Vector2f(0.f, 0.f);
		currentAnimation = animType(direction + ATT1_ANIM);
		generateAttack();
		break;
	case ATTACK_RECOVER:
		animFinished = false;
		currentAnimation = animType(direction + AREC_ANIM);
		break;
	case DAMAGED:
		animFinished = false;
		hit = true;
		invulnerable = true;
		currentAnimation = animType(direction + AREC_ANIM);
		break;
	case DASH:
		phased = true;
		invulnerable = true;
		break;
	case DEAD:
		animFinished = false;
		phased = true;
		hit = false;
		invulnerable = true;
		currentAnimation = animType(direction + DEAD_ANIM);
		break;
	}
	state = newState;
}

/*
 *	Set player to stop being invulnerable if certain conditions are met.
 */
void Player::setInvulFalse() {
	if (!hit && state != DASH) 
		invulnerable = false;
}

/*
 *	Generate an attack with proper animation and force depending on the current attackType
 */
void Player::generateAttack() {
	std::vector<std::pair<Vector2f, Vector2f>> attLines;
	Texture *t;
	Animation *anim;
	Vector2f pos, f;
	switch (attackType) {
	case 0:
	case 1:
		attLines.push_back(createNormalLine(LENGTH, DISTANCE));
		attLines.push_back(createNormalLine(LENGTH / 2, DISTANCE + 5));
		t = rm_master->getTexture("playerAttackAnim1.png");
		anim = new Animation(t, 0.f, 0.f, 16, 32, 5, 0.4f, false);
		anim->setRotation(-float(direction) * 45);
		pos = findMidpointOfLine(attLines.at(0));
		createAttack(pos, 1, 10, int(ATT_BASE_STR), Vector2f(0,0), attLines, anim);
		break;
	case 2:
	case 3:
	default:
		attLines.push_back(createNormalLine(LENGTH, DISTANCE));
		attLines.push_back(createNormalLine(LENGTH/2, DISTANCE + 5));
		f = generateForceFromDirection(ATT_FORCE);
		t = rm_master->getTexture("playerAttackAnim1.png");
		anim = new Animation(t, 0.f, 0.f, 16, 32, 5, 0.4f, false);
		anim->setRotation(-float(direction) * 45);
		pos = findMidpointOfLine(attLines.at(0));
		createAttack(pos, 1, 10, int(ATT_BASE_STR * 1.5f), f, attLines, anim);
	}
}

void Player::dash() {
	// Remove the dashTimer condition for fully controllable dash. Plan on making this a player upgrade to dash
	// at some point.
	if (updateDashDirection() && (dashTimer < 0.11)) {
		switch (direction) {
		case EAST: v = Vector2f(SPEED * 2.f, 0); break;
		case NORTHEAST: v = Vector2f(SPEED * 2.f * DIAG_MOD, -SPEED * 2.f * DIAG_MOD); break;
		case NORTH: v = Vector2f(0, -SPEED * 2.f); break;
		case NORTHWEST: v = Vector2f(-SPEED * 2.f * DIAG_MOD, -SPEED *2.f * DIAG_MOD); break;
		case WEST: v = Vector2f(-SPEED * 2.f, 0); break;
		case SOUTHWEST: v = Vector2f(-SPEED * 2.f * DIAG_MOD, SPEED * 2.f * DIAG_MOD); break;
		case SOUTH: v = Vector2f(0, SPEED * 2.f); break;
		case SOUTHEAST: v = Vector2f(SPEED * 2.f * DIAG_MOD, SPEED * 2.f * DIAG_MOD); break;
		default: std::cout << "You've done the impossible... You're facing a direction I've never seen before!\n";
		}
		currentAnimation = animType(direction + DASH_ANIM);
	}

	if (int(dashTimer * 20) % 2 == 0) {
		SpriteEffect *spr = new SpriteEffect(animationList[currentAnimation]->sprite, x, y, 26, 2);
		createSpriteEffect(spr);
	}
}

void Player::keyHeld(Keyboard::Key key) {
	if (key == Keyboard::Space) {
		if (state == IDLE || state == WALK) {	// Initial attack
			attackType = 0;
			setState(ATTACK_BACKSWING);
		}
		if (state == ATTACK_RECOVER) {			// Combo attacks
			if (attackType < maxAttacks) {
				attackType++;
				setState(ATTACK_BACKSWING);
			}
		}
		if (state == RUN) {						// Run attack
			attackType = maxAttacks + 1;
			setState(ATTACK_BACKSWING);
		}
	}
}

void Player::keyPress(Keyboard::Key key) {
	if (key == Keyboard::LShift) running = true; 
	if (key == Keyboard::RShift) { 
		SpriteEffect *spr = new SpriteEffect(animationList[currentAnimation]->sprite, x, y, 50, 16); 
		spr->setRotationSpeed(8); 
		createSpriteEffect(spr);
	}
	if (key == Keyboard::LControl) { damage(32); std::cout << "Life: " << life << "\n"; }
	if (key == Keyboard::RControl) recover(500);
	if (key == Keyboard::Q) {
		//createNewEntity("Slime", Vector2f(100.f, 100.f));
		//* ENTITY INTERACTION TESTS
		// Access entity at position. For things like text box conversations, or pressing a button.
		Entity * t = getEntityAt(createNormalLine(8.f, float(cWidth/2 + 8)));
		if (t == nullptr) {
			t = getEntityById(25);
			if (t == nullptr)
				return;
			std::cout << "Entity is: " << t->name << " (" << t->ID << "), life: (" << t->life <<
				"/" << t->maxLife << ")\n";
			return;
		}
		std::cout << "Entity is: " << t->name << " (" << t->ID << "), life: (" << t->life <<
			"/" << t->maxLife << ")\n";
	}
	if (key == Keyboard::W) up = true;
	if (key == Keyboard::A) left = true;
	if (key == Keyboard::S) down = true;
	if (key == Keyboard::D) right = true;
	if (key == Keyboard::Up) { dashU = true; }
	if (key == Keyboard::Left) { dashL = true; }
	if (key == Keyboard::Down) { dashD = true; }
	if (key == Keyboard::Right) { dashR = true; }
}
void Player::keyRelease(Keyboard::Key key) {
	if (key == Keyboard::LShift) running = false;
	if (key == Keyboard::W) { up = false; }
	if (key == Keyboard::A) { left = false; }
	if (key == Keyboard::S) { down = false; }
	if (key == Keyboard::D) { right = false; }
	if (key == Keyboard::Up) { dashU = false; }
	if (key == Keyboard::Left) { dashL = false; }
	if (key == Keyboard::Down) { dashD = false; }
	if (key == Keyboard::Right) { dashR = false; }
}

void Player::render(RenderWindow *window) {
	// RENDER COLLISION BOX
	RectangleShape sh(Vector2f(cWidth * 1.f, cHeight * 1.f));
	sh.setFillColor(Color(0, 0, 128, 160));
	sh.setOutlineColor(Color::Blue);
	sh.setOutlineThickness(1.0f);
	sh.setPosition((float)cX, (float)cY);
	window->draw(sh);
}
