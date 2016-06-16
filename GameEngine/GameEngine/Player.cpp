#include "Player.h"

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
	keyWatchlist.push_back((int)Keyboard::LShift);	// Run modifier
	keyWatchlist.push_back((int)Keyboard::Space);	// Attack button

	keyWatchlist.push_back((int)Keyboard::LControl); // TEMP KEYS
	keyWatchlist.push_back((int)Keyboard::RControl);
	keyWatchlist.push_back((int)Keyboard::RShift);
	keyWatchlist.push_back((int)Keyboard::Q);
	
	std::cout << "player initialized\n";
}

//Player::~Player() {};
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
	stateType oldState = state;
	animType oldAnimation = currentAnimation;
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

	// If the Player has been hit, flash the current sprite.
	flashCurrentSprite(oldAnimation);

	// Reset the current animation to its first frame so the animation isn't left on its last frame the next 
	// time it is used. Note that this keeps walk/run animations where they left off when switching directions.
	if (oldState != state ) animationList[oldAnimation]->restart();

	updatePosition();
}

void Player::updateState() {
	switch (state) {
	case IDLE:
	case WALK:
	case RUN:
		if (dashU || dashL || dashD || dashR)
			setState(DASH);
		else if (up || left || down || right) {
			if (shiftHeld) setState(RUN);
			else setState(WALK);
		}
		else setState(IDLE);
		break;
	case ATTACK_BACKSWING: 
		if (dashU || dashL || dashD || dashR) 
			setState(DASH);
		else if (animFinished) 
			setState(ATTACK_SWING);
		break;
	case ATTACK_SWING: 
		if (animFinished) 
			setState(ATTACK_RECOVER);
		break;
	case ATTACK_RECOVER: 
		if (dashU || dashL || dashD || dashR) 
			setState(DASH);
		else if (animFinished)
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
	default: std::cout << "What did you do now?\n";
	}
}

/*
 *	Set Player properties to correct values when switching states
 */
void Player::setState(stateType type) {
	if (state == type)
		return;
	switch (type) {
	case IDLE:
		dx = 0;
		dy = 0;
		attackType = 0;
		phased = false;
		dashU = false; dashL = false; dashD = false; dashR = false;
		break;
	case ATTACK_BACKSWING:
		animFinished = false;
		if (attackType <= maxAttacks) {
			dx = 0;
			dy = 0;
		}
		currentAnimation = animType(direction + 24);
		break;
	case ATTACK_SWING:
		animFinished = false;
		dx = 0; 
		dy = 0; 
		currentAnimation = animType(direction + 32);
		break;
	case ATTACK_RECOVER:
		animFinished = false;
		currentAnimation = animType(direction + 64);
		break;
	case DASH:
		phased = true;
		invulnerable = true;
		break;
	}
	state = type;
}

/*
 *	Set player to stop being invulnerable if certain conditions are met.
 *	To be called after updating the state of the Player.
 */
void Player::setInvulFalse() {
	if (!hit && state != DASH) 
		invulnerable = false;
}

// Player idle behavior
void Player::idle() {
	currentAnimation = animType(direction);
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
		currentAnimation = animType(direction + 8);
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
		currentAnimation = animType(direction + 16);
	}
	else idle(); // Idle animation if currently not moving.
}

// Player attack backswing behavior
void Player::abs() {
	animFinished = animationList[currentAnimation]->isLastFrame();
}

// Player attack behavior
void Player::attack() {
	animFinished = animationList[currentAnimation]->isLastFrame();
}

// Player attack recover behavior
void Player::attRec() {
	animFinished = animationList[currentAnimation]->isLastFrame();
}

// Player dash behavior
void Player::dash() {
	// Remove the dashTimer condition for fully controllable dash. Plan on making this a player upgrade to dash
	// at some point.
	if (updateDashDirection() && (dashTimer < 0.11)) {
		switch (direction) {
		case EAST: dx = SPEED * 2.f; dy = 0; break;
		case NORTHEAST: dx = SPEED * 2.f * DIAG_MOD; dy = -SPEED * 2.f * DIAG_MOD; break;
		case NORTH: dx = 0; dy = -SPEED * 2.f; break;
		case NORTHWEST: dx = -SPEED * 2.f * DIAG_MOD; dy = -SPEED *2.f * DIAG_MOD; break;
		case WEST: dx = -SPEED * 2.f; dy = 0; break;
		case SOUTHWEST: dx = -SPEED * 2.f * DIAG_MOD; dy = SPEED * 2.f * DIAG_MOD; break;
		case SOUTH: dx = 0; dy = SPEED * 2.f; break;
		case SOUTHEAST: dx = SPEED * 2.f * DIAG_MOD; dy = SPEED * 2.f * DIAG_MOD; break;
		default: std::cout << "You've done the impossible... You're facing a direction I've never seen before!\n";
		}
		currentAnimation = animType(direction + 8);
	}

	if (int(dashTimer*20) % 2 == 0) {
		SpriteEffect *spr = new SpriteEffect(animationList[currentAnimation]->sprite, x, y, 26, 2);
		spriteEffectList.push_back(spr);
	}
}

/*
 *	Flashes the current sprite. The old animation animList type is passed in to reset any animations whose
 *	color has been changed while the Entity is changing animations.
 */
void Player::flashCurrentSprite(animType oldAnimation) {
	if (!hit)
		return;
	flashDmg += 0.12f;
	if (flashDmg > 9) { hit = false; flashDmg = 0; setInvulFalse(); }
	if (int(flashDmg) %2 == 1) animationList[currentAnimation]->setColor(Color(240, 50, 0));
	else animationList[currentAnimation]->setColor(Color(255, 255, 255));
	// Checking if sprite changed, and resetting the old sprite back to its original color:
	if (oldAnimation != currentAnimation) animationList[oldAnimation]->setColor(Color(255, 255, 255));
}

bool Player::updateDashDirection() {
	if (!dashL && dashR) {	// EAST/NORTHEAST/SOUTHEAST
		if (!dashU && dashD) { direction = SOUTHEAST; return true; }
		if (dashU && !dashD) { direction = NORTHEAST; return true; }
		direction = EAST;
		return true;
	}
	if (dashL && !dashR) {	// WEST/NORTHWEST/SOUTHWEST
		if (!dashU && dashD) { direction = SOUTHWEST; return true; }
		if (dashU && !dashD) { direction = NORTHWEST; return true; }
		direction = WEST;
		return true;
	}
	if (dashU && !dashD) { direction = NORTH; return true; }
	if (!dashU && dashD) { direction = SOUTH; return true; }

	return false; // No direction is being held right now.
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
	if (key == Keyboard::LShift) shiftHeld = true; 
	if (key == Keyboard::RShift) { 
		SpriteEffect *spr = new SpriteEffect(animationList[currentAnimation]->sprite, x, y, 50, 16); 
		spriteEffectList.push_back(spr); 
		spr->setRotationSpeed(8); 
	}
	if (key == Keyboard::LControl) { damage(32); std::cout << "Life: " << life << "\n"; }
	if (key == Keyboard::RControl) recover(500);
	if (key == Keyboard::Q) {
		/* ENTITY PUSHING TESTS
		if (weight != 20)
			weight = 20;
		else
			weight = 8;
		//*/
		//* ENTITY INTERACTION TESTS
		// Access entity at position. For things like text box conversations.
		std::pair<Vector2f, Vector2f> line = getAccessorLineFromDirection(); 
		Entity * t = getEntityAt(line);

		if (t == nullptr)
			return;

		std::cout << "Entity is: " << t->ID << "\n";
		//*/
		//std::cout << "GridPos: " << gridPos[0] << ", " << gridPos[1] << ", " << gridPos[2] << ", " << gridPos[3] << "\n";
		/* LINE INTERSECTION TESTS
		std::pair<Vector2f, Vector2f> l; l.first = Vector2f(100.0f, 20.f); l.second = Vector2f(100.0f, 90.f);
		std::pair<Vector2f, Vector2f> l2; l2.first = Vector2f(130.0f, 20.f); l2.second = Vector2f(170.0f, 90.f);
		std::pair<Vector2f, Vector2f> l3; l3.first = Vector2f(200.0f, 90.f); l3.second = Vector2f(250.0f, 20.f);
		std::pair<Vector2f, Vector2f> l4; l4.first = Vector2f(300.0f, 90.f); l4.second = Vector2f(350.0f, 90.f);
		std::cout << "Intersects: " << intersectsLine(l) << " " << intersectsLine(l2) << " " << intersectsLine(l3) << " " << intersectsLine(l4) << "\n";
		//*/
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
	if (key == Keyboard::LShift) shiftHeld = false;
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