#define changingTime 0.5

#include "LayerTeamFunction.h"

USING_NS_CC;

float positions_x[4];
float positions_y[4];
float positions_z[4] = { 2, 1, 0, 1 };
float scale[4] = { 0.8f, 0.6f, 0.4f, 0.6f };
int monster_now=0;
Vec2 location1;
Scene* LayerTeamFunction::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LayerTeamFunction::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LayerTeamFunction::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	positions_x[0] = visibleSize.width / 2;
	positions_y[0] = visibleSize.height / 2;
	positions_x[1] = visibleSize.width *3 / 4;
	positions_y[1] = visibleSize.height / 2;
	positions_x[2] = visibleSize.width  / 2;
	positions_y[2] = visibleSize.height / 2;
	positions_x[3] = visibleSize.width /4;
	positions_y[3] = visibleSize.height / 2;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LayerTeamFunction::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(LayerTeamFunction::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Team Layer", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	label_monster1 = LabelTTF::create("Monster1","Arial", 24);
	label_monster2 = LabelTTF::create("Monster2", "Arial", 24);
	label_monster3 = LabelTTF::create("Monster3", "Arial", 24);
	label_monster4 = LabelTTF::create("Monster4", "Arial", 24);
	sprite_monster1 = Sprite::create("monsterHolder.png");
	sprite_monster2 = Sprite::create("monsterHolder.png");
	sprite_monster3 = Sprite::create("monsterHolder.png");
	sprite_monster4 = Sprite::create("monsterHolder.png");

	label_monster1->setPosition(Vec2(positions_x[0], positions_y[1] + 220 * scale[0]));
	label_monster2->setPosition(Vec2(positions_x[1], positions_y[2] + 220 * scale[1]));
	label_monster3->setPosition(Vec2(positions_x[2], positions_y[3] + 220 * scale[2]));
	label_monster4->setPosition(Vec2(positions_x[3], positions_y[4] + 220 * scale[3]));

	sprite_monster1->setPosition(Vec2(positions_x[0], positions_y[0]));
	sprite_monster2->setPosition(Vec2(positions_x[1], positions_y[1]));
	sprite_monster3->setPosition(Vec2(positions_x[2], positions_y[2]));
	sprite_monster4->setPosition(Vec2(positions_x[3], positions_y[3]));

	sprite_monster1->setPositionZ(positions_z[0]);
	sprite_monster2->setPositionZ(positions_z[1]);
	sprite_monster3->setPositionZ(positions_z[2]);
	sprite_monster4->setPositionZ(positions_z[3]);

	label_monster1->setScale(scale[0]);
	label_monster2->setScale(scale[1]);
	label_monster3->setScale(scale[2]);
	label_monster4->setScale(scale[3]);

	sprite_monster1->setScale(scale[0]);
	sprite_monster2->setScale(scale[1]);
	sprite_monster3->setScale(scale[2]);
	sprite_monster4->setScale(scale[3]);

	this->addChild(label_monster1);
	this->addChild(label_monster2);
	this->addChild(label_monster3);
	this->addChild(label_monster4);

	this->addChild(sprite_monster1);
	this->addChild(sprite_monster2);
	this->addChild(sprite_monster3);
	this->addChild(sprite_monster4);


	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("teambg.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, -1);

	return true;
}


void LayerTeamFunction::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


bool LayerTeamFunction::onTouchBegan(Touch* touch, Event  *event)
{
	location1 = touch->getLocation();
	return true;
}

void LayerTeamFunction::onTouchEnded(Touch* touch, Event  *event)
{
	auto location2 = touch->getLocation();
	int no1=0, no2=0, no3=0, no4=0;


	float o = location2.x - location1.x;
	if (o > 0){
		if (monster_now == 3){
			monster_now = -1;
		}
		monster_now++;
	
	}
	else{
		if (monster_now == 0){
			monster_now = 4;
		}
		monster_now--;
	}

	no1 = monster_now + 0;
	no2 = monster_now + 1;
	no3 = monster_now + 2;
	no4 = monster_now + 3;
	if (no1 > 3)
		no1 = no1 - 4;

	if (no2 > 3){
		no2 = no2 - 4;
	}
	if (no3 > 3){
		no3 = no3 - 4;
	}
	if (no4 > 3){
		no4 = no4 - 4;
	}

	label_monster1->runAction(MoveTo::create(changingTime, Vec2(positions_x[no1], positions_y[no1] + 220 * scale[no1])));
	label_monster1->runAction(ScaleTo::create(changingTime, scale[no1]));
	label_monster1->setPositionZ(positions_z[no1]);

	label_monster2->runAction(MoveTo::create(changingTime, Vec2(positions_x[no2], positions_y[no2] + 220 * scale[no2])));
	label_monster2->runAction(ScaleTo::create(changingTime, scale[no2]));
	label_monster2->setPositionZ(positions_z[no2]);

	label_monster3->runAction(MoveTo::create(changingTime, Vec2(positions_x[no3], positions_y[no3] + 220 * scale[no3])));
	label_monster3->runAction(ScaleTo::create(changingTime, scale[no3]));
	label_monster3->setPositionZ(positions_z[no3]);

	label_monster4->runAction(MoveTo::create(changingTime, Vec2(positions_x[no4], positions_y[no4] + 220 * scale[no4])));
	label_monster4->runAction(ScaleTo::create(changingTime, scale[no4]));
	label_monster4->setPositionZ(positions_z[no4]);

	sprite_monster1->runAction(MoveTo::create(changingTime, Vec2(positions_x[no1], positions_y[no1])));
	sprite_monster1->runAction(ScaleTo::create(changingTime, scale[no1]));
	sprite_monster1->setPositionZ(positions_z[no1]);

	sprite_monster2->runAction(MoveTo::create(changingTime, Vec2(positions_x[no2], positions_y[no2])));
	sprite_monster2->runAction(ScaleTo::create(changingTime, scale[no2]));
	sprite_monster2->setPositionZ(positions_z[no2]);

	sprite_monster3->runAction(MoveTo::create(changingTime, Vec2(positions_x[no3], positions_y[no3])));
	sprite_monster3->runAction(ScaleTo::create(changingTime, scale[no3]));
	sprite_monster3->setPositionZ(positions_z[no3]);

	sprite_monster4->runAction(MoveTo::create(changingTime, Vec2(positions_x[no4], positions_y[no4])));
	sprite_monster4->runAction(ScaleTo::create(changingTime, scale[no4]));
	sprite_monster4->setPositionZ(positions_z[no4]);



}