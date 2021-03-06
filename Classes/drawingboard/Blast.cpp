#include "Blast.h"
#include "GameWorld.h"

Blast* Blast::createWithRadiusAndDuration(float radius, float duration)
{
	Blast* blast = new Blast();
	if(blast && blast->initWithRadiusAndDuration(radius, duration))
	{
		blast->autorelease();
		return blast;
	}
	CC_SAFE_DELETE(blast);
	return NULL;
}

bool Blast::initWithRadiusAndDuration(float radius, float duration)
{
	if(!DrawNode::init())
	{
		return false;
	}

	radius_ = radius;
	duration_ = duration;

	// initially scale down completely
	setScale(0.0f);
	drawDot(Point::ZERO, radius_, Color4F(1, 0.34118f, 0, 1));
	drawDot(Point::ZERO, radius_ * 0.8f, Color4F(1, 0.68235f, 0, 0.25f));
	drawDot(Point::ZERO, radius_ * 0.75f, Color4F(1, 0.68235f, 0, 0.5f));
	drawDot(Point::ZERO, radius_ * 0.7f, Color4F(1, 0.68235f, 0, 0.5f));
	drawDot(Point::ZERO, radius_ * 0.6f, Color4F(1, 0.83529f, 0.40392f, 0.25f));
	drawDot(Point::ZERO, radius_ * 0.55f, Color4F(1, 0.83529f, 0.40392f, 0.5f));
	drawDot(Point::ZERO, radius_ * 0.5f, Color4F(1, 0.83529f, 0.40392f, 0.5));
	drawDot(Point::ZERO, radius_ * 0.4f, Color4F(1, 1, 1, 0.25f));
	drawDot(Point::ZERO, radius_ * 0.35f, Color4F(1, 1, 1, 0.75f));
	drawDot(Point::ZERO, radius_ * 0.3f, Color4F(1, 1, 1, 1));
	// scale-up, then wait for 'duration_' amount of seconds before cooling down
	runAction(Sequence::create(EaseSineOut::create(ScaleTo::create(0.25f, 1.0f)), DelayTime::create(duration_), CallFunc::create(this, callfunc_selector(Blast::Cooldown)), NULL));

	return true;
}

void Blast::Cooldown()
{
	// remove this blast in the next iteration
	must_be_removed_ = true;
	// animate exit then remove with cleanup
	runAction(Sequence::createWithTwoActions(EaseSineOut::create(ScaleTo::create(0.5f, 0.0f)), RemoveSelf::create(true)));
}
