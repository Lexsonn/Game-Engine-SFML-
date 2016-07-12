#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

using namespace sf;

#define SSX 12
#define SSY 12
#define TILESIZE_X 40
#define TILESIZE_Y 40

class TileMap : public Drawable, public Transformable {
public:
	~TileMap();
	TileMap();
	TileMap(const std::string &tileset, Vector2u tileSize, const int * tiles, Vector2u offset, ResourceManager *rm);
private:
	VertexArray m_vertices;
	Texture *m_tileset;

	virtual void draw(RenderTarget &target, RenderStates states) const;
};
#endif
