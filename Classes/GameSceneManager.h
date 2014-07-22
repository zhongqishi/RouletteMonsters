#ifndef GAME_SCENE_MANAGER_H
#define GAME_SCENE_MANAGER_H

#include "cocos2d.h"

class GameSceneManager : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();


    void toMainScene() ; 

    void toMonsterScene() ; 

    
    // a selector callback
    // void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameSceneManager);
};



#endif
