#include "spacecraze\Enemy.h"
#include "spacecraze\GameWorld.h"

using namespace spacecraze;

Enemy::Enemy(GameWorld* game_world, const char* frame_name)
{
	game_world_ = game_world;
	score_ = 0;

	// different enemies have different properties
	if(strstr(frame_name, "1"))
	{
		bullet_name_ = "sfbullet3";
		particle_color_ = Color4F(0.5255, 0.9373, 0, 1);
		bullet_duration_ = BULLET_MOVE_DURATION * 3;
		size_ = Size(50, 35);
	}
	else if(strstr(frame_name, "2"))
	{
		bullet_name_ = "sfbullet1";
		particle_color_ = Color4F(0.9569, 0.2471, 0.3373, 1);
		bullet_duration_ = BULLET_MOVE_DURATION * 1.5;
		size_ = Size(50, 50);
	}
	else if(strstr(frame_name, "3"))
	{
		bullet_name_ = "sfbullet2";
		particle_color_ = Color4F(0.9451, 0.8157, 0, 1);
		bullet_duration_ = BULLET_MOVE_DURATION * 0.8;
		size_ = Size(55, 55);
	}
}

Enemy::~Enemy()
{}

Enemy* Enemy::createWithSpriteFrameName(GameWorld* game_world, const char* frame_name)
{
	auto enemy = new Enemy(game_world, frame_name);
	if(enemy && enemy->initWithSpriteFrameName(frame_name))
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

int Enemy::Die()
{
	// do this so that the movement action stops
	stopAllActions();

	// play an animation when this enemy is hit by player bullet
	auto blast = ScaleTo::create(0.25f, 0.0f);
	auto remove = RemoveSelf::create(true);
	runAction(Sequence::createWithTwoActions(blast, remove));

	// play a particle effect
	// modify the start & end color to suit the enemy
	auto explosion = ParticleSystemQuad::create(RESOURCES_SPACECRAZE_SHEET_EXPLOTION);
	explosion->setStartColor(particle_color_);
	explosion->setEndColor(particle_color_);
	explosion->setAutoRemoveOnFinish(true);
	// explosion->setPosition(m_obPosition);
	explosion->setPosition(getPosition());
	game_world_->addChild(explosion);

	SOUND_ENGINE->playEffect(RESOURCES_SPACECRAZE_SOUND_BLAST_ENEMY);

	// return score_ so it can be credited to the player
	return score_;
}
