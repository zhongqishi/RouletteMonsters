#include "StartLayer.h"
#include "MainScene.h"

USING_NS_CC;

Scene* StartLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool StartLayer::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //背景图片
    auto start_background_sprite = Sprite::create("StartScene/Start_Scene_Background.png");
    start_background_sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    start_background_sprite->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    start_background_sprite->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    this->addChild(start_background_sprite, 0);

    //Start 文字
    auto start_word_sprite = Sprite::create("StartScene/Start_Scene_Word.png") ;
    start_word_sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    start_word_sprite->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    start_word_sprite->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    this->addChild(start_word_sprite, 1);

 
    //触屏事件监听
    auto onScreenTouchListener = EventListenerTouchOneByOne::create();
    // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    onScreenTouchListener->setSwallowTouches(true);

    // 使用 lambda 实现 onTouchBegan 事件回调函数
    onScreenTouchListener->onTouchBegan = [](Touch* touch, Event* event){
        // 获取事件所绑定的 target 
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        // 获取当前点击点所在相对按钮的位置坐标
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        // 点击范围判断检测
        if (rect.containsPoint(locationInNode))
        {
            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
            auto scene = Scene::create();
            MainScene *main_scene_layer = MainScene::create();
            scene->addChild(main_scene_layer) ;
            auto transitions = CCTransitionFade::create(2.0f, scene);
            Director::getInstance()->replaceScene( transitions );
            // target->setOpacity(180);
            return true;
        }
        return false;
        };

    // 触摸移动时触发
    onScreenTouchListener->onTouchMoved = [](Touch* touch, Event* event){;};

    // 点击事件结束处理
    onScreenTouchListener->onTouchEnded = [=](Touch* touch, Event* event){;};

    // 添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(onScreenTouchListener, start_background_sprite);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(onScreenTouchListener->clone(), start_word_sprite);
    
    return true;
}


void StartLayer::toMainLayerScene()
{

    auto scene = Scene::create();
    MainScene *main_scene_layer = MainScene::create();
    scene->addChild(main_scene_layer) ;
    auto transitions = CCTransitionFade::create(1.0f, scene);
    Director::getInstance()->replaceScene( transitions );

}

