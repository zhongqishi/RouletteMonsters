#include "LayerLevelSelection.h"
#include "LayerLoading.h"
#include "SceneGame.h"
#include "Monster.h"
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
	this->addChild(label, 1);
	auto closeItem = MenuItemImage::create(
		"SceneGame/CloseNormal.png",
		"SceneGame/CloseSelected.png",
		CC_CALLBACK_1(LayerLevelSelection::menuFunctionCallback, this));

	
	closeItem->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - closeItem->getContentSize().height));


	auto menu = Menu::create(closeItem, NULL);

	menu->setTag(10);
	menu->setOpacity(1);
	this->addChild(menu, 10);
	menu->setPosition(Vec2::ZERO);
	


	// add the label as a child to this layer
	


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
	sprite->setTag(12);
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScaleX(visibleSize.width / sprite->getContentSize().width);
	// add the sprite as a child to this layer
	this->addChild(sprite,0);

	//创建一个数组，存储CCSpriteFrame
	

	return true;
}



void LayerLevelSelection::menuFunctionCallback(Ref* pSender)
{

 
	auto s = SceneGame::createScene(new GodnessMinerva(false, 100), new PrincessShieldWaerqili(false, 100), new GoddessOfLoveVenus(false, 100), new Archdemon(false, 100));
	Director::sharedDirector()->replaceScene(TransitionFade::create(1, s));

}

