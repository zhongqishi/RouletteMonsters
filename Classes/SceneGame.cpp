# define Math_PI           3.14159265358979323846  /* pi */
# define Level_0           0
# define Level_1           1
# define Level_2           2
# define Level_3           3
# define circlesToTurn     4
# define circleTurnTime    2

#include "SceneGame.h"
#include "SceneMainMenu.h"
#include "UtilFadeRotateRy.h"
#include "UtilBeingAttack.h"
#include "UtilAttackMove.h"
#include <string>
#include <cstdlib>
#include <cmath>
USING_NS_CC;

float angleRate = -5.0f;
float scalNow,scalZhuanPan;
float zhuanPanActionTime = 3.2f;
int StreakRadiusParameter=255;
bool touched = false;
bool actionFinished = false;
int percentageOf = 0;
float position[2];
int zhuanPanCenterLevel[4] = {4,3,2,1};
enum
{
	PinSpriteNo1 = 1,
	PinSpriteNo2 = 2,
	PinSpriteNo3 = 3,
	PinSpriteNo4 = 4,
};



Scene* SceneGame::createScene(std::string MonsterPin1, std::string MonsterPin2, std::string MonsterPin3, std::string MonsterPin4, std::string boss)
{
	// 'scene' is an autorelease object

	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = create(MonsterPin1, MonsterPin2, MonsterPin3, MonsterPin4,boss);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

Layer* SceneGame::create(std::string MonsterPin1, std::string MonsterPin2, std::string MonsterPin3, std::string MonsterPin4, std::string boss)
{
	SceneGame *ret = new SceneGame();
    if (ret && ret->init(MonsterPin1, MonsterPin2, MonsterPin3, MonsterPin4,boss))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

// on "init" you need to initialize your instance
bool SceneGame::init(std::string MonsterPin1, std::string MonsterPin2, std::string MonsterPin3, std::string MonsterPin4, std::string boss)
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SceneGame::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SceneGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SceneGame::menuCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 5,
		origin.y + visibleSize.height - closeItem->getContentSize().height));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ONE);
	this->addChild(menu, 1);

	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto sprite_zhuanpanOutSide = Sprite::create("outside.png");

	auto zhuanpan_center = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height /3.5 + origin.y);
	position[0] = visibleSize.width / 2 + origin.x;
	position[1] = visibleSize.height / 3.5 + origin.y;
	sprite_zhuanpanOutSide->setPosition(zhuanpan_center);
	float  scal_ZhuanPan = visibleSize.height / sprite_zhuanpanOutSide->getContentSize().height;
	if(visibleSize.width/2>visibleSize.height/3){
		scal_ZhuanPan = visibleSize.width/520;
	}
	scal_ZhuanPan=scal_ZhuanPan/2.3;
	scalZhuanPan = scal_ZhuanPan;
	sprite_zhuanpanOutSide->setScale(scal_ZhuanPan);
	addChild(sprite_zhuanpanOutSide, Level_1);

	auto label = LabelTTF::create("Game Layer", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, Level_0);
	

	// add "HelloWorld" splash screen"
	auto sprite_pin1 = Sprite::create(MonsterPin1);
	auto sprite_pin2 = Sprite::create(MonsterPin2);
	auto sprite_pin3 = Sprite::create(MonsterPin3);
	auto sprite_pin4 = Sprite::create(MonsterPin4);

	// position the sprite on the center of the screen
	sprite_pin1->setPosition(zhuanpan_center);
	sprite_pin2->setPosition(zhuanpan_center);
	sprite_pin3->setPosition(zhuanpan_center);
	sprite_pin4->setPosition(zhuanpan_center);

	sprite_pin1->setScale(scal_ZhuanPan);
	sprite_pin2->setScale(scal_ZhuanPan);
	sprite_pin3->setScale(scal_ZhuanPan);
	sprite_pin4->setScale(scal_ZhuanPan);

	sprite_pin2->setRotation(90.0f);
	sprite_pin3->setRotation(180.0f);
	sprite_pin4->setRotation(270.0f);

	// add the sprite as a child to this layer
	this->addChild(sprite_pin1, Level_2, PinSpriteNo1);
	this->addChild(sprite_pin2, Level_2, PinSpriteNo2);
	this->addChild(sprite_pin3, Level_2, PinSpriteNo3);
	this->addChild(sprite_pin4, Level_2, PinSpriteNo4);
	
	this->scheduleUpdate();

	auto sprite_ZhuanpanCenter0 = Sprite::create("ZhuanpanCenter03.png");
	auto sprite_ZhuanpanCenter1 = Sprite::create("ZhuanpanCenter13.png");
	auto sprite_ZhuanpanCenter2 = Sprite::create("ZhuanpanCenter23.png");
	auto sprite_ZhuanpanCenter3 = Sprite::create("ZhuanpanCenter33.png");


	sprite_ZhuanpanCenter0->setTag(30);
	sprite_ZhuanpanCenter1->setTag(31);
	sprite_ZhuanpanCenter2->setTag(32);
	sprite_ZhuanpanCenter3->setTag(33);

	sprite_ZhuanpanCenter0->setPosition(zhuanpan_center);
	sprite_ZhuanpanCenter1->setPosition(zhuanpan_center);
	sprite_ZhuanpanCenter2->setPosition(zhuanpan_center);
	sprite_ZhuanpanCenter3->setPosition(zhuanpan_center);


	sprite_ZhuanpanCenter0->setScale(scal_ZhuanPan);
	sprite_ZhuanpanCenter1->setScale(scal_ZhuanPan);
	sprite_ZhuanpanCenter2->setScale(scal_ZhuanPan);
	sprite_ZhuanpanCenter3->setScale(scal_ZhuanPan);

	sprite_ZhuanpanCenter0->setPositionZ(zhuanPanCenterLevel[0]);
	sprite_ZhuanpanCenter1->setPositionZ(zhuanPanCenterLevel[1]);
	sprite_ZhuanpanCenter2->setPositionZ(zhuanPanCenterLevel[2]);
	sprite_ZhuanpanCenter3->setPositionZ(zhuanPanCenterLevel[3]);

	this->addChild(sprite_ZhuanpanCenter0);
	this->addChild(sprite_ZhuanpanCenter1);
	this->addChild(sprite_ZhuanpanCenter2);
	this->addChild(sprite_ZhuanpanCenter3);

	streak = MotionStreak::create(3.0f, 1.0f, 10.0f, Color3B(255, 255, 0), "MotionStreak.png");
	addChild(streak,1);

	Partical_Emitter = ParticleFlower::create();
	Partical_Emitter->autorelease();
	Partical_Emitter->retain();
	streak->addChild(Partical_Emitter, 5);
	Partical_Emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("stars.png"));


	gs_MotionStreak_center = zhuanpan_center;
	gs_MotionStreak_radius = StreakRadiusParameter*scal_ZhuanPan;
	gs_MotionStreak_angle = 0.0f;
	/////////////////////////////

	auto spriteHP = Sprite::create("HP.png");
	float temp = visibleSize.height / 3 + gs_MotionStreak_radius;
	spriteHP->setPosition(Vec2(visibleSize.width / 2, (float)temp));
	spriteHP->setScaleX(visibleSize.width / spriteHP->getContentSize().width);
	spriteHP->setScaleY(0.5);
	this->addChild(spriteHP, Level_3);
	
	// add "HelloWorld" splash screen"
	auto spriteBg = Sprite::create("SceneGameBg.png");

	// position the sprite on the center of the screen
	spriteBg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layerd
	this->addChild(spriteBg, Level_0);


	// add "HelloWorld" splash screen"
	auto spriteBoss = Sprite::create(boss);
	this->theBoss = spriteBoss;
	float  scal = visibleSize.height / spriteBoss->getContentSize().height;
	spriteBoss->setScale(scal / 3);
	scalNow = scal / 3;
	// position the sprite on the center of the screen
	spriteBoss->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height*(1-scal/6.5)));

	// add the sprite as a child to this layer
	this->addChild(spriteBoss, Level_0);


	return true;
}

