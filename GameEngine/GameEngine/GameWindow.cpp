#include "GameWindow.h"

using namespace sf;

GameWindow::~GameWindow(void) {}
GameWindow::GameWindow(RenderWindow* window) {
	nativeRenderer = window;
}

void GameWindow::start() {
	nativeRenderer->clear();
}

void GameWindow::end() {
	nativeRenderer->display();
}

sf::RenderWindow *GameWindow::getNative() {
	return nativeRenderer;
}

void GameWindow::renderDO(DrawableObject *d) {
	if (d->isVisible()) {
		d->render(nativeRenderer);
	}
}

void GameWindow::render(std::pair<Vector2f, Vector2f> line) {
	Vertex l[2];
	l[0] = Vertex(line.first);
	l[1] = Vertex(line.second);
	nativeRenderer->draw(l, 2, Lines);
}

void GameWindow::render(Collidable *c) {
	RectangleShape sh(Vector2f(c->cWidth * 1.f, c->cHeight * 1.f));
	sh.setFillColor(Color(0, 128, 0, 216));
	sh.setOutlineColor(Color::Green);
	sh.setOutlineThickness(1.0f);
	sh.setPosition((float)c->cX, (float)c->cY);
	nativeRenderer->draw(sh);
}

void GameWindow::render(ResourceManager *rm) {
	rm->render(nativeRenderer);
}

void GameWindow::render(CollisionGrid *cg) {
	cg->render(nativeRenderer);
}

void GameWindow::render(CollisionGrid *cg, short int gridPos[]) {
	cg->render(nativeRenderer, gridPos);
}