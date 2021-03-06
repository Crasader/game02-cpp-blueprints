#include "PowerUp.h"
#include "GameWorld.h"

bool PowerUp::init(GameWorld* instance)
{
	if(!DrawNode::init())
		return false;
	
	game_world_ = instance;
	// calculate how much time the power-up should wait on screen before activation
	time_left_ = MAX_POWERUP_WAIT_ON_SCREEN / 2 + CCRANDOM_0_1() * MAX_POWERUP_WAIT_ON_SCREEN / 2;
	// calculate speed
	speed_ = Point(CCRANDOM_MINUS1_1() * 2, CCRANDOM_MINUS1_1() * 2);

	// draw the brown coloured ring
	drawDot(Point::ZERO, POWERUP_ICON_OUTER_RADIUS, Color4F(0.73725f, 0.5451f, 0, 1));
	drawDot(Point::ZERO, POWERUP_ICON_OUTER_RADIUS - 3, Color4F(0, 0, 0, 1));
	setScale(0.0f);

	return true;
}

void PowerUp::Update()
{
	// bounce within the boundary
	if (!RECT_CONTAINS_CIRCLE(game_world_->boundary_rect_, getPosition(), POWERUP_ICON_OUTER_RADIUS))
	{
		// bounce off the left & right edge
		if( (getPosition().x - POWERUP_ICON_OUTER_RADIUS) < game_world_->boundary_rect_.origin.x ||
			(getPosition().x + POWERUP_ICON_OUTER_RADIUS) > (game_world_->boundary_rect_.origin.x + game_world_->boundary_rect_.size.width) )
			speed_.x *= -1;
		// bounce off the top & bottom edge
		if( (getPosition().y + POWERUP_ICON_OUTER_RADIUS) > (game_world_->boundary_rect_.origin.y + game_world_->boundary_rect_.size.height) ||
			(getPosition().y - POWERUP_ICON_OUTER_RADIUS) < game_world_->boundary_rect_.origin.y )
			speed_.y *= -1;
	}

	setPosition(getPosition().x + speed_.x, getPosition().y + speed_.y);
}

void PowerUp::Tick()
{
	-- time_left_;

	// remove this power-up in the next iteration when it's on-screen time is over
	if(time_left_ < 0)
	{
		must_be_removed_ = true;
		runAction(Sequence::createWithTwoActions(EaseBackIn::create(ScaleTo::create(0.25f, 0.0f)), RemoveSelf::create(true)));
	}
}

void PowerUp::Spawn()
{
	// animate the entry
	runAction(EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f)));
	runAction(RepeatForever::create(Sequence::create(DelayTime::create(5 + CCRANDOM_0_1() * 5), EaseSineIn::create(ScaleTo::create(0.1f, 1.2f)), EaseSineOut::create(ScaleTo::create(0.1f, 1.0f)), EaseSineIn::create(ScaleTo::create(0.1f, 1.2f)), EaseSineOut::create(ScaleTo::create(0.1f, 1.0f)), NULL)));
}

void PowerUp::Activate()
{
	// clear the geometry and stop all actions
	// now the child classes can add their own behaviour
	is_active_ = true;
	clear();
	stopAllActions();
}

void PowerUp::Deactivate()
{
	// remove this power-up in the next iteration
	runAction(Sequence::createWithTwoActions(DelayTime::create(0.01f), RemoveSelf::create(true)));
	must_be_removed_ = true;
}