void SceneGame::setEmitterPosition()
{
	auto s = Director::getInstance()->getWinSize();
	if (Partical_Emitter != NULL)
	{
		Partical_Emitter->setPosition(Vec2(s.width /3, s.height / 3));
	}
}


void SceneGame::update(float dt)
{
	gs_MotionStreak_angle += angleRate;
	streak->setPosition(Vec2(gs_MotionStreak_center.x + cosf(gs_MotionStreak_angle / 180 * M_PI)*gs_MotionStreak_radius,
		gs_MotionStreak_center.y + sinf(gs_MotionStreak_angle / 180 * M_PI)*gs_MotionStreak_radius));
	Partical_Emitter->setPosition(Vec2(gs_MotionStreak_center.x + cosf(gs_MotionStreak_angle / 180 * M_PI)*gs_MotionStreak_radius,
		gs_MotionStreak_center.y + sinf(gs_MotionStreak_angle / 180 * M_PI)*gs_MotionStreak_radius));
	if (touched){
		auto *s1 = getChildByTag(PinSpriteNo1);

		if (s1->numberOfRunningActions()==0){
			touched = false;
			beAttacked();

		}

	}

	if (actionFinished){

	}
}


void SceneGame::beAttacked(){



	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto splade2 = MotionStreak::create(1.0f, 1.0f, 2.0f, Color3B(255, 255, 0), "MotionStreak.png");
	splade2->setTag(999);
	int temp = rand() % 100;
	float a = visibleSize.height - 200 + temp;
	float b = visibleSize.width;
	this->addChild(splade2, 1);

	splade2->setPosition(Vec2(0,a));
	splade2->runAction(UtilAttackMove::create(0.5f, 0, a, b, visibleSize.height - temp));
	this->theBoss->runAction(UtilBeingAttack::create(0.5f, scalNow));
	actionFinished = true;
}



