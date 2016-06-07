#include "Player.h"

#define SPEED 2.f

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
	Entity::init();
	// Get spritesheet memory locations from Resource Manager for every texture used by sprites
	Texture *tx0 = rm_master->getTexture("playerIdle.png");
	Texture *tx1 = rm_master->getTexture("playerWalk.png");
	Texture *tx2 = rm_master->getTexture("playerRun.png");
	Texture *tx3 = rm_master->getTexture("playerABS.png");
	Texture *tx4 = rm_master->getTexture("playerAtt1.png");
	Texture *tx5 = rm_master->getTexture("playerAtt2.png");
	Texture *tx6 = rm_master->getTexture("playerAttRec.png");
	Texture *tx7 = rm_master->getTexture("playerHit.png");
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
	// List of keys used by Player
	keyWatchlist.push_back((int)Keyboard::W);		// Player movement (WASD)
	keyWatchlist.push_back((int)Keyboard::A);
	keyWatchlist.push_back((int)Keyboard::S);
	keyWatchlist.push_back((int)Keyboard::D);
	keyWatchlist.push_back((int)Keyboard::Up);		// Dash movement (Arrow keys)
	keyWatchlist.push_back((int)Keyboard::Left);
	keyWatchlist.push_back((int)Keyboard::Down);
	keyWatchlist.push_back((int)Keyboard::Right);
	keyWatchlist.push_back((int)Keyboard::LShift);	// Walk modifier
	keyWatchlist.push_back((int)Keyboard::Space);	// Attack button

	keyWatchlist.push_back((int)Keyboard::LControl); // TEMP KEYS
	keyWatchlist.push_back((int)Keyboard::RControl);
	keyWatchlist.push_back((int)Keyboard::RShift);
	keyWatchlist.push_back((int)Keyboard::Q);
	std::cout << "player initialized\n";
}

Player::~Player() {};
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

void Player::update() {
	stateList oldState = state;
	animList oldAnimation = currentAnimation;
	// Update the player state
	updateState();
	// Perform the correct action depending on the state
	switch (state) {
	case IDLE: idle(); break;
	case WALK: walk(); break;
	case RUN: run(); break;
	case ATTACK_BACKSWING: abs();  break;
	case ATTACK_SWING: attack();  break;
	case ATTACK_RECOVER: attRec();  break;
	case DASH: dash(); break;
	default: std::cout << "wat\n";
	}

	// Player has been hit. Invulnerable for a few seconds
	if (playerHit) flashCurrentSprite(oldAnimation);

	// Reset the current animation to its first frame so the animation isn't left on its last frame the next 
	// time it is used. Note that this keeps walk/run animations where they left off when switching directions.
	if (oldState != state ) animationList[oldAnimation]->restart();

	updatePosition();

	if (isInAnimList(currentAnimation)) 
		animationList[currentAnimation]->update(x, y);
	else 
		std::cout << "Invalid animation for player, can not update animation.\n";
}

void Player::updateState() {
	switch (state) {
	case IDLE:
	case WALK:
	case RUN:
		if (up || left || down || right) {
			if (shiftHeld)
				state = WALK;
			else
				state = RUN;
		}
		else
			state = IDLE;
		break;
	case ATTACK_BACKSWING: if (absFinished) { state = ATTACK_SWING; } break;
	case ATTACK_SWING: if (attFinished) { state = ATTACK_RECOVER; } break;
	case ATTACK_RECOVER: if (recFinished) { state = IDLE; } break;
	default: std::cout << "What did you do now?\n";
	}
}

// Player idle behavior
void Player::idle() {
	dx = 0;
	dy = 0;
	attackType = 0;
	absFinished = false;
	attFinished = false;
	recFinished = false;
	currentAnimation = animList(direction);
}

// Player walk behavior
void Player::walk() {
	if (updateDirection())  {
		switch (direction) {
		case EAST: dx = SPEED/2; dy = 0; break;
		case NORTHEAST: dx = SPEED/2 * DIAG_MOD; dy = -SPEED/2 * DIAG_MOD; break;
		case NORTH: dx = 0; dy = -SPEED/2; break;
		case NORTHWEST: dx = -SPEED/2 * DIAG_MOD; dy = -SPEED/2 * DIAG_MOD; break;
		case WEST: dx = -SPEED/2; dy = 0; break;
		case SOUTHWEST: dx = -SPEED/2 * DIAG_MOD; dy = SPEED/2 * DIAG_MOD; break;
		case SOUTH: dx = 0; dy = SPEED/2; break;
		case SOUTHEAST: dx = SPEED/2 * DIAG_MOD; dy = SPEED/2 * DIAG_MOD; break;
		default: std::cout << "You've done the impossible... You're facing a direction I've never seen before!\n";
		}
		currentAnimation = animList(direction + 8);
	}
	else idle(); // Idle animation if currently not moving.
}

