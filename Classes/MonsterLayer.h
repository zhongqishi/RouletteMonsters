#ifndef MONSTER_LAYER_H
#define MONSTER_LAYER_H

#include "cocos2d.h"
#include "cocos-ext.h"
// #include "cocos2d-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;  

class MonsterLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // a selector callback
    // void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MonsterLayer);

    
    void FunctionMonster (cocos2d::Ref* pSender) ;
    void TeamEdit(cocos2d::Ref* pSender) ;
    void MonsterBox(cocos2d::Ref* pSender);

   

};



#endif