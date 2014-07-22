#include "MonsterBoxLayer.h"
#include "AppMacros.h"
#include "AllClassLists.h"

#define MONSTER_BOX_WIDTH 1080
#define MONSTER_BOX_HEIGHT 1300

#define MONSTER_ROW_NUMBER 6
#define MONSTER_COLUMN_NUMBER 5 

#define MONSTER_IMAGE_HEIGHT 165
#define MONSTER_IMAGE_WIDTH 161

Scene* MonsterBoxLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MonsterBoxLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MonsterBoxLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    float currentHeight = MAIN_SCENE_LAYER_TOP_HEIGHT ; 
    float currentWidth = 0 ; 
    float menuWidth = 0 ;
    float menuHeight = 0 ;
    
    auto monster_box_back_button_sprite = Sprite::create("MonsterBox/Monster_Box_Back_Button.png") ;
    monster_box_back_button_sprite->setPosition(Vec2(currentWidth, currentHeight )) ;
    monster_box_back_button_sprite->setAnchorPoint(ccp(0,1));
    this->addChild(monster_box_back_button_sprite,GAME_LEVEL) ;

    monster_box_back_button_height = monster_box_back_button_sprite->getContentSize().height ;
    monster_box_back_button_width = monster_box_back_button_sprite->getContentSize().width ;

    auto onScreenTouchListener = EventListenerTouchOneByOne::create();
    // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    // onScreenTouchListener->setSwallowTouches(true);

    // 使用 lambda 实现 onTouchBegan 事件回调函数
    onScreenTouchListener->onTouchBegan = [](Touch* touch, Event* event){
        // 获取事件所绑定的 target 
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        // 获取当前点击点所在相对按钮的位置坐标
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        // 点击范围判断检测
        if (rect.containsPoint(locationInNode))
        {
            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);

            auto scene = Scene::create();
            MAIN_SCENE_OPENED_LAYER = MAIN_SCENE_LAYERS::MONSTERLAYER ; 
            MainScene *main_scene_layer = MainScene::create(); 
            scene->addChild(main_scene_layer) ;
            auto transitions = CCTransitionFade::create(1.0f, scene);
            Director::getInstance()->replaceScene( transitions );
            target->setOpacity(180);
            return true;
        }
        return false;
        };

    // 触摸移动时触发
    onScreenTouchListener->onTouchMoved = [](Touch* touch, Event* event){;};

    // 点击事件结束处理
    onScreenTouchListener->onTouchEnded = [=](Touch* touch, Event* event){;};

    // 添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(onScreenTouchListener, monster_box_back_button_sprite);

    currentHeight -= monster_box_back_button_sprite->getContentSize().height * 1.2; 

    currentPage = 0 ; 

    int counter = 0 ; 

    Menu *monsterMenu = Menu::create(); 

    for ( int i = 0 ; i < MONSTER_ROW_NUMBER ; i ++ )
    {
        if ( counter > gTotalMonsterAmount )    break ;
        for ( int j = 0 ; j < MONSTER_COLUMN_NUMBER ; j ++ )
        {   
            counter ++ ; 
            if ( counter > gTotalMonsterAmount )    break ; 
            CCString *monsterNameString = CCString::createWithFormat("Monster/%d.png", counter );
            MenuItemImage *monsterMenuImage = MenuItemImage::create(monsterNameString->getCString(),monsterNameString->getCString(),this,menu_selector(MonsterBoxLayer::FunctionHome));
            monsterMenuImage->setAnchorPoint(ccp(0,1));
            monsterMenuImage->setTag(counter);
            monsterMenuImage->setPosition(ccp(j*MONSTER_IMAGE_WIDTH*1.4,currentHeight- i*MONSTER_IMAGE_HEIGHT*1.2));

            monsterMenu->addChild(monsterMenuImage,1);
        }

    }

    monsterMenu->setPosition(ccp(0,0));
    monsterMenu->setAnchorPoint(ccp(0,0));
    this->addChild(monsterMenu,GAME_LEVEL) ;
    return true;
}



void MonsterBoxLayer::FunctionHome (cocos2d::Ref* pSender) 
{
    log("Can Clicked");

    auto monster = (MenuItemImage*) pSender;

    int monsterTag = monster->getTag() ;
    // log("TAG=%d",monsterTag);
     

    if ( gIsFromTeamEditToMonsterBox ) {
        gIsFromMonsterBoxToTeamEdit = true ;  
        gMonsterBoxClickedMonster = monsterTag ;
        // gTeamMonsterCode[gCurrentSelectedTeam][gCurrentSelectTeamMember] = monsterTag ;
        log("TEAMMOSTERCODE=%d gCurrentSelectedTeam=%d gCurrentSelectTeamMember = %d",gTeamMonsterCode[gCurrentSelectedTeam][gCurrentSelectTeamMember] , gCurrentSelectedTeam , gCurrentSelectTeamMember ) ;
        auto scene = Scene::create();
        MAIN_SCENE_OPENED_LAYER = MAIN_SCENE_LAYERS::TEAMEDITLAYER ; 
        MainScene *main_scene_layer = MainScene::create(); 
        scene->addChild(main_scene_layer) ;
        auto transitions = CCTransitionFade::create(2.0f, scene);
        Director::getInstance()->replaceScene( transitions );
    }
    log("monsterTag=%d",monster->getTag());

}

// bool MonsterBoxLayer::monsterOnTouchBegan(Touch* touch, Event  *event){
//     log("TOUCHBEGAN");
//     // touchStartLocation = touch->getLocation() ;
//     return true ; 
// }
// void MonsterBoxLayer::monsterOnTouchMoved(Touch* touch, Event  *event){
//     log("TOUCHMOVED");


// }
// void MonsterBoxLayer::monsterOnTouchEnded(Touch* touch, Event  *event){
//     log("TOUCHENDED");

//     // touchEndedLocation = touch->getLocation() ;


//     // auto monsterImageSprite = (Sprite*)this->getChildByTag(10);
//     // auto monsterNameSprite = (Sprite*)this->getChildByTag(11);
//     // auto monsterBaseSprite = (Sprite*)this->getChildByTag(12);
//     // auto monsterLevelSprite = (Sprite*)this->getChildByTag(13);

//     // auto monsterLeftSprite = (Sprite*)this->getChildByTag(1);
//     // auto monsterRightSprite = (Sprite*)this->getChildByTag(2);
//     // auto monsterUpSprite = (Sprite*)this->getChildByTag(3);
//     // auto monsterDownSprite = (Sprite*)this->getChildByTag(4);


//     // if ( touchEndedLocation.x < touchStartLocation.x )
//     // {
//     //     currentPage -= 1 ; 
//     //     if ( currentMonster < 0 ) currentMonster += 4 ; 

        

//     // }
//     // else if ( touchEndedLocation.x > touchStartLocation.x )
//     // {
//     //     currentPage += 1 ;
//     //     if ( currentMonster > 3 ) currentMonster -= 4 ;

        
//     // }
//     // else
//     //     log ("touchDirection = Not Moved");

//     // log ("CurrentMonster = %d" , currentMonster );

// }


