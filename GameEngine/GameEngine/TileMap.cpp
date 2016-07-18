#include "TileMap.h"

TileMap::~TileMap() { }
TileMap::TileMap() : m_tileset(nullptr) { }
TileMap::TileMap(const std::string &tileset, Vector2u tileSize, const int * tiles, Vector2u offset, ResourceManager *rm) { 
	m_tileset = rm->getTexture(tileset);
	if (m_tileset == nullptr)
		return;

	Vector2u min = Vector2u(offset.x * SSX, offset.y * SSY);
	Vector2u max = Vector2u(std::min(offset.x * SSX + SSX, (unsigned int)tiles[0]), std::min(offset.y * SSY + SSY, (unsigned int)tiles[1]));

	this->setPosition(float(min.x * TILESIZE_X), float(min.y * TILESIZE_Y));

	m_vertices.setPrimitiveType(Quads);
	m_vertices.resize((max.x - min.x) * (max.y - min.y) * 4);

	for (unsigned int i = 0; i < max.x - min.x; i++) {
		for (unsigned int j = 0; j < max.y - min.y; j++) {
			// The tile number corresponding to the current tile
			int tileNumber = tiles[(i + min.x) + (j + min.y) * tiles[0] + 2];
			// x and y position of the current tile's texture
			int tx = tileNumber / (m_tileset->getSize().x / tileSize.x);
			int ty = tileNumber % (m_tileset->getSize().x / tileSize.x);

			// Specify the 4 corners of the current tile.
			sf::Vertex *quad = &m_vertices[((i) + (j) * (max.x - min.x)) * 4];
			// Specify the global position of the tile in the world.
			quad[0].position = Vector2f(float(i * tileSize.x), float(j * tileSize.y));
			quad[1].position = Vector2f(float((i + 1) * tileSize.x), float(j * tileSize.y));
			quad[2].position = Vector2f(float((i + 1) * tileSize.x), float((j + 1) * tileSize.y));
			quad[3].position = Vector2f(float(i * tileSize.x), float((j + 1) * tileSize.y));
			// Specify the texture position of the current tile in the tileset
			quad[0].texCoords = Vector2f(float(tx * tileSize.x), float(ty * tileSize.y));
			quad[1].texCoords = Vector2f(float((tx + 1) * tileSize.x), float(ty * tileSize.y));
			quad[2].texCoords = Vector2f(float((tx + 1) * tileSize.x), float((ty + 1) * tileSize.y));
			quad[3].texCoords = Vector2f(float(tx * tileSize.x), float((ty + 1) * tileSize.y));
		}
	}
	std::cout << "Loaded tilemap at (" << offset.x << "," << offset.y << "), of size (" << (max.x - min.x) << "," << (max.y - min.y) << ").\n";
}

void TileMap::draw(RenderTarget &target, RenderStates states) const {
	if (m_tileset == nullptr)
		return;
	states.transform *= getTransform();
	states.texture = m_tileset;
	target.draw(m_vertices, states);
}
