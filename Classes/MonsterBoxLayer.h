#ifndef MONSTER_BOX_LAYER_H
#define MONSTER_BOX_LAYER_H

#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC_EXT; 
USING_NS_CC;



class MonsterBoxLayer : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // virtual void scrollViewDidScroll(ScrollView* view);
    
    // //scrollview缩放的时候会调用
    // virtual void scrollViewDidZoom(ScrollView* view);

    // virtual void tableCellTouched(TableView* table, TableViewCell* cell) ;
    // virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) ;
    // virtual ssize_t numberOfCellsInTableView(TableView *table) ;
    // virtual Size cellSizeForTable(TableView *table);
    // 
    // 
    int currentPage ; 

    void FunctionHome (cocos2d::Ref* pSender) ;

    float monster_box_back_button_height ;
    float monster_box_back_button_width ;

    CREATE_FUNC(MonsterBoxLayer);

    Rect rouletteRoundRect ; 

    Vec2 touchStartLocation , touchEndedLocation ; 
};



#endif