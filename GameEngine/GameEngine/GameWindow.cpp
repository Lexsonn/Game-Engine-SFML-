#include "GameWindow.h"

using namespace sf;

extern int WWIDTH;
extern int WHEIGHT;

GameWindow::~GameWindow(void) {}
GameWindow::GameWindow(RenderWindow* window, float width, float height, bool isLimited) {
	nativeRenderer = window;

	limited = isLimited;
	rectW = 80;
	rectH = 60;
	view = View();
	view.setCenter(width/2, height/2);
	view.setSize(width, height);

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

void GameWindow::updateView(Entity *entity) {
	boundViewX(entity->x);
	boundViewY(entity->y);
	nativeRenderer->setView(view);
}

void GameWindow::setViewBounds(float width, float height) {
	rectW = abs(width);
	rectH = abs(height);
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

	if (centerX > x + rectW / 2) 		// Right edge case
		x += centerX - (x + rectW / 2);
	else if (centerX < x - rectW / 2)	// Left edge case
		x -= (x - rectW / 2) - centerX;

	if (limited) {
		if (x < vsX / 2)				// Leftmost bound
			x = vsX / 2;
		else if (x > WWIDTH - vsX / 2)	// Rightmost bound
			x = WWIDTH - vsX / 2;
	}
	view.setCenter(x, view.getCenter().y);
}

void GameWindow::boundViewY(float centerY) {
	float y, vsY;

	vsY = view.getSize().y;
	y = view.getCenter().y;

	if (centerY > y + rectH / 2) 		// Bottom edge case
		y += centerY - (y + rectH / 2);
	else if (centerY < y - rectH / 2)	// Top edge case
		y -= (y - rectH / 2) - centerY;

	if (limited) {
		if (y < vsY / 2)				// Topmost bound
			y = vsY / 2;
		else if (y > WHEIGHT - vsY / 2)	// Bottommost bound
			y = WHEIGHT - vsY / 2;
	}
	view.setCenter(view.getCenter().x, y);
}

void GameWindow::renderDO(DrawableObject *d) {
	if (d->isVisible())
		d->render(nativeRenderer);
}

void GameWindow::render(std::pair<Vector2f, Vector2f> line) {
	Vertex l[2];
	l[0] = Vertex(line.first);
	l[1] = Vertex(line.second);
	nativeRenderer->draw(l, 2, Lines);
}

void GameWindow::render(Collidable *c) {
	RectangleShape sh(Vector2f(c->cWidth*1.f, c->cHeight*1.f));
	sh.setFillColor(Color(0, 128, 0, 216));
	sh.setOutlineColor(Color::Green);
	sh.setOutlineThickness(1.0f);
	sh.setPosition((float)c->cX, (float)c->cY);
	nativeRenderer->draw(sh);
}

void GameWindow::render(SpriteRenderer *sr) {
	sr->render(nativeRenderer);
}

void GameWindow::render(CollisionGrid *cg) {
	cg->render(nativeRenderer);
}

void GameWindow::render(CollisionGrid *cg, short int gridPos[]) {
	cg->render(nativeRenderer, gridPos);
}

void GameWindow::render(CollisionGrid *cg, std::map<short int, unsigned short int> gridPos) {
	cg->render(nativeRenderer, gridPos);
}
