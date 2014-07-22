#ifndef HOME_LAYER_H
#define HOME_LAYER_H

#include "cocos2d.h"

#include "AllClassLists.h"

class HomeLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HomeLayer);  

    virtual bool rouletteRoundOnTouchBegan(Touch* touch, Event  *event) ;  
    virtual void rouletteRoundOnTouchMoved(Touch* touch, Event  *event) ;  
    virtual void rouletteRoundOnTouchEnded(Touch* touch, Event  *event) ;  

    

    Rect rouletteRoundRect ; 

    Vec2 touchStartLocation , touchEndedLocation ; 
    struct timeval lastSwipe,currentSwipe;
    int currentMonster ;

    Texture2D *monsterImageTexture [ 4 ],
                *monsterNameTexture [ 4 ],
                *monsterBaseTexture [ 4 ],
                *monsterLevelTexture [ 4 ] ;


};




#endif