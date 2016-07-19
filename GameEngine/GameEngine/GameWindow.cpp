#include "GameWindow.h"

using namespace sf;

extern int WWIDTH;
extern int WHEIGHT;

GameWindow::~GameWindow(void) {}
GameWindow::GameWindow(RenderWindow* window, float width, float height, bool isLimited) {
	nativeRenderer = window;
	limited = isLimited;
	bounds = Vector2u(80, 60);
	view = View(Vector2f(width / 2, height / 2), Vector2f(width, height));

	nativeRenderer->setView(view);
}

void GameWindow::start() {
	nativeRenderer->clear();
}

void GameWindow::end() {
	nativeRenderer->display();
}

RenderWindow *GameWindow::getNative() {
	return nativeRenderer;
}

View *GameWindow::getView() {
	return &view;
}

void GameWindow::setLimit(bool limit) {
	limited = limit;
}

void GameWindow::updateView(Entity *entity) {
	if (entity == nullptr || (view.getSize().x > WWIDTH && view.getSize().y > WHEIGHT))
		return;
	boundViewX(entity->x);
	boundViewY(entity->y);
	nativeRenderer->setView(view);
}

void GameWindow::setViewBounds(unsigned int width, unsigned int height) {
	bounds = Vector2u(width, height);
}

void GameWindow::setLetterboxView() {
	int winW = nativeRenderer->getSize().x;
	int winH = nativeRenderer->getSize().y;


	float winRatio = winW / float(winH);
	float viewRatio = view.getSize().x / view.getSize().y;

	float sizeX, sizeY, posX, posY;
	sizeX = 1.f; posX = 0.f;
	sizeY = 1.f; posY = 0.f;

	if (winRatio >= viewRatio) {
		sizeX = viewRatio / winRatio;
		posX = (1 - sizeX) / 2.f;
	}

	else {
		sizeY = winRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	view.setViewport(FloatRect(posX, posY, sizeX, sizeY));
}

void GameWindow::boundViewX(float centerX) {
	float x, vsX;

	vsX = view.getSize().x;
	x = view.getCenter().x;

	if (centerX > x + bounds.x / 2) 	 // Right edge case
		x += centerX - (x + bounds.x / 2);
	else if (centerX < x - bounds.x / 2) // Left edge case
		x -= (x - bounds.x / 2) - centerX;

	if (limited) {
		if (x < vsX / 2)				 // Leftmost bound
			x = vsX / 2;
		else if (x > WWIDTH - vsX / 2)	 // Rightmost bound
			x = WWIDTH - vsX / 2;
	}
	view.setCenter(x, view.getCenter().y);
}

void GameWindow::boundViewY(float centerY) {
	float y, vsY;

	vsY = view.getSize().y;
	y = view.getCenter().y;

	if (centerY > y + bounds.y / 2) 	 // Bottom edge case
		y += centerY - (y + bounds.y / 2);
	else if (centerY < y - bounds.y / 2) // Top edge case
		y -= (y - bounds.y / 2) - centerY;

	if (limited) {
		if (y < vsY / 2)				 // Topmost bound
			y = vsY / 2;
		else if (y > WHEIGHT - vsY / 2)	 // Bottommost bound
			y = WHEIGHT - vsY / 2;
	}
	view.setCenter(view.getCenter().x, y);
}

void GameWindow::renderDO(DrawableObject *d) const {
	if (d->isVisible())
		d->render(nativeRenderer);
}

void GameWindow::renderTiles(const SpriteRenderer &sr) const {
	sr.renderTiles(nativeRenderer);
}

void GameWindow::render(const std::pair<Vector2f, Vector2f> &line) const {
	Vertex l[2];
	l[0] = Vertex(line.first);
	l[1] = Vertex(line.second);
	nativeRenderer->draw(l, 2, Lines);
}

void GameWindow::render(const FloatRect &rect) const {
	RectangleShape sh(Vector2f(rect.width, rect.height));
	sh.setFillColor(Color(0, 0, 0, 0));
	sh.setOutlineColor(Color::White);
	sh.setOutlineThickness(1.0f);
	sh.setPosition(rect.left, rect.top);
	nativeRenderer->draw(sh);
}

void GameWindow::render(Collidable *c) const {
	RectangleShape sh(Vector2f(c->cWidth*1.f, c->cHeight*1.f));
	sh.setFillColor(Color(0, 128, 0, 160));
	sh.setOutlineColor(Color::Green);
	sh.setOutlineThickness(1.0f);
	sh.setPosition((float)c->cX, (float)c->cY);
	nativeRenderer->draw(sh);
}

void GameWindow::render(const TileMap &tileMap) const {
	nativeRenderer->draw(tileMap);
}

void GameWindow::render(const SpriteRenderer &sr) const {
	sr.render(nativeRenderer);
}

void GameWindow::render(const CollisionGrid &cg) const {
	cg.render(nativeRenderer);
}

void GameWindow::render(const CollisionGrid &cg, short int gridPos[]) const {
	cg.render(nativeRenderer, gridPos);
}

void GameWindow::render(const CollisionGrid &cg, std::map<short int, unsigned short int> gridPos) const {
	cg.render(nativeRenderer, gridPos);
}