bool SceneGame::onTouchBegan(Touch* touch, Event  *event)
{
	
	return true;
}



bool SceneGame::toucheTheCenterOfZhuanpanThePosition(float x,float y){
	MessageBox("Touched","alert");
	if ((abs(x - position[0])<50 * scalZhuanPan) && (abs(y - position[1])<50 * scalZhuanPan))
		return true;
	return false;
}



void SceneGame::onTouchEnded(Touch* touch, Event  *event)
{
	auto c0 = getChildByTag(30);
	auto c1 = getChildByTag(31);
	auto c2 = getChildByTag(32);
	auto c3 = getChildByTag(33);

	auto location = touch->getLocation();
	if (percentageOf == 3 && toucheTheCenterOfZhuanpanThePosition(location.x,location.y)){
		percentageOf = 0;

		c0->setPositionZ(zhuanPanCenterLevel[0]);
		c1->setPositionZ(zhuanPanCenterLevel[1]);
		c2->setPositionZ(zhuanPanCenterLevel[2]);
		c3->setPositionZ(zhuanPanCenterLevel[3]);

	}
	else{

		percentageOf++;
		if (percentageOf > 3)
			percentageOf = 3;
		int temp1, temp2, temp3, temp4;

		temp1 = percentageOf - 0;
		temp2 = percentageOf - 1;
		temp3 = percentageOf - 2;
		temp4 = percentageOf - 3;

		if (temp2 < 0)
			temp2 = -temp2;
		if (temp3 < 0)
			temp3 = -temp3;
		if (temp4 < 0)
			temp4 = -temp4;


		c0->setPositionZ(zhuanPanCenterLevel[temp1]);
		c1->setPositionZ(zhuanPanCenterLevel[temp2]);
		c2->setPositionZ(zhuanPanCenterLevel[temp3]);
		c3->setPositionZ(zhuanPanCenterLevel[temp4]);

		

		auto s1 = getChildByTag(PinSpriteNo1);
		auto s2 = getChildByTag(PinSpriteNo2);
		auto s3 = getChildByTag(PinSpriteNo3);
		auto s4 = getChildByTag(PinSpriteNo4);
		s1->stopAllActions();
		s2->stopAllActions();
		s3->stopAllActions();
		s4->stopAllActions();

		float o = location.x - s1->getPosition().x;
		float a = location.y - s1->getPosition().y;
		float at = (fabs(a) + fabs(o))*1.5;

		auto *action1 = UtilFadeRotateRy::create(at, zhuanPanActionTime);
		auto *action2 = UtilFadeRotateRy::create(at, zhuanPanActionTime);
		auto *action3 = UtilFadeRotateRy::create(at, zhuanPanActionTime);
		auto *action4 = UtilFadeRotateRy::create(at, zhuanPanActionTime);

		s1->runAction(action1);
		s2->runAction(action2);
		s3->runAction(action3);
		s4->runAction(action4);
		touched = true;
	}

	
	
}


void SceneGame::menuCallback(cocos2d::Ref* pSender){

	auto s = SceneMainMenu::createScene();

	Director::sharedDirector()->replaceScene(TransitionFade::create(1, s));
}
