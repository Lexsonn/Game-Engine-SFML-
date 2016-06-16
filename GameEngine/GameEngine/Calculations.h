#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <SFML/System.hpp>

using namespace sf;

extern int WWIDTH;
extern int WHEIGHT;

bool lineIntersectsRect(float x, float y, float w, float h, std::pair<Vector2f, Vector2f> l);
float findDistance(Vector2f l1, Vector2f l2, Vector2f point);

#endif