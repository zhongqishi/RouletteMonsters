#include "LayerLoading.h"
#include "SceneGame.h"
#include "Monster.h"
USING_NS_CC;
int layerLoading_timer_start = 0;
Scene* LayerLoading::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LayerLoading::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LayerLoading::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("Loading.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScaleX(visibleSize.width / sprite->getContentSize().width);
	sprite->setScaleY(visibleSize.height / sprite->getContentSize().height);
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	layerLoading_timer_start = 1;
	this->scheduleUpdate();

	return true;
}


void LayerLoading::update(float dt){
	if (layerLoading_timer_start != 0){
		layerLoading_timer_start++;
		if (layerLoading_timer_start == 250){
			layerLoading_timer_start = 0;
			auto s = SceneGame::createScene(new GodnessMinerva(false, 100), new PrincessShieldWaerqili(false, 100), new GoddessOfLoveVenus(false, 100), new Archdemon(false, 100));
			Director::sharedDirector()->replaceScene(TransitionFade::create(1, s));
		}
	}
}
