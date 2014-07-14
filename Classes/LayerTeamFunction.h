#ifndef __TEAMFunction_SCENE_H__
#define __TEAMFunction_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class LayerTeamFunction : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback

	bool onTouchBegan(Touch* touch, Event  *event);
	void onTouchEnded(Touch* touch, Event  *event);

	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuFunctionCallback(cocos2d::Ref* pSender);
	
	// implement the "static create()" method manually
	CREATE_FUNC(LayerTeamFunction);

private:
	cocos2d::LabelTTF* label_monster1;
	cocos2d::LabelTTF* label_monster2;
	cocos2d::LabelTTF* label_monster3;
	cocos2d::LabelTTF* label_monster4;
	cocos2d::Sprite * sprite_monster1;
	cocos2d::Sprite * sprite_monster2;
	cocos2d::Sprite * sprite_monster3;
	cocos2d::Sprite * sprite_monster4;



};

#endif // __TEAMFunction_SCENE_H__
