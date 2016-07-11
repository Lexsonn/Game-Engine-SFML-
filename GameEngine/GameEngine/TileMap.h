#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

using namespace sf;

class TileMap : public Drawable, public Transformable {
public:
	~TileMap();
	TileMap();
	TileMap(const std::string &tileset, Vector2u tileSize, const int * tiles, 
			unsigned int width, unsigned int height, ResourceManager *rm);
private:
	VertexArray m_vertices;
	Texture *m_tileset;

	virtual void draw(RenderTarget &target, RenderStates states) const;
};

#endif