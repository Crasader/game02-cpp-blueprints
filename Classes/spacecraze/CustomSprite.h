#ifndef _SPACECRAZE_CUSTOM_SPRITE_H_
#define _SPACECRAZE_CUSTOM_SPRITE_H_

#include "spacecraze\GameGlobals.h"

namespace spacecraze
{
	class CustomSprite : public CCSprite
	{
	public:
		CustomSprite() : size_(Size::ZERO) {}
		virtual ~CustomSprite();

		// returns and autorelease CustomSprite
		static CustomSprite* createWithSpriteFrameName(const char* frame_name);

		// override CCSprite's boundingBox method
		virtual CCRect boundingBox();

		// add a customized CCSize used for the boundingBox
		CC_SYNTHESIZE(CCSize, size_, Size);
	};
}

#endif // _SPACECRAZE_CUSTOM_SPRITE_H_
