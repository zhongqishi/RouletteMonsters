#ifndef __Layer_Function_H__
#define __Layer_Function_H__

#include "cocos2d.h"

class LayerLoading : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual void update(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(LayerLoading);
};

#endif // __Layer_Function_H__
