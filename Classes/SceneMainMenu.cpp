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
	auto btn_MainFunction = MenuItemImage::create(
		"MainButton.png",
		"MainButtonPressed.png",
		CC_CALLBACK_1(SceneMainMenu::menuFunctionCallback, this));


	auto btn_function1 = MenuItemImage::create(
		"Button.png",
		"ButtonPressed.png",
		CC_CALLBACK_1(SceneMainMenu::menuFunctionCallback, this));

	auto btn_function2 = MenuItemImage::create(
		"Button.png",
		"ButtonPressed.png",
		CC_CALLBACK_1(SceneMainMenu::menuFunctionCallback, this));


	auto btn_function3 = MenuItemImage::create(
		"Button.png",
		"ButtonPressed.png",
		CC_CALLBACK_1(SceneMainMenu::menuFunctionCallback, this));


	auto btn_function4 = MenuItemImage::create(
		"Button.png",
		"ButtonPressed.png",
		CC_CALLBACK_1(SceneMainMenu::menuFunctionCallback, this));

	btn_function1->setTag(0);
	btn_function2->setTag(2);
	btn_MainFunction->setTag(1);
	btn_function3->setTag(2);
	btn_function4->setTag(2);

	auto menu2 = Menu::create(btn_function1, btn_function2, btn_MainFunction, btn_function3, btn_function4, NULL);
	menu2->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + btn_MainFunction->getContentSize().height / 2));

	menu2->alignItemsHorizontallyWithPadding(10);
	menu2->setAnchorPoint(Vec2::ZERO);
	this->addChild(menu2,3);

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
