#ifndef __MainMenuScene_SCENE_H__
#define __MainMenuScene_SCENE_H__

#include "cocos2d.h"
#include "AllClassLists.h"

class SceneMainMenu : public cocos2d::Layer
{

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void menuFunctionCallback(cocos2d::Ref* pSender);
		
    // implement the "static create()" method manually
	CREATE_FUNC(SceneMainMenu);
		
    cocos2d::LayerMultiplex *_layer_Muticomplex;
	LayerFunction *_layer_function;
	LayerTeamFunction *_layer_teamFunction;
	LayerLevelSelection *_layer_levelSelection;
	int _curLayerPos = 1;

};

#endif // __MainMenuScene_SCENE_H__
