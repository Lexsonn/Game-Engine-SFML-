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

ResourceManager::~ResourceManager() { 
	for (auto tex : textureList) {
		delete tex.second;
	}
	textureList.clear();
	zOrderedSpriteList.clear();
}

ResourceManager::ResourceManager() { 
	init(); 
}

void ResourceManager::setView(View *view) {
	this->view = view;
}

////////////////////////////////////////////////////////////////////////////////////////
// TEXTURE MANAGEMENT //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

texType ResourceManager::getTextureType(std::string texPath) {
	if (texPath == "playerIdle.png") { return playerIdle; }
	if (texPath == "playerWalk.png") { return playerWalk; }
	if (texPath == "playerRun.png") { return playerRun; }
	if (texPath == "playerABS.png") { return playerABS; }
	if (texPath == "playerAtt1.png") { return playerAttack1; }
	if (texPath == "playerAtt2.png") { return playerAttack2; }
	if (texPath == "playerAttRec.png") { return playerAttRec; }
	return UNKNOWN_t;
}

Texture *ResourceManager::getTexture(std::string texPath) {
	std::string fullpath = std::string(TEXTURE_PATH) + texPath;
	std::cout << "LOADING " << fullpath << " ... ";
	texType type = getTextureType(texPath);
	if (type == UNKNOWN_t) {
		std::cout << "No such texture defined.\n";
		return nullptr;
	}

	std::map<texType, Texture*>::iterator it = textureList.find(type);
	if (it == textureList.end()) {
		std::cout << "Texture not found.\n";
		return nullptr;
	}

	std::cout << "Texture successfully loaded.\n";
	return textureList[type];
}

bool ResourceManager::addTexture(std::string texPath) {
	std::string fullpath = std::string(TEXTURE_PATH) + texPath;
	texType type = getTextureType(texPath);
	if (type == UNKNOWN_t) {
		std::cout << "No texture " << fullpath << " defined.\n";
		return false;
	}
	
	Texture *tx = new Texture();
	if (!tx->loadFromFile(fullpath)) { // Load new texture from path
		std::cout << "No texture " << fullpath << " found!\n";
		delete tx;
		return false;
	}

	if (textureList.insert(std::pair<texType, Texture*>(type, tx)).second == false) {
		std::cout << "Texture " << fullpath << " is already loaded in memory.\n";
		delete tx;
		return false;
	}

	std::cout << "Sucessfully added " << fullpath << " to memory.\n";
	return true;
}

bool ResourceManager::deleteTexture(std::string texPath) {
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

sfxType ResourceManager::getSoundType(std::string sfxPath) {
	return UNKNOWN_s;
}

Sound ResourceManager::getSound(std::string sfxPath) { 
	std::string fullpath = std::string(SOUND_PATH) + sfxPath;
	std::cout << "LOADING " << fullpath << " ... ";
	sfxType type = getSoundType(sfxPath);
	if (type == UNKNOWN_s) {
		std::cout << "No sound " << fullpath << " defined.\n";
		return Sound();
	}

	std::map<sfxType, SoundBuffer>::iterator it = soundList.find(type);
	if (it == soundList.end()) {
		std::cout << "Sound not found.\n";
		return Sound();
	}

	std::cout << "Sound successfully loaded.\n";
	return Sound(soundList[type]);
}

bool ResourceManager::addSound(std::string sfxPath) {
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

bool ResourceManager::deleteSound(std::string sfxPath) {
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

musicType ResourceManager::getMusicType(std::string musicPath) {
	return UNKNOWN_m;
}

Music *ResourceManager::getMusic(std::string musicPath) { 
	std::string fullpath = std::string(MUSIC_PATH) + musicPath;
	std::cout << "LOADING " << fullpath << " ... ";
	musicType type = getMusicType(musicPath);
	if (type == UNKNOWN_m) {
		std::cout << "No music " << fullpath << " defined.\n";
		return nullptr;
	}

	std::map<musicType, Music *>::iterator it = songList.find(type);
	if (it == songList.end()) {
		std::cout << "Music not found.\n";
		return nullptr;
	}

	std::cout << "Music successfully loaded.\n";
	return songList[type];
}

bool ResourceManager::addMusic(std::string musicPath) {
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

bool ResourceManager::deleteMusic(std::string musicPath) {
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

////////////////////////////////////////////////////////////////////////////////////////
// SPRITE DRAW PRIORITY MANAGEMENT /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

/*
 *	Adds a sprite to the z-ordered sprite list (typically ordered by y alone, but for "flying" objects
 *	a z value can be added to the y to move it forward) and returns true if the sprite is inside the view. 
 *	If the sprite is outside the current view, the sprite is not inserted, and the function returns false.
 */
bool ResourceManager::addSprite(int z, Sprite &spr) {
	if (isInsideView(spr)) {
		zOrderedSpriteList.insert(std::pair<int, Sprite&>(z, spr));
		return true;
	}
	return false;
}

void ResourceManager::clearList() {
	zOrderedSpriteList.clear();
}

void ResourceManager::render(RenderWindow *window) {
	std::multimap<int, Sprite&>::iterator it = zOrderedSpriteList.begin();
	while (it != zOrderedSpriteList.end()) 
		window->draw(it++->second);
}

bool ResourceManager::isInsideView(Sprite &spr) {
	FloatRect bound = spr.getGlobalBounds();
	float vcX, vcY, vsX, vsY;

	vcX = view->getCenter().x;
	vcY = view->getCenter().y;
	vsX = view->getSize().x / 2;
	vsY = view->getSize().y / 2;

	return !((bound.left > vcX + vsX) || (bound.left + bound.width < vcX - vsX) || (bound.top > vcY + vsY) || (bound.top + bound.height < vcY - vsY));
}