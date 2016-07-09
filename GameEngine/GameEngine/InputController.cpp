#include "InputController.h"

InputController::~InputController() {}
InputController::InputController() {
	std::fill_n(keyPressed, (int)Keyboard::KeyCount, false);
}

void InputController::checkKeyState() {
	for (Controllable* controllable : controllableList) {
		for (int currentKey : controllable->getWatchlist()) {
			if (Keyboard::isKeyPressed((Keyboard::Key)currentKey) && !keyPressed[currentKey]) {
				controllable->_keyPress((Keyboard::Key)currentKey);
				keyPressed[currentKey] = true;
			}
			else if (!Keyboard::isKeyPressed((Keyboard::Key)currentKey) && keyPressed[currentKey]) {
				controllable->_keyRelease((Keyboard::Key)currentKey);
				keyPressed[currentKey] = false;
			}
			if (Keyboard::isKeyPressed((Keyboard::Key)currentKey)) {
				controllable->_keyHeld((Keyboard::Key)currentKey);
			}
		}
	}
}

void InputController::addControllable(Controllable* controllable) {
	controllableList.push_back(controllable);
}
