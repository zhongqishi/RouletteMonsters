#ifndef COPYRIGHT_SCENE_H
#define COPYRIGHT_SCENE_H

#include "cocos2d.h"

class CopyRightScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    //定时切换场景函数，切换到开始层
    void toStartLayerScene(float dt);

    // a selector callback
    // void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(CopyRightScene);
};



#endif