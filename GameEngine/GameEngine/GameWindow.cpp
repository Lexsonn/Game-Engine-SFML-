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

void GameWindow::render(std::pair<Vector2i, Vector2i> line) {
	Vertex l[2];
	l[0] = Vertex(Vector2f(line.first.x, line.first.y));
	l[1] = Vertex(Vector2f(line.second.x, line.second.y));
	nativeRenderer->draw(l, 2, Lines);
}

void GameWindow::render(Collidable *c) {
	RectangleShape sh(Vector2f(c->cWidth, c->cHeight));
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