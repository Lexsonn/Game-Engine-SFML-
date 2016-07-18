#include "DrawableObjectManager.h"
#include "SpriteEffect.h"

#define _CHECK_SPRITE_EFFECT_DT if (dO->getDrawableType() == SpriteEffect::drawableType) { SpriteEffect *eff = dynamic_cast<SpriteEffect *>(dO); if (!eff->update()) { delete dO; it = drawableList.erase(it); draw = false; }}

std::vector<DrawableObject *> DrawableObjectManager::drawableList;

void DrawableObjectManager::addDrawableObject(DrawableObject* drawObj) {
	drawableList.push_back(drawObj);
}

/*
 *	Deletes all DrawableObjects from the DrawableObject list
 */
void DrawableObjectManager::clearDrawableList() {
	std::vector<DrawableObject *>::iterator it;
	for (it = drawableList.begin(); it < drawableList.end(); it++) 
		delete *it;
	
	drawableList.clear();
}


/*
 *	Iterate through the list of all drawable objects, deleting them if needed.
 *	If they aren't deleted, they are sent to the SpriteRenderer to check for rendering.
 */
void DrawableObjectManager::update() {
	if (!drawableList.empty()) {
		std::vector<DrawableObject *>::iterator it;
		for (it = drawableList.begin(); it < drawableList.end(); ) {
			DrawableObject *dO = *it;
			bool draw = true;
			_CHECK_SPRITE_EFFECT_DT;
			if (draw) { dO->addToRenderer(int(dO->y)); it++; }
		}
	}
}
