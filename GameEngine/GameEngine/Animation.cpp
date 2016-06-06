#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"

using namespace sf;

Animation::Animation() {
	animationSpeed = -1.f;
	currentFrame = 0.f;
}
/*
 *	Create sprite animation using file (1 line per animation)
 */
Animation::Animation(Texture *t, float x, float y, int w, int h, int frameCount, float speed, bool r) {
	currentFrame = 0;
	animationSpeed = speed;
	repeat = r;

	for (int i = 0; i<frameCount; i++)
		frames.push_back(IntRect(x + i*w, y, w, h));

	sprite.setTexture(*t);
	sprite.setOrigin(w / 2, h / 2);
	sprite.setTextureRect(frames[0]);

	frameSize = frames.size();
}

void Animation::setRotation(int angle) {
	sprite.setRotation(angle);
}

void Animation::rotate(int angle) {
	sprite.rotate(angle);
}

void Animation::setScale(float xScale, float yScale) {
	sprite.setScale(Vector2f(xScale, yScale));
}

void Animation::setOrigin(float x, float y) {
	sprite.setOrigin(x, y);
}

void Animation::moveOrigin(float x, float y) {
	Vector2f pos = sprite.getOrigin();
	sprite.setOrigin(pos.x + x, pos.y + y);
}

void Animation::setColor(Color c) {
	sprite.setColor(c);
}

void Animation::update(float x, float y) {
	sprite.setPosition(x, y);
}

void Animation::beginUpdate() {
	currentFrame += animationSpeed;
}

void Animation::endUpdate() {
	if (currentFrame >= frameSize && repeat) currentFrame -= frameSize;
	if (frameSize > 0 && currentFrame < frames.size()) sprite.setTextureRect(frames[int(currentFrame)]);
}

void Animation::restart() {
	currentFrame = 0;
}

bool Animation::isLastFrame() {
	return (currentFrame + animationSpeed > frames.size());
}