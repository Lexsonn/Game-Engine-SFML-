#include "InputController.h"

InputController::~InputController() {}
InputController::InputController() {
	keyPressed.resize((int) Keyboard::KeyCount, false);
}

void InputController::checkKeyState() {
	//Temp keyPressed values, so multiple input objects can be properly handled
	std::vector<bool> _keyPressed = keyPressed;
	for (Controllable* controllable : controllableList) {
		for (int currentKey : controllable->getWatchlist()) {
			if (Keyboard::isKeyPressed((Keyboard::Key)currentKey) && !keyPressed.at(currentKey)) {
				controllable->_keyPress((Keyboard::Key)currentKey);
				_keyPressed[currentKey] = true;
			}
			else if (!Keyboard::isKeyPressed((Keyboard::Key)currentKey) && keyPressed.at(currentKey)) {
				controllable->_keyRelease((Keyboard::Key)currentKey);
				_keyPressed[currentKey] = false;
			}
			if (Keyboard::isKeyPressed((Keyboard::Key)currentKey)) {
				controllable->_keyHeld((Keyboard::Key)currentKey);
			}
		}
	}
	keyPressed = _keyPressed;
}

void InputController::addControllable(Controllable* controllable) {
	controllableList.push_back(controllable);
}
