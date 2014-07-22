#include "CopyRightScene.h"
#include "StartLayer.h"
#include "AppMacros.h"

USING_NS_CC;

Scene* CopyRightScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CopyRightScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CopyRightScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto copyright_scene_sprite = Sprite::create("CopyRightScene/CopyRight.png");

    // position the sprite on the center of the screen
    copyright_scene_sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    log("VisibleSize.width=%f",(visibleSize.width/DESIGNED_WIDTH));
    log("VisibleSize.height=%f",(visibleSize.height/DESIGNED_HEIGHT));
    copyright_scene_sprite->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    copyright_scene_sprite->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    // add the sprite as a child to this layer
    this->addChild(copyright_scene_sprite, 0);
    this->scheduleOnce(schedule_selector(CopyRightScene::toStartLayerScene), 1.0f);
    
    return true;
}

void CopyRightScene::toStartLayerScene(float dt)
{
    auto scene = Scene::create();
    StartLayer *start_scene = StartLayer::create();
    scene->addChild(start_scene) ;
    auto transitions = CCTransitionFade::create(2.0f, scene);
    Director::getInstance()->replaceScene( transitions ); 

}
