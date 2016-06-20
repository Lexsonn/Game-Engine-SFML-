#include "Attack.h"

extern int WWIDTH;
extern int WHEIGHT;

Attack::~Attack() {}
Attack::Attack() : ID(0), parent(0), type(0), currentLife(0), strength(0), force(Vector2f(0,0)) { }
Attack::Attack(unsigned short int _ID, unsigned short int parentID, unsigned short int _type, short int life, short int str, 
			   std::vector<std::pair<Vector2f, Vector2f>> lineList, Animation *anim) : force(Vector2f(0, 0)) {
	ID = _ID;
	parent = parentID;
	type = _type;
	currentLife = life;
	strength = str;
	attackLines = lineList;
	animation = anim;
	//generateGridPos();
}

void Attack::generateGridPos() {
	int height = (WHEIGHT - 1) / GRID_HEIGHT;
	unsigned short int num = 0;
	for (auto l : attackLines) {
		bool diagLine = false;
		int diffX = int(l.second.x) / GRID_WIDTH - int(l.first.x) / GRID_WIDTH;
		int diffY = int(l.second.y) / GRID_HEIGHT - int(l.first.y) / GRID_HEIGHT;
		int x = int(l.first.x) / GRID_WIDTH;
		int y = int(l.first.y) / GRID_HEIGHT;
		int x_inc = 0, y_inc = 0;

		if (diffX > 0) x_inc = 1;
		else if (diffX < 0) x_inc = -1;
		if (diffY > 0) y_inc = 1;
		else if (diffY < 0) y_inc = -1;

		// ADD METHOD FOR CHEKING IF LINE BISECTS ONLY ON DIAGONALS

		// First point
		if (validGridPos(x, y)) 
			gridPos.insert(std::pair<short int, unsigned short int>(x * (height + 1) + y, ID));

		while (abs(diffX) > 0 || abs(diffY) > 0) {
			bool xx = false, yy = false;
			if (gridIntersects(x + x_inc, y, l)) {
				xx = true;
				if (validGridPos(x + x_inc, y))
					gridPos.insert(std::pair<short int, unsigned short int>((x + x_inc) * (height + 1) + y, ID));
			}
			if (gridIntersects(x, y + y_inc, l)) {
				yy = true;
				if (validGridPos(x, y + y_inc))
					gridPos.insert(std::pair<short int, unsigned short int>(x * (height + 1) + y + y_inc, ID));
			}
			if (!xx && !yy) {
				if (gridIntersects(x + x_inc, y + y_inc, l)) {
					xx = true; yy = true;
					if (validGridPos(x + x_inc, y + y_inc))
						gridPos.insert(std::pair<short int, unsigned short int>((x + x_inc) * (height + 1) + y + y_inc, ID));
				}
			}

			if (xx) { x += x_inc; diffX -= x_inc; }
			if (yy) { y += y_inc; diffY -= y_inc; }

			if (y_inc > 0 && diffY < 0) diffY = 0;
			if (y_inc < 0 && diffY > 0) diffY = 0;
			if (x_inc > 0 && diffX < 0) diffX = 0;
			if (x_inc < 0 && diffX > 0) diffX = 0;
		}
	}
}

bool Attack::validGridPos(int x, int y) {
	int width = (WWIDTH - 1) / GRID_WIDTH;
	int height = (WHEIGHT - 1) / GRID_HEIGHT;
	if (x < 0 || y < 0 || x > width || y > height)
		return false;

	return true;
}

bool Attack::gridIntersects(int x, int y, std::pair<Vector2f, Vector2f> line) {
	float left = float(x * GRID_WIDTH);
	float width = GRID_WIDTH * 1.f;
	float top = float(y * GRID_HEIGHT);
	float height = GRID_HEIGHT * 1.f;
	return lineIntersectsRect(left, top, width, height, line);
}

void Attack::update() {
	if (currentLife-- <= 0)
		return;
	animation->beginUpdate();

	animation->endUpdate();
}

void Attack::setPosition(float _x, float _y) {
	x = _x;
	y = _y;
	animation->updatePosition(x, y);
}

void Attack::setForce(float dx, float dy) {
	force = Vector2f(dx, dy);
}

Sprite &Attack::getSprite() {
	return animation->sprite;
}
