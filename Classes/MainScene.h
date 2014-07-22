#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include "cocos2d.h"

#include "AllClassLists.h"


USING_NS_CC;


class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

    GameSceneManager *manager ;  

    LayerMultiplex *layer_manager ; 

    void ReadUserData() ;

    

    //场景切换函数

 	void FunctionHome (cocos2d::Ref* pSender) ;
 	void FunctionQuest (cocos2d::Ref* pSender) ;
 	void FunctionMonster(cocos2d::Ref* pSender) ;
    void FunctionFriend(cocos2d::Ref* pSender) ;
 	void FunctionShop(cocos2d::Ref* pSender) ;
 	void FunctionOption(cocos2d::Ref* pSender) ;


};




#endif