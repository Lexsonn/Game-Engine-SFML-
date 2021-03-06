#include "ResourceManager.h"
#include <iostream>

using namespace sf;

// Initialize the texture list with player sprites.
void ResourceManager::init() {
	addTexture("Tilesets/tileset1.png");
	addTexture("playerIdle.png");
	addTexture("playerWalk.png");
	addTexture("playerRun.png");
	addTexture("playerABS.png");
	addTexture("playerAtt1.png");
	addTexture("playerAttRec.png");
	addTexture("playerDeath.png");
	addTexture("playerAttackAnim1.png");
}

ResourceManager::~ResourceManager() { 
	for (auto tex : textureList) {
		delete tex.second;
	}
	textureList.clear();
}

ResourceManager::ResourceManager() { 
	init(); 
}

////////////////////////////////////////////////////////////////////////////////////////
// TEXTURE MANAGEMENT //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

texType ResourceManager::getTextureType(const std::string &texPath) {
	if (texPath == "Tilesets/tileset1.png") { return tileset1; }
	if (texPath == "playerIdle.png") { return playerIdle; }
	if (texPath == "playerWalk.png") { return playerWalk; }
	if (texPath == "playerRun.png") { return playerRun; }
	if (texPath == "playerABS.png") { return playerABS; }
	if (texPath == "playerAtt1.png") { return playerAttack1; }
	if (texPath == "playerAtt2.png") { return playerAttack2; }
	if (texPath == "playerAttRec.png") { return playerAttRec; }
	if (texPath == "playerDeath.png") { return playerDeath; }
	if (texPath == "playerAttackAnim1.png") { return playerAttackAnim1; }
	return UNKNOWN_t;
}

Texture *ResourceManager::getTexture(const std::string &texPath) {
	std::string fullpath = std::string(TEXTURE_PATH) + texPath;
	texType type = getTextureType(texPath);

	if (type == UNKNOWN_t)
		return nullptr;

	std::map<texType, Texture*>::iterator it = textureList.find(type);
	if (it == textureList.end()) 
		return nullptr;

	return textureList[type];
}

bool ResourceManager::addTexture(const std::string &texPath) {
	std::string fullpath = std::string(TEXTURE_PATH) + texPath;
	std::cout << "LOADING " << fullpath << " ... ";
	texType type = getTextureType(texPath);
	if (type == UNKNOWN_t) {
		std::cout << "No texture defined.\n";
		return false;
	}
	
	Texture *tx = new Texture();
	if (!tx->loadFromFile(fullpath)) { // Load new texture from path
		std::cout << "No texture found!\n";
		delete tx;
		return false;
	}

	if (textureList.insert(std::pair<texType, Texture*>(type, tx)).second == false) {
		std::cout << "Texture is already loaded in memory.\n";
		delete tx;
		return false;
	}

	std::cout << "Sucess!\n";
	return true;
}

bool ResourceManager::deleteTexture(const std::string &texPath) {
	std::string fullpath = std::string(TEXTURE_PATH) + texPath;
	std::cout << "DELETING " << fullpath << "... ";
	texType type = getTextureType(texPath);
	if (type == UNKNOWN_t) {
		std::cout << "Texture does not exist.\n";
		return false;
	}

	std::map<texType, Texture*>::iterator it;
	it = textureList.find(type);

	if (it == textureList.end()) {
		std::cout << "Texture not found. Perhaps it was already deleted?\n";
		return false;
	}
	
	delete it->second;
	textureList.erase(it);

	std::cout << "Texture succesfully deleted\n";
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
// SOUND MANAGEMENT ////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

sfxType ResourceManager::getSoundType(const std::string &sfxPath) {
	return UNKNOWN_s;
}

Sound ResourceManager::getSound(const std::string &sfxPath) { 
	std::string fullpath = std::string(SOUND_PATH) + sfxPath;
	sfxType type = getSoundType(sfxPath);
	if (type == UNKNOWN_s) 
		return Sound();

	std::map<sfxType, SoundBuffer>::iterator it = soundList.find(type);
	if (it == soundList.end())
		return Sound();

	return Sound(soundList[type]);
}

bool ResourceManager::addSound(const std::string &sfxPath) {
	std::string fullpath = std::string(SOUND_PATH) + sfxPath;
	sfxType type = getSoundType(sfxPath);
	if (type == UNKNOWN_s) {
		std::cout << "No sound " << fullpath << " defined.\n";
		return false;
	}

	SoundBuffer sfx = SoundBuffer();
	if (!sfx.loadFromFile(fullpath)) { // Load new sound from path
		std::cout << "No sound " << fullpath << " found!\n";
		return false;
	}

	if (soundList.insert(std::pair<sfxType, SoundBuffer>(type, sfx)).second == false) {
		std::cout << "Sound " << fullpath << " is already loaded in memory.\n";
		return false;
	}

	std::cout << "Sucessfully added " << fullpath << " to memory.\n";
	return true;
}

bool ResourceManager::deleteSound(const std::string &sfxPath) {
	std::string fullpath = std::string(SOUND_PATH) + sfxPath;
	std::cout << "DELETING " << fullpath << "... ";
	sfxType type = getSoundType(sfxPath);
	if (type == UNKNOWN_s) {
		std::cout << "Sound does not exist.\n";
		return false;
	}

	std::map<sfxType, SoundBuffer>::iterator it;
	it = soundList.find(type);

	if (it == soundList.end()) {
		std::cout << "Sound not found. Perhaps it was already deleted?\n";
		return false;
	}

	soundList.erase(it);

	std::cout << "Sound succesfully deleted\n";
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
// MUSIC MANAGEMENT ////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

musicType ResourceManager::getMusicType(const std::string &musicPath) {
	return UNKNOWN_m;
}

Music *ResourceManager::getMusic(const std::string &musicPath) {
	std::string fullpath = std::string(MUSIC_PATH) + musicPath;
	musicType type = getMusicType(musicPath);
	if (type == UNKNOWN_m)
		return nullptr;

	std::map<musicType, Music *>::iterator it = songList.find(type);
	if (it == songList.end())
		return nullptr;

	return songList[type];
}

bool ResourceManager::addMusic(const std::string &musicPath) {
	std::string fullpath = std::string(MUSIC_PATH) + musicPath;
	musicType type = getMusicType(musicPath);
	if (type == UNKNOWN_m) {
		std::cout << "No music " << fullpath << " defined.\n";
		return false;
	}

	Music *music = new Music();
	if (!music->openFromFile(fullpath)) { // Load new music from path
		std::cout << "No music " << fullpath << " found!\n";
		return false;
	}

	if (songList.insert(std::pair<musicType, Music *>(type, music)).second == false) {
		std::cout << "Music " << fullpath << " is already loaded in memory.\n";
		return false;
	}

	std::cout << "Sucessfully added " << fullpath << " to memory.\n";
	return true;
}

bool ResourceManager::deleteMusic(const std::string &musicPath) {
	std::string fullpath = std::string(MUSIC_PATH) + musicPath;
	std::cout << "DELETING " << fullpath << "... ";
	musicType type = getMusicType(musicPath);
	if (type == UNKNOWN_m) {
		std::cout << "Music does not exist.\n";
		return false;
	}

	std::map<musicType, Music *>::iterator it;
	it = songList.find(type);

	if (it == songList.end()) {
		std::cout << "Music not found. Perhaps it was already deleted?\n";
		return false;
	}

	delete it->second;
	songList.erase(it);

	std::cout << "Music succesfully deleted\n";
	return true;
}
 