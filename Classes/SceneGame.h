#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"
#include "string"
#include "Resources.h"
USING_NS_CC;

class SceneGame : public cocos2d::Layer
{
public:
	static std::string MonsterPin1;
	static std::string MonsterPin2;
	static std::string MonsterPin3;
	static std::string MonsterPin4;
	static std::string boss;
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(std::string MonsterPin1, std::string MonsterPin2, std::string MonsterPin3, std::string MonsterPin4, std::string boss);
	static cocos2d::Layer* create(std::string MonsterPin1, std::string MonsterPin2, std::string MonsterPin3, std::string MonsterPin4, std::string boss);
	//static void setParameter(std::string MonsterPin_1, std::string MonsterPin_2, std::string MonsterPin_3, std::string MonsterPin_4);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(std::string MonsterPin1, std::string MonsterPin2, std::string MonsterPin3, std::string MonsterPin4, std::string boss);

	bool onTouchBegan(Touch* touch, Event  *event);
	void onTouchEnded(Touch* touch, Event  *event);
	void menuCallback(cocos2d::Ref* pSender);

	bool toucheTheCenterOfZhuanpanThePosition(float x,float y);

	void setEmitterPosition();
	virtual void update(float dt);
	
	// implement the "static create()" method manually

private:
	void beAttacked();

	Sprite* theBoss;
	SpriteBatchNode * CrystalPin;
	ParticleSystemQuad*    Partical_Emitter;
	MotionStreak * streak;
	Vec2 gs_MotionStreak_center;
	float gs_MotionStreak_radius;
	float gs_MotionStreak_angle;
	
};

#endif // __Game_SCENE_H__
