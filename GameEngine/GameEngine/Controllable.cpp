#include "Controllable.h"

Controllable::~Controllable() {}
Controllable::Controllable() {
	keyWatchlist = std::vector<int>();
}

std::vector<int> Controllable::getWatchlist() {
	return keyWatchlist;
}

bool Controllable::isKeyPressed(sf::Keyboard::Key key) {
	return sf::Keyboard::isKeyPressed(key);
}

void Controllable::_keyHeld(sf::Keyboard::Key key) {
	keyHeld(key);
}

void Controllable::_keyPress(sf::Keyboard::Key key) {
	keyPress(key);
}

void Controllable::_keyRelease(sf::Keyboard::Key key) {
	keyRelease(key);
}

void Controllable::keyHeld(sf::Keyboard::Key key) {}
void Controllable::keyPress(sf::Keyboard::Key key) {}
void Controllable::keyRelease(sf::Keyboard::Key key) {}
