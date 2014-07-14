#include "LayerLevelSelection.h"
#include "Resources.h"
#include "SceneGame.h"
#include <string>
USING_NS_CC;

Scene* LayerLevelSelection::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LayerLevelSelection::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LayerLevelSelection::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Level Layer", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);


	auto btn_function1 = MenuItemImage::create(
		"btnLevelNormal.png",
		"btnLevelPressed.png",
		CC_CALLBACK_1(LayerLevelSelection::menuFunctionCallback, this));

	auto btn_function2 = MenuItemImage::create(
		"btnLevelNormal.png",
		"btnLevelPressed.png",
		CC_CALLBACK_1(LayerLevelSelection::menuFunctionCallback, this));


	auto btn_function3 = MenuItemImage::create(
		"btnLevelNormal.png",
		"btnLevelPressed.png",
		CC_CALLBACK_1(LayerLevelSelection::menuFunctionCallback, this));


	auto btn_function4 = MenuItemImage::create(
		"btnLevelNormal.png",
		"btnLevelPressed.png",
		CC_CALLBACK_1(LayerLevelSelection::menuFunctionCallback, this));

	btn_function1->setTag(1);
	btn_function2->setTag(2);
	btn_function3->setTag(3);
	btn_function4->setTag(4);

	auto menu2 = Menu::create(btn_function1, btn_function2, btn_function3, btn_function4, NULL);
	menu2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height*2 /3 + origin.y));
	menu2->alignItemsVerticallyWithPadding(10);

	this->addChild(menu2, 1);


	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("MainMenuBackground.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	return true;
}



void LayerLevelSelection::menuFunctionCallback(Ref* pSender)
{
	//SceneGame::createSceneGame();
	auto s = SceneGame::createScene("pin1.png", "pin2.png", "pin1.png", "pin2.png", "demoboss.png");
	Director::sharedDirector()->replaceScene(TransitionFade::create(1,s));
}

