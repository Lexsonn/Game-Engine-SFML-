#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <SFML/System.hpp>

using namespace sf;

#define GRID_WIDTH 160
#define GRID_HEIGHT 160

// LINE CALCULATIONS ///////////////////////////////////////////////////////////////////////////

bool lineIntersectsRect(float x, float y, float w, float h, std::pair<Vector2f, Vector2f> l);
float findDistancePointToLine(Vector2f l1, Vector2f l2, Vector2f p);
Vector2f findMidpointOfLine(std::pair<Vector2f, Vector2f> l);

// GRID CALCULATIONS ///////////////////////////////////////////////////////////////////////////

int getGrid(unsigned int x, unsigned int y);
Vector2i getCoords(int gridPos);

#endif