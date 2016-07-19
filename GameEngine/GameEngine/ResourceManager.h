#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "MusicList.h"
#include "TexList.h"
#include "SFXList.h"
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

	texType getTextureType(const std::string &texPath);
	Texture *getTexture(const std::string &texPath);
	bool addTexture(const std::string &texPath);
	bool deleteTexture(const std::string &texPath);

	sfxType getSoundType(const std::string &sfxPath);
	Sound getSound(const std::string &sfxPath);
	bool addSound(const std::string &sfxPath);
	bool deleteSound(const std::string &sfxPath);

	musicType getMusicType(const std::string &musicPath);
	Music *getMusic(const std::string &musicPath);
	bool addMusic(const std::string &musicPath);
	bool deleteMusic(const std::string &musicPath);
private:
	std::map<texType, Texture *> textureList;
	std::map<sfxType, SoundBuffer> soundList;
	std::map<musicType, Music *> songList;

	void init();
};
#endif
