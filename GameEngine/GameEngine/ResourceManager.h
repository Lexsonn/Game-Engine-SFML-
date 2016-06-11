#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "MusicList.h"
#include "TexList.h"
#include "SFXList.h"
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

	void setView(View *view);

	texType getTextureType(std::string texPath);
	Texture *getTexture(std::string texPath);
	bool addTexture(std::string texPath);
	bool deleteTexture(std::string texPath);

	sfxType getSoundType(std::string sfxPath);
	Sound getSound(std::string sfxPath);
	bool addSound(std::string sfxPath);
	bool deleteSound(std::string sfxPath);

	musicType getMusicType(std::string musicPath);
	Music *getMusic(std::string musicPath);
	bool addMusic(std::string musicPath);
	bool deleteMusic(std::string musicPath);

	bool addSprite(int z, Sprite &spr);
	void clearList();

	void render(RenderWindow *window);
private:
	void init();
	View *view;

	std::map<texType, Texture *> textureList;
	std::map<sfxType, SoundBuffer> soundList;
	std::map<musicType, Music *> songList;

	std::multimap<int, Sprite &> zOrderedSpriteList;

	bool isInsideView(Sprite &spr);
};
#endif