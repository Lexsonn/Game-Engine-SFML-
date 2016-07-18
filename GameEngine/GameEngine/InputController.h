#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "Controllable.h"

using namespace sf;

struct InputController {
public:
	void update();
	void addControllable(Controllable *controllable);
	void clearControllables();
private:
	static std::vector<bool> keyPressed;
	static std::vector<Controllable *> controllableList;
};
#endif
