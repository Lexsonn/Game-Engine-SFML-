#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <SFML/Graphics.hpp>

using namespace sf;

#define GRID_WIDTH 160
#define GRID_HEIGHT 160

#define PI 3.1415f

// LINE CALCULATIONS ///////////////////////////////////////////////////////////////////////////

bool lineIntersectsRect(const float &x, const float &y, const float &w, const float &h, const std::pair<Vector2f, Vector2f> &l);
float findDistancePointToLine(const std::pair<Vector2f, Vector2f> &l, const Vector2f &p);
Vector2f findMidpointOfLine(const std::pair<Vector2f, Vector2f> &l);
std::pair<Vector2f, Vector2f> rotateLineAboutPoint(const std::pair<Vector2f, Vector2f> &line, const Vector2f &point, const float &angle);

// GRID CALCULATIONS ///////////////////////////////////////////////////////////////////////////

int getGrid(const unsigned int &x, const unsigned int &y);
Vector2i getCoords(const int &gridPos);

// RECTANGLE CALCULATIONS //////////////////////////////////////////////////////////////////////

//bool 

// VIEW CALCULATIONS ///////////////////////////////////////////////////////////////////////////

bool insideView(const FloatRect &bound, View * view);

#endif
