#ifndef _DRAGONDASH_MAINMENU_SCENE_H_
#define _DRAGONDASH_MAINMENU_SCENE_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Resources.h"
#include "dragondash\DragonDashDefinition.h"
#include "dragondash\FairyTaleManager.h"

USING_NS_CC;

class MainMenu : public cocos2d::Layer
{
	Size screenSize;
	SpriteBatchNode* spriteBatchNode;
	FairyTaleManager* fairytaleManager;

	public:
		static cocos2d::Scene* createScene();

		virtual bool init();

		// a selector callback
		void menuCloseCallback(cocos2d::Ref* pSender);

		// implement the "static create()" method manually
		CREATE_FUNC(MainMenu);

	private:
		void addDragonAnimation();
		void addDragon();
		void onPlayClicked(cocos2d::Ref* ref);
		void update(float dt);
};

#endif // _DRAGONDASH_MAINMENU_SCENE_H_