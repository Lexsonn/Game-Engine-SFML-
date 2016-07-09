#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "Controllable.h"

using namespace sf;

class InputController {
public:
	InputController();
	~InputController();

	void checkKeyState();
	void addControllable(Controllable* controllable);

private:
	std::vector<bool> keyPressed;
	std::vector<Controllable*> controllableList;
};
#endif
