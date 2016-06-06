#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

using namespace sf;

/*
 *	A single sprite animation (such as walk south, attack north, etc.)
 */
class Animation {
public:
	Sprite sprite;

	Animation();
	Animation(Texture *t, float x, float y, int w, int h, int frameCount, float speed, bool r);
	void setRotation(int angle);
	void rotate(int angle);
	void setScale(float xScale, float yScale);
	void setColor(Color color);
	void setOrigin(float x, float y);
	void moveOrigin(float x, float y);
	void update(float x, float y);
	void beginUpdate();
	void endUpdate();
	void restart();
	bool isLastFrame();
private:
	bool repeat;
	float currentFrame;
	float animationSpeed;
	int frameSize;
	std::vector<IntRect> frames;
};
#endif