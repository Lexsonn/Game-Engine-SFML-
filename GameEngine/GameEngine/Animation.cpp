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

	if (t == nullptr) {
		frameSize = 0;
		return;
	}

	for (int i = 0; i < frameCount; i++)
		frames.push_back(IntRect(int(x) + i*w, int(y), w, h));

	sprite.setTexture(*t);
	sprite.setOrigin(float(w / 2), float(h / 2));
	sprite.setTextureRect(frames[0]);

	frameSize = (int)frames.size();
}

void Animation::setRotation(float angle) {
	sprite.setRotation(angle);
}

void Animation::rotate(float angle) {
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

void Animation::updatePosition(float x, float y) {
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
