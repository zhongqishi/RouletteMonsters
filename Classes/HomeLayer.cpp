#include "HomeLayer.h"
#include "AppMacros.h"

USING_NS_CC;

Scene* HomeLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HomeLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HomeLayer::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    gettimeofday(&lastSwipe, NULL);

    auto team_edit_layer_roulette_round_sprite = Sprite::create("TeamEditLayer/Team_Edit_Layer_Roulette_Round.png") ;
    float team_edit_layer_roulette_round_sprite_width = visibleSize.width/2 ; 
    float team_edit_layer_roulette_round_sprite_height = 62;
    team_edit_layer_roulette_round_sprite->setPosition(Vec2(team_edit_layer_roulette_round_sprite_width, team_edit_layer_roulette_round_sprite_height )) ;
    team_edit_layer_roulette_round_sprite->setAnchorPoint(ccp(0.5,0.5));
    this->addChild(team_edit_layer_roulette_round_sprite,1) ;


    float team_edit_layer_roulette_center_sprite_height = team_edit_layer_roulette_round_sprite_height ; 
    float team_edit_layer_roulette_center_sprite_width = ( visibleSize.width ) / 2 ; 
    auto team_edit_layer_roulette_center_sprite = Sprite::create("TeamEditLayer/Team_Edit_Layer_Roulette_Center.png") ; 
    team_edit_layer_roulette_center_sprite->setPosition(Vec2(team_edit_layer_roulette_center_sprite_width, team_edit_layer_roulette_center_sprite_height )) ;
    team_edit_layer_roulette_center_sprite->setAnchorPoint(ccp(0.5,0.5));
    this->addChild(team_edit_layer_roulette_center_sprite,3) ;

    auto rouletteRoundCenter = Vec2(team_edit_layer_roulette_center_sprite_width,team_edit_layer_roulette_center_sprite_height);

    

    float team_edit_team_member_sprite_left_width = team_edit_layer_roulette_center_sprite_width ;
    float team_edit_team_member_sprite_left_height = team_edit_layer_roulette_center_sprite_height ; 
    auto team_edit_team_member_sprite_left = Sprite::create("TeamEditLayer/Team_Edit_Layer_Team_Member_Left.png") ; 
    team_edit_team_member_sprite_left->setPosition(Vec2(team_edit_team_member_sprite_left_width, team_edit_team_member_sprite_left_height )) ;
    team_edit_team_member_sprite_left->setTag(1);
    team_edit_team_member_sprite_left->setAnchorPoint(ccp(1,0.5));
    this->addChild(team_edit_team_member_sprite_left,1) ;

    float team_edit_team_member_sprite_right_height = team_edit_layer_roulette_center_sprite_height ; 
    float team_edit_team_member_sprite_right_width = team_edit_layer_roulette_center_sprite_width ;

    auto team_edit_team_member_sprite_right = Sprite::create("TeamEditLayer/Team_Edit_Layer_Team_Member_Right.png") ; 
    team_edit_team_member_sprite_right->setPosition(Vec2(team_edit_team_member_sprite_right_width, team_edit_team_member_sprite_right_height )) ;
    team_edit_team_member_sprite_right->setTag(2);
    team_edit_team_member_sprite_right->setAnchorPoint(ccp(0,0.5));
    this->addChild(team_edit_team_member_sprite_right,1) ;

    float team_edit_team_member_sprite_up_width = team_edit_layer_roulette_center_sprite_width ; 
    float team_edit_team_member_sprite_up_height = team_edit_layer_roulette_center_sprite_height ; 
    auto team_edit_team_member_sprite_up = Sprite::create("TeamEditLayer/Team_Edit_Layer_Team_Member_Up.png") ; 
    team_edit_team_member_sprite_up->setPosition(Vec2(team_edit_team_member_sprite_up_width, team_edit_team_member_sprite_up_height )) ;
    team_edit_team_member_sprite_up->setAnchorPoint(ccp(0.5,0));
    team_edit_team_member_sprite_up->setTag(3);
    this->addChild(team_edit_team_member_sprite_up,1) ;

    float team_edit_team_member_sprite_down_width = team_edit_layer_roulette_center_sprite_width ; 
    float team_edit_team_member_sprite_down_height = team_edit_layer_roulette_center_sprite_height ;

    auto team_edit_team_member_sprite_down = Sprite::create("TeamEditLayer/Team_Edit_Layer_Team_Member_Down.png") ; 
    team_edit_team_member_sprite_down->setPosition(Vec2(team_edit_team_member_sprite_down_width, team_edit_team_member_sprite_down_height )) ;
    team_edit_team_member_sprite_down->setTag(4);
    team_edit_team_member_sprite_down->setAnchorPoint(ccp(0.5,1));
    this->addChild(team_edit_team_member_sprite_down,1) ;


    auto current_monster_image_sprite = Sprite::create("HomeLayer/Home_Layer_Monster_Up.png") ;
    float current_monster_image_sprite_height =  446 ; 
    float current_monster_image_sprite_width =  visibleSize.width / 2 ; 
    current_monster_image_sprite->setPosition(Vec2(current_monster_image_sprite_width,current_monster_image_sprite_height));
    current_monster_image_sprite->setTag(10);
    current_monster_image_sprite->setAnchorPoint(ccp(0.5,0));
    this->addChild(current_monster_image_sprite,1) ;
    
    auto current_monster_name_sprite = Sprite::create("HomeLayer/Home_Layer_Monster_Up_Name.png") ;
    float current_monster_name_sprite_height =  1353 ; 
    float current_monster_name_sprite_width =  0 ; 
    current_monster_name_sprite->setPosition(Vec2(current_monster_name_sprite_width,current_monster_name_sprite_height));
    current_monster_name_sprite->setTag(11);
    current_monster_name_sprite->setAnchorPoint(ccp(0,0));
    this->addChild(current_monster_name_sprite,1) ;

    auto current_monster_base_sprite = Sprite::create("HomeLayer/Home_Layer_Monster_Up_Base.png") ;
    float current_monster_base_sprite_width =  visibleSize.width ; 
    float current_monster_base_sprite_height =  520 ; 
    current_monster_base_sprite->setPosition(Vec2(current_monster_base_sprite_width,current_monster_base_sprite_height));
    current_monster_base_sprite->setTag(12);
    current_monster_base_sprite->setAnchorPoint(ccp(1,0));
    this->addChild(current_monster_base_sprite,1) ;
    

    auto current_monster_level_sprite = Sprite::create("HomeLayer/Home_Layer_Monster_Support_Type.png") ;
    float current_monster_level_sprite_width =  67 ; 
    float current_monster_level_sprite_height =  1365 ; 
    current_monster_level_sprite->setPosition(Vec2(current_monster_level_sprite_width,current_monster_level_sprite_height));
    current_monster_level_sprite->setTag(13);
    current_monster_level_sprite->setAnchorPoint(ccp(0,0));
    this->addChild(current_monster_level_sprite,1) ;

    currentMonster = ROULETTE_MONSTER_ORDER::UP ; 


    monsterImageTexture[ROULETTE_MONSTER_ORDER::UP] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Up.png") ;
    monsterImageTexture[ROULETTE_MONSTER_ORDER::DOWN] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Down.png") ;
    monsterImageTexture[ROULETTE_MONSTER_ORDER::LEFT] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Left.png") ;
    monsterImageTexture[ROULETTE_MONSTER_ORDER::RIGHT] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Right.png") ;

    monsterNameTexture[ROULETTE_MONSTER_ORDER::UP] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Up_Name.png") ;
    monsterNameTexture[ROULETTE_MONSTER_ORDER::DOWN] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Down_Name.png") ;
    monsterNameTexture[ROULETTE_MONSTER_ORDER::LEFT] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Left_Name.png") ;
    monsterNameTexture[ROULETTE_MONSTER_ORDER::RIGHT] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Right_Name.png") ;

    monsterBaseTexture[ROULETTE_MONSTER_ORDER::UP] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Up_Base.png") ;
    monsterBaseTexture[ROULETTE_MONSTER_ORDER::DOWN] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Down_Base.png") ;
    monsterBaseTexture[ROULETTE_MONSTER_ORDER::LEFT] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Left_Base.png") ;
    monsterBaseTexture[ROULETTE_MONSTER_ORDER::RIGHT] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Right_Base.png") ;

    monsterLevelTexture[ROULETTE_MONSTER_ORDER::UP] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Support_Type.png") ;
    monsterLevelTexture[ROULETTE_MONSTER_ORDER::DOWN] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Attack_Type.png") ;
    monsterLevelTexture[ROULETTE_MONSTER_ORDER::LEFT] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Support_Type.png") ;
    monsterLevelTexture[ROULETTE_MONSTER_ORDER::RIGHT] = TextureCache::sharedTextureCache()->addImage("HomeLayer/Home_Layer_Monster_Attack_Type.png") ;


    // auto current_monster_level_label = Label::createWithTTF("Lv.100(辅助型)","Fonts/Yahei.ttf", 32);  
    // float current_monster_level_label_width =  67 ; 
    // float current_monster_level_label_height =  1365 ; 
    // current_monster_level_label->setPosition(ccp(current_monster_level_label_width,current_monster_level_label_height));  
    // current_monster_level_label->setAlignment(TextHAlignment::LEFT);  
    // current_monster_level_label->setAnchorPoint(Point(0.0f, 0.0f));  
    // this->addChild(current_monster_level_label,1);  
    // 
    // 
    // 
    // 
    rouletteRoundRect = Rect(0 , 186, visibleSize.width, 190);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();  
    auto rouletteRoundListener = EventListenerTouchOneByOne::create();
   //  // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    // team_edit_back_button_sprite_listener->setSwallowTouches(true);

   //  // 使用 lambda 实现 onTouchBegan 事件回调函数
    rouletteRoundListener->onTouchBegan = CC_CALLBACK_2(HomeLayer::rouletteRoundOnTouchBegan, this);

    // 触摸移动时触发
    rouletteRoundListener->onTouchMoved = CC_CALLBACK_2(HomeLayer::rouletteRoundOnTouchMoved, this);

    // 点击事件结束处理
    rouletteRoundListener->onTouchEnded = CC_CALLBACK_2(HomeLayer::rouletteRoundOnTouchEnded, this);

    // 添加监听器
    dispatcher->addEventListenerWithSceneGraphPriority(rouletteRoundListener, this);




    return true;
}

bool HomeLayer::rouletteRoundOnTouchBegan(Touch* touch, Event  *event){
    log("TOUCHBEGAN");
    touchStartLocation = touch->getLocation() ;
    gettimeofday(&currentSwipe,NULL) ;
    return true ; 
}
void HomeLayer::rouletteRoundOnTouchMoved(Touch* touch, Event  *event){
    log("TOUCHMOVED");


}
void HomeLayer::rouletteRoundOnTouchEnded(Touch* touch, Event  *event){
    log("TOUCHENDED");

    touchEndedLocation = touch->getLocation() ;
    if(currentSwipe.tv_sec - lastSwipe.tv_sec < 1 ) {
        log("Time<1") ;
            return ;
    }
    


    auto monsterImageSprite = (Sprite*)this->getChildByTag(10);
    auto monsterNameSprite = (Sprite*)this->getChildByTag(11);
    auto monsterBaseSprite = (Sprite*)this->getChildByTag(12);
    auto monsterLevelSprite = (Sprite*)this->getChildByTag(13);

    auto monsterLeftSprite = (Sprite*)this->getChildByTag(1);
    auto monsterRightSprite = (Sprite*)this->getChildByTag(2);
    auto monsterUpSprite = (Sprite*)this->getChildByTag(3);
    auto monsterDownSprite = (Sprite*)this->getChildByTag(4);


    if ( touchEndedLocation.x < touchStartLocation.x )
    {
        currentMonster -= 1 ; 
        if ( currentMonster < 0 ) currentMonster += 4 ; 

        monsterImageSprite->setTexture(monsterImageTexture[currentMonster]) ;
        monsterNameSprite->setTexture(monsterNameTexture[currentMonster]);
        monsterBaseSprite->setTexture(monsterBaseTexture[currentMonster]) ;
        monsterLevelSprite->setTexture(monsterLevelTexture[currentMonster]) ;

        monsterLeftSprite->runAction(RotateBy::create(0.5f,-90));
        monsterRightSprite->runAction(RotateBy::create(0.5f,-90));
        monsterUpSprite->runAction(RotateBy::create(0.5f,-90));
        monsterDownSprite->runAction(RotateBy::create(0.5f,-90));

    }
    else if ( touchEndedLocation.x > touchStartLocation.x )
    {
        currentMonster += 1 ;
        if ( currentMonster > 3 ) currentMonster -= 4 ;

        monsterImageSprite->setTexture(monsterImageTexture[currentMonster]) ;
        monsterNameSprite->setTexture(monsterNameTexture[currentMonster]);
        monsterBaseSprite->setTexture(monsterBaseTexture[currentMonster]) ;
        monsterLevelSprite->setTexture(monsterLevelTexture[currentMonster]) ;


        monsterLeftSprite->runAction(RotateBy::create(0.5,90));
        monsterRightSprite->runAction(RotateBy::create(0.5,90));
        monsterUpSprite->runAction(RotateBy::create(0.5,90));
        monsterDownSprite->runAction(RotateBy::create(0.5,90));
    }
    else
        log ("touchDirection = Not Moved");

    log ("CurrentMonster = %d" , currentMonster );

    gettimeofday(&lastSwipe,NULL) ;

}



