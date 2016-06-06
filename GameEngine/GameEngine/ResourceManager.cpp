#include "ResourceManager.h"

using namespace sf;

// Initialize the texture list with player sprites.
void ResourceManager::init() {
	addTexture("playerIdle.png");
	addTexture("playerWalk.png");
	addTexture("playerRun.png");
	addTexture("playerABS.png");
	addTexture("playerAtt1.png");
	addTexture("playerAttRec.png");
}

ResourceManager::~ResourceManager() { }
ResourceManager::ResourceManager() { 
	init(); 
}

// Master list for relating texture paths with their texList value
texList ResourceManager::getTextureType(std::string texPath) {
	if (texPath == "playerIdle.png") { return playerIdle; }
	if (texPath == "playerWalk.png") { return playerWalk; }
	if (texPath == "playerRun.png") { return playerRun; }
	if (texPath == "playerABS.png") { return playerABS; }
	if (texPath == "playerAtt1.png") { return playerAttack1; }
	if (texPath == "playerAtt2.png") { return playerAttack2; }
	if (texPath == "playerAttRec.png") { return playerAttRec; }
	return UNKNOWN_t;
}

Texture * ResourceManager::getTexture(std::string texPath) {
	std::string fullpath = std::string(TEXTURE_PATH) + texPath;
	std::cout << "LOADING " << fullpath << " ... ";
	texList type = getTextureType(texPath);
	std::cout << type << " ";
	if (type == UNKNOWN_t) {
		std::cout << "\nNo such texture " << fullpath << " defined.\n";
		return nullptr;
	}
	std::cout << "checking... ";
	std::map<texList, Texture*>::iterator it = textureList.find(type);
	if (it == textureList.end()) {
		std::cout << "Texture not found.\n";
		return nullptr;
	}
	std::cout << "returning...\n";
	return textureList[type];
}

bool ResourceManager::addTexture(std::string texPath) {
	std::string fullpath = std::string(TEXTURE_PATH) + texPath;
	texList type = getTextureType(texPath);
	if (type == UNKNOWN_t) { // No textureType defined for this current path
		std::cout << "No such texture " << fullpath << " defined.\n";
		return false;
	}

	Texture *tx = new Texture();
	if (!tx->loadFromFile(fullpath)) { // Load new texture from path
		std::cout << "No image " << fullpath << " found!\n";
		delete tx;
		return false;
	}

	if (textureList.insert(std::pair<texList, Texture*>(type, tx)).second == false) { // Texture is already in use
		std::cout << "Texture " << fullpath << " is already loaded in memory.\n";
		delete tx;
		return false;
	}

	std::cout << "Sucessfully added " << fullpath << " to memory.\n";
	return true;
}

bool ResourceManager::deleteTexture(std::string texPath) {
	texList type = getTextureType(texPath);
	if (type == UNKNOWN_t)
		return false;

	std::map<texList, Texture*>::iterator it;
	it = textureList.find(type);
	// TODO: DELETE THE TEXTURE MORON. DONT JUST STAND THERE AFTER FINDING IT IN THE GODDAMN MAP

	return false;
}

Sound * ResourceManager::loadSound(std::string sfxPath) { return nullptr; }
Sound * ResourceManager::loadMusic(std::string musicPath) { return nullptr; }

bool ResourceManager::addSprite(int y, Sprite &spr) {
	zOrderedSpriteList.insert(std::pair<int, Sprite&>(y, spr));
	return true;
}

void ResourceManager::clearList() {
	zOrderedSpriteList.clear();
}

void ResourceManager::render(RenderWindow *window) {
	std::multimap<int, Sprite&>::iterator it = zOrderedSpriteList.begin();
	while (it != zOrderedSpriteList.end()) {
		window->draw(it->second);
		it++;
	}
}