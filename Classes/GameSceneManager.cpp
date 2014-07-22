#include "GameSceneManager.h"
#include "AllClassLists.h"
USING_NS_CC;

Scene* GameSceneManager::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    CopyRightScene *copyright_scene_layer = CopyRightScene::create();

    // add layer as a child to scene
    scene->addChild(copyright_scene_layer);

    // return the scene
    return scene;
}

void GameSceneManager::toMainScene()
{



}

void GameSceneManager::toMonsterScene()
{
	auto scene = Scene::create();
    MonsterLayer *monster_scene_layer = MonsterLayer::create();
    scene->addChild(monster_scene_layer) ;
    auto transitions = CCTransitionFade::create(2.0f, scene);
    Director::getInstance()->replaceScene( transitions );
}

