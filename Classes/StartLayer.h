#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "cocos2d.h"

class StartLayer : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    //切换到主界面
    void toMainLayerScene() ;

    CREATE_FUNC(StartLayer);
};



#endif
