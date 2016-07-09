#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Controllable  {
public:
	Controllable();
	~Controllable();

	bool isKeyPressed(Keyboard::Key key);
	std::vector<int> getWatchlist();
	void _keyHeld(Keyboard::Key key);
	void _keyPress(Keyboard::Key key);
	void _keyRelease(Keyboard::Key key);

	virtual void keyHeld(Keyboard::Key key);
	virtual void keyPress(Keyboard::Key key);
	virtual void keyRelease(Keyboard::Key key);
protected:
	std::vector<int> keyWatchlist;
};
#endif