// Player run behavior
void Player::run() {
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
		default: std::cout << "You've done the impossible... You're facing a direction I've never seen before!\n";
		}
		currentAnimation = animList(direction + 16);
	}
	else idle(); // Idle animation if currently not moving.
}

// Player attack backswing behavior
void Player::abs() {
	if (attackType <= maxAttacks) {
		dx = 0;
		dy = 0;
	}
	currentAnimation = animList(direction + 24);
	absFinished = animationList[currentAnimation]->isLastFrame();
}

// Player attack behavior
void Player::attack() {
	if (attackType == maxAttacks + 1) { dx = 0; dy = 0; }
	currentAnimation = animList(direction + 32);
	attFinished = animationList[currentAnimation]->isLastFrame();
}

// Player attack recover behavior
void Player::attRec() {
	currentAnimation = animList(direction + 64);
	recFinished = animationList[currentAnimation]->isLastFrame();
}

// Player dash behavior
void Player::dash() {

}

/*
 *	Flashes the current sprite. The old animation animList type is passed in to reset any animations whose
 *	color has been changed while the player is changing animations.
 */
void Player::flashCurrentSprite(animList oldAnimation) {
	flashDmg += 0.12f;
	if (flashDmg > 12) { playerHit = false; flashDmg = 0; }
	if (int(flashDmg) %2 == 1) animationList[currentAnimation]->setColor(Color(240, 50, 0));
	else animationList[currentAnimation]->setColor(Color(255, 255, 255));
	// Checking if sprite changed, and resetting the old sprite back to its original color:
	if (oldAnimation != currentAnimation) animationList[oldAnimation]->setColor(Color(255, 255, 255));
}

void Player::keyHeld(Keyboard::Key key) {
	if (key == Keyboard::Space) {
		if (state == IDLE || state == WALK) {	// Initial attack
			attackType = 0;
			state = ATTACK_BACKSWING;
		}
		if (state == ATTACK_RECOVER) {			// Combo attacks
			if (attackType < maxAttacks) {
				attackType++;
				state = ATTACK_BACKSWING;
				absFinished = false;
				attFinished = false;
			}
		}
		if (state == RUN) {						// Run attack
			attackType = maxAttacks + 1;
			state = ATTACK_BACKSWING;
		}
	}
}

void Player::keyPress(Keyboard::Key key) {
	if (key == Keyboard::LShift) shiftHeld = true; 
	if (key == Keyboard::RShift) { 
		SpriteEffect *spr = new SpriteEffect(animationList[currentAnimation]->sprite, x, y, 50, 2); 
		spriteEffectList.push_back(spr); 
		spr->setRotationSpeed(8); 
	}
	if (key == Keyboard::LControl) playerHit = true;
	if (key == Keyboard::RControl) playerHit = false;
	if (key == Keyboard::Q) {
		if (weight != 20)
			weight = 20;
		else
			weight = 8;
		/* FOR LINE TESTS
		std::pair<Vector2f, Vector2f> l; l.first = Vector2f(100.0f, 20.f); l.second = Vector2f(100.0f, 90.f);
		std::pair<Vector2f, Vector2f> l2; l2.first = Vector2f(130.0f, 20.f); l2.second = Vector2f(170.0f, 90.f);
		std::pair<Vector2f, Vector2f> l3; l3.first = Vector2f(200.0f, 90.f); l3.second = Vector2f(250.0f, 20.f);
		std::pair<Vector2f, Vector2f> l4; l4.first = Vector2f(300.0f, 90.f); l4.second = Vector2f(350.0f, 90.f);
		std::cout << "Intersects: " << intersectsLine(l) << " " << intersectsLine(l2) << " " << intersectsLine(l3) << " " << intersectsLine(l4) << "\n";
		*/
	}
	if (key == Keyboard::W) up = true;
	if (key == Keyboard::A) left = true;
	if (key == Keyboard::S) down = true;
	if (key == Keyboard::D) right = true;
}
void Player::keyRelease(Keyboard::Key key) {
	if (key == Keyboard::LShift) shiftHeld = false;
	if (key == Keyboard::W) { up = false; }
	if (key == Keyboard::A) { left = false; }
	if (key == Keyboard::S) { down = false; }
	if (key == Keyboard::D) { right = false; }
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