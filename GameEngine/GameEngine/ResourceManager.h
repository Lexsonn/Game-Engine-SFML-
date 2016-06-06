#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "TexList.h"
#include <iostream>
#include <vector>
#include <map>

using namespace sf;

#define TEXTURE_PATH "Resources/Images/"
#define SOUND_PATH "Resources/Sounds/"
#define MUSIC_PATH "Resources/Music/"

class ResourceManager {
public:
	~ResourceManager();
	ResourceManager();

	texList getTextureType(std::string texPath);
	Texture *getTexture(std::string texPath);
	bool addTexture(std::string texPath);
	bool deleteTexture(std::string texPath);

	Sound *loadSound(std::string sfxPath);
	Sound *loadMusic(std::string musicPath);

	bool addSprite(int y, Sprite &spr);
	void clearList();

	void render(RenderWindow *window);
private:
	void init();

	std::map<texList, Texture *> textureList;
	//std::map<sfxList, Sound*> soundList;
	//std::map<musicList, Sound*> musicList;
	std::multimap<int, Sprite &> zOrderedSpriteList;
};
#endif