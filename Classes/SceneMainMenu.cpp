#define level_background -4
#define level_btn 3

#include "SceneMainMenu.h"
USING_NS_CC;


Scene* SceneMainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
	auto layer_tag = SceneMainMenu::create();

    // add layer as a child to scene
	scene->addChild(layer_tag);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneMainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	_layer_function = LayerFunction::create();
	_layer_teamFunction = LayerTeamFunction::create();
	_layer_levelSelection = LayerLevelSelection::create();
	_layer_Muticomplex = LayerMultiplex::create(_layer_teamFunction, _layer_levelSelection, _layer_function, NULL);//创建多层布景层'
	_layer_Muticomplex->switchTo(1);
	this->addChild(_layer_Muticomplex, -1);//添加到场景，默认显示第一个布景  

    Size visibleSize = Director::getInstance()->getVisibleSize();
	auto s = Director::getInstance()->getWinSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is cli	cked to quit the program
    //    you may modify it.
	auto btn_HomeFunction = MenuItemImage::create(
		"MainMenu/button_home.png",
		"MainMenu/button_home.png",
		CC_CALLBACK_1(SceneMainMenu::menuFunctionCallback, this));


	auto btn_MonsterFunction = MenuItemImage::create(
		"MainMenu/button_monster.png",
		"MainMenu/button_monster.png",
		CC_CALLBACK_1(SceneMainMenu::menuFunctionCallback, this));

	auto btn_QuestFunction = MenuItemImage::create(
		"MainMenu/button_quest.png",
		"MainMenu/button_quest.png",
		CC_CALLBACK_1(SceneMainMenu::menuFunctionCallback, this));


	auto btn_FriendFunction = MenuItemImage::create(
		"MainMenu/button_friend.png",
		"MainMenu/button_friend.png",
		CC_CALLBACK_1(SceneMainMenu::menuFunctionCallback, this));


	auto btn_ShopFunction = MenuItemImage::create(
		"MainMenu/button_shop.png",
		"MainMenu/button_shop.png",
		CC_CALLBACK_1(SceneMainMenu::menuFunctionCallback, this));

	auto btn_OptionFunction = MenuItemImage::create(
		"MainMenu/button_option.png",
		"MainMenu/button_option.png",
		CC_CALLBACK_1(SceneMainMenu::menuFunctionCallback, this));

	level_background;

	btn_HomeFunction->setTag(0);
	btn_MonsterFunction->setTag(2);
	btn_QuestFunction->setTag(1);
	btn_FriendFunction->setTag(2);
	btn_ShopFunction->setTag(2);
	btn_OptionFunction->setTag(2);

	float scal;

	if (visibleSize.height < visibleSize.width){
		scal = (visibleSize.height / 8) / btn_HomeFunction->getContentSize().height;
	}
	else {
		scal = (visibleSize.width/6) / btn_HomeFunction->getContentSize().width;
	}


	btn_HomeFunction->setScale(scal);
	btn_MonsterFunction->setScale(scal);
	btn_QuestFunction->setScale(scal);
	btn_FriendFunction->setScale(scal);
	btn_ShopFunction->setScale(scal);
	btn_OptionFunction->setScale(scal);

	
	btn_HomeFunction->setAnchorPoint(Vec2(0.5, -0.02));
	btn_MonsterFunction->setAnchorPoint(Vec2(0.5, -0.02));
	btn_QuestFunction->setAnchorPoint(Vec2(0.5, -0.02));
	btn_FriendFunction->setAnchorPoint(Vec2(0.5, -0.02));
	btn_ShopFunction->setAnchorPoint(Vec2(0.5, -0.02));
	btn_OptionFunction->setAnchorPoint(Vec2(0.5, -0.02));

	auto menu2 = Menu::create(btn_HomeFunction, btn_MonsterFunction, btn_QuestFunction, btn_FriendFunction, btn_ShopFunction, btn_OptionFunction, NULL);
	

	menu2->setPosition(Vec2(visibleSize.width / 2 + origin.x, 0));
	//menu2->alignItemsHorizontally();
	menu2->alignItemsHorizontallyWithPadding(0);
	menu2->setAnchorPoint(Vec2::ZERO);

	this->addChild(menu2, level_btn);

	auto sprite = Sprite::create("MainMenu/buttons_behindbar.png");
	sprite->setScale(scal);
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, 0));
	sprite->setAnchorPoint(Vec2(0.5,0.07));
	// add the sprite as a child to this layer
	this->addChild(sprite, 2);



    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(SceneMainMenu::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width/5,
				origin.y + visibleSize.height - closeItem->getContentSize().height));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ONE);
    this->addChild(menu, 1);

    return true;
}


void SceneMainMenu::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void SceneMainMenu::menuFunctionCallback(cocos2d::Ref* pSender){
		int item = ((CCMenuItemImage*)pSender)->getTag();//获取选择项  
		if (item != _curLayerPos)
		{
			_layer_Muticomplex->switchTo(item);//切换布景，如果使用switchToAndReleaseMe会释放掉当前布景  
			_curLayerPos = item;
		}

}
