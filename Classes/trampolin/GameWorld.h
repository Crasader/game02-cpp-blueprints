#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "GameGlobals.h"

class GLESDebugDraw;
class GameObject;
class Clown;
class Collectible;
class BackgroundManager;

class GameWorld : public Layer, public b2ContactListener
{
public:
	GameWorld();
	virtual ~GameWorld();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* scene();
    
#ifdef ENABLE_DEBUG_DRAW
	virtual void draw();
#endif
	// update functions
	virtual void update(float dt);
	void UpdateCounters();
	
	// touch & tilt control events
	virtual void onAcceleration(Acceleration* acc, Event* event);
	bool onTouchBegan(const std::vector<Touch*>& touches, Event* evt);
	void onTouchMoving(const std::vector<Touch*>& touches, Event* evt);
	void onTouchEnded(const std::vector<Touch*>& touches, Event* evt);
    
	// b2ContactListener callback
	virtual void BeginContact(b2Contact* contact);

    // implement the "static node()" method manually
    CREATE_FUNC(GameWorld);

	// creation functions
	void CreateWorld();
	void DestroyWorld();
	void CreateGame();
	void CreateWall();
	void CreateClown();
	void CreateBasePlatform();
	void CreatePlatform();
	void CreateCollectibles();
	void CreateHUD();

	// add remove game element functions
	void AddPlatform(Point start, Point end);
	void RemovePlatform();
	void RemoveBasePlatform();
	void AddCollectible(bool special);
	void RemoveCollectible(Collectible* collectible);
	void AddScore(int value);

	// collision response functions
	void OnCollision(b2Vec2 contact_normal);
	void DoCollisionResponse(float dt);
	void DoBasePlatformCollision();
	void DoBasePlatformIdle(float dt);

	inline Clown* GetClown() { return clown_; }
	inline bool HasGameBegun() { return has_game_begun_; }

	// game life-cycle functions
	void ResumeGame();
	void GameOver();

	// game update functions
	void OnPauseClicked(Ref* sender);

private:
	b2World* world_;
#ifdef ENABLE_DEBUG_DRAW
    GLESDebugDraw* debug_draw_;
#endif
	SpriteBatchNode* sprite_batch_node_;
	BackgroundManager* background_manager_;

	Clown* clown_;
	b2Body* wall_;	
	b2Vec2 contact_normal_;
	GameObject* platform_;
	GameObject* base_platform_;

	__Array* pool_collectibles_;
	__Array* active_collectibles_;
	int num_collectibles_active_;

	bool has_game_begun_;
	Point touch_start_, touch_end_;
	Label* score_label_;
	int score_;

	EventListenerAcceleration *accListener;
	EventListenerTouchAllAtOnce *touchListener;

public:
	Node* game_object_layer_;
	bool is_popup_active_;
	int distance_travelled_;
};

#endif // __GameWorld_SCENE_H__
