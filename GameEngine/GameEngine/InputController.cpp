#include "InputController.h"

// Keypress values representing whether the current key is being held
std::vector<bool> InputController::keyPressed((int)Keyboard::KeyCount);
// List of controllables
std::vector<Controllable *> InputController::controllableList;

/*
 *	Update keyPress information for all controllables.
 */
void InputController::update() {
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

/*
 *	Add a Controllable to the controllable list
 */
void InputController::addControllable(Controllable* controllable) {
	controllableList.push_back(controllable);
}

/*
 *	Clear the list of controllables
 */
void InputController::clearControllables() {
	controllableList.clear();
}
