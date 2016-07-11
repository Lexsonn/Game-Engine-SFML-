#include "TileMap.h"

TileMap::~TileMap() { }
TileMap::TileMap() : m_tileset(nullptr) { }
TileMap::TileMap(const std::string &tileset, Vector2u tileSize, const int * tiles, 
				 unsigned int width, unsigned int height, ResourceManager *rm) { 
	// load the tileset texture
	m_tileset = rm->getTexture(tileset);
	if (m_tileset == nullptr)
		return;

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			// get the current tile number
			int tileNumber = tiles[i + j * width];

			// find its position in the tileset texture
			int tx = tileNumber / (m_tileset->getSize().x / tileSize.x);
			int ty = tileNumber % (m_tileset->getSize().x / tileSize.x);

			// Define a quad as the 4 points of a Vertex at the tile's position (x4)
			sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

			quad[0].position = sf::Vector2f(float(i * tileSize.x), float(j * tileSize.y));
			quad[1].position = sf::Vector2f(float((i + 1) * tileSize.x), float(j * tileSize.y));
			quad[2].position = sf::Vector2f(float((i + 1) * tileSize.x), float((j + 1) * tileSize.y));
			quad[3].position = sf::Vector2f(float(i * tileSize.x), float((j + 1) * tileSize.y));

			quad[0].texCoords = sf::Vector2f(float(tx * tileSize.x), float(ty * tileSize.y));
			quad[1].texCoords = sf::Vector2f(float((tx + 1) * tileSize.x), float(ty * tileSize.y));
			quad[2].texCoords = sf::Vector2f(float((tx + 1) * tileSize.x), float((ty + 1) * tileSize.y));
			quad[3].texCoords = sf::Vector2f(float(tx * tileSize.x), float((ty + 1) * tileSize.y));
		}
	}

	std::cout << "Loaded tilemap (" << width << "," << height << ").\n";
}

void TileMap::draw(RenderTarget &target, RenderStates states) const {
	if (m_tileset == nullptr)
		return;
	states.transform *= getTransform();
	states.texture = m_tileset;
	target.draw(m_vertices, states);
}