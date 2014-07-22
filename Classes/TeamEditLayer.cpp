#include "TeamEditLayer.h"
#include "MainScene.h"
#include "math.h"

#define PI 3.1415926


Scene* TeamEditLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool TeamEditLayer::init()
{
    
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

    if (gIsFromMonsterBoxToTeamEdit )
    {
        currentActiveTeam = gCurrentSelectedTeam ; 
    }
    else
    {
        currentActiveTeam = TEAM::A ; 
        gCurrentSelectedTeam = TEAM::A ; 
    }


    teamLabelTexture[TEAM::A][TEAM_STATUS::SELECTED] = TextureCache::sharedTextureCache()->addImage("TeamEditLayer/Team_Edit_Layer_Team_A_Active.png") ;  
    teamLabelTexture[TEAM::A][TEAM_STATUS::UNSELECTED] = TextureCache::sharedTextureCache()->addImage("TeamEditLayer/Team_Edit_Layer_Team_A_InActive.png") ;  
    teamLabelTexture[TEAM::B][TEAM_STATUS::SELECTED] = TextureCache::sharedTextureCache()->addImage("TeamEditLayer/Team_Edit_Layer_Team_B_Active.png") ;  
    teamLabelTexture[TEAM::B][TEAM_STATUS::UNSELECTED] = TextureCache::sharedTextureCache()->addImage("TeamEditLayer/Team_Edit_Layer_Team_B_InActive.png") ;  
    teamLabelTexture[TEAM::C][TEAM_STATUS::SELECTED] = TextureCache::sharedTextureCache()->addImage("TeamEditLayer/Team_Edit_Layer_Team_C_Active.png") ;  
    teamLabelTexture[TEAM::C][TEAM_STATUS::UNSELECTED] = TextureCache::sharedTextureCache()->addImage("TeamEditLayer/Team_Edit_Layer_Team_C_InActive.png") ;  
    teamLabelTexture[TEAM::D][TEAM_STATUS::SELECTED] = TextureCache::sharedTextureCache()->addImage("TeamEditLayer/Team_Edit_Layer_Team_D_Active.png") ;  
    teamLabelTexture[TEAM::D][TEAM_STATUS::UNSELECTED] = TextureCache::sharedTextureCache()->addImage("TeamEditLayer/Team_Edit_Layer_Team_D_InActive.png") ;  
    teamLabelTexture[TEAM::E][TEAM_STATUS::SELECTED] = TextureCache::sharedTextureCache()->addImage("TeamEditLayer/Team_Edit_Layer_Team_E_Active.png") ;  
    teamLabelTexture[TEAM::E][TEAM_STATUS::UNSELECTED] = TextureCache::sharedTextureCache()->addImage("TeamEditLayer/Team_Edit_Layer_Team_E_InActive.png") ;  

    for ( int i = 1 ; i <= 10 ; i ++ )
    {
        monsterTexture[i][ROULETTE_MONSTER_ORDER::UP]= TextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("TeamMemberMonster/%d/Team_Member_Monster_%d_Up.png",i,i)->getCString()) ;  
        monsterTexture[i][ROULETTE_MONSTER_ORDER::DOWN] = TextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("TeamMemberMonster/%d/Team_Member_Monster_%d_Down.png",i,i)->getCString()) ; 
        monsterTexture[i][ROULETTE_MONSTER_ORDER::LEFT] = TextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("TeamMemberMonster/%d/Team_Member_Monster_%d_Left.png",i,i)->getCString()) ; 
        monsterTexture[i][ROULETTE_MONSTER_ORDER::RIGHT] = TextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("TeamMemberMonster/%d/Team_Member_Monster_%d_Right.png",i,i)->getCString()) ; 
    }

    

    float team_edit_layer_back_button_sprite_width = currentWidth ; 
    float team_edit_layer_back_button_sprite_height = currentHeight ; 
    auto team_edit_layer_back_button_sprite = Sprite::create("TeamEditLayer/Team_Edit_Layer_Back_Button.png") ;
    team_edit_layer_back_button_sprite->setPosition(Vec2(currentWidth, currentHeight )) ;
    team_edit_layer_back_button_sprite->setAnchorPoint(ccp(0,1));
    team_edit_layer_back_button_sprite->setTag(100);
    this->addChild(team_edit_layer_back_button_sprite,2) ;

    log ("HEIGHT=%f",team_edit_layer_back_button_sprite_height - team_edit_layer_back_button_sprite->getContentSize().height);

    backButtonRect = Rect(0 , team_edit_layer_back_button_sprite_height - team_edit_layer_back_button_sprite->getContentSize().height, team_edit_layer_back_button_sprite->getContentSize().width, team_edit_layer_back_button_sprite->getContentSize().height) ;

    auto dispatcher = Director::getInstance()->getEventDispatcher();  
    auto team_edit_back_button_sprite_listener = EventListenerTouchOneByOne::create();
   //  // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    // team_edit_back_button_sprite_listener->setSwallowTouches(true);

   //  // 使用 lambda 实现 onTouchBegan 事件回调函数
    team_edit_back_button_sprite_listener->onTouchBegan = CC_CALLBACK_2(TeamEditLayer::backButtonOnTouchBegan, this);

    // 触摸移动时触发
    team_edit_back_button_sprite_listener->onTouchMoved = CC_CALLBACK_2(TeamEditLayer::backButtonOnTouchMoved, this);

    // 点击事件结束处理
    team_edit_back_button_sprite_listener->onTouchEnded = CC_CALLBACK_2(TeamEditLayer::backButtonOnTouchEnded, this);

    // 添加监听器
    dispatcher->addEventListenerWithSceneGraphPriority(team_edit_back_button_sprite_listener, team_edit_layer_back_button_sprite);


    
    auto team_edit_layer_roulette_round_sprite = Sprite::create("TeamEditLayer/Team_Edit_Layer_Roulette_Round.png") ;
    float team_edit_layer_roulette_round_sprite_width = ( visibleSize.width - team_edit_layer_roulette_round_sprite->getContentSize().width ) / 2 ; 
    float team_edit_layer_roulette_round_sprite_height = team_edit_layer_back_button_sprite_height - team_edit_layer_back_button_sprite->getContentSize().height *1.3; 
    team_edit_layer_roulette_round_sprite->setPosition(Vec2(team_edit_layer_roulette_round_sprite_width, team_edit_layer_roulette_round_sprite_height )) ;
    team_edit_layer_roulette_round_sprite->setAnchorPoint(ccp(0,1));
    this->addChild(team_edit_layer_roulette_round_sprite,1) ;


    float team_edit_layer_roulette_center_sprite_height = team_edit_layer_roulette_round_sprite_height - team_edit_layer_roulette_round_sprite->getContentSize().height / 2 ; 
    float team_edit_layer_roulette_center_sprite_width = ( visibleSize.width ) / 2 ; 
    auto team_edit_layer_roulette_center_sprite = Sprite::create("TeamEditLayer/Team_Edit_Layer_Roulette_Center.png") ; 
    team_edit_layer_roulette_center_sprite->setPosition(Vec2(team_edit_layer_roulette_center_sprite_width, team_edit_layer_roulette_center_sprite_height )) ;
    team_edit_layer_roulette_center_sprite->setAnchorPoint(ccp(0.5,0.5));
    this->addChild(team_edit_layer_roulette_center_sprite,3) ;

    rouletteRoundCenter = Vec2(team_edit_layer_roulette_center_sprite_width,team_edit_layer_roulette_center_sprite_height);

    Sprite* teamMemberSprite[4] ;

    float team_edit_team_member_sprite_left_width = team_edit_layer_roulette_center_sprite_width ;
    float team_edit_team_member_sprite_left_height = team_edit_layer_roulette_center_sprite_height ; 

    teamMemberSprite[ROULETTE_MONSTER_ORDER::LEFT] = Sprite::create(CCString::createWithFormat("TeamMemberMonster/%d/Team_Member_Monster_%d_Left.png",gTeamMonsterCode[gCurrentSelectedTeam][ROULETTE_MONSTER_ORDER:: LEFT],gTeamMonsterCode[gCurrentSelectedTeam][ROULETTE_MONSTER_ORDER:: LEFT])->getCString()) ;
    teamMemberLeftRect = Rect(team_edit_team_member_sprite_left_width - teamMemberSprite[ROULETTE_MONSTER_ORDER::LEFT]->getContentSize().width ,
        team_edit_team_member_sprite_left_height - teamMemberSprite[ROULETTE_MONSTER_ORDER::LEFT]->getContentSize().height / 2 ,
         teamMemberSprite[ROULETTE_MONSTER_ORDER::LEFT]->getContentSize().width, 
         teamMemberSprite[ROULETTE_MONSTER_ORDER::LEFT]->getContentSize().height ) ;
    teamMemberSprite[ROULETTE_MONSTER_ORDER::LEFT]->setPosition(Vec2(team_edit_team_member_sprite_left_width, team_edit_team_member_sprite_left_height )) ;
    teamMemberSprite[ROULETTE_MONSTER_ORDER::LEFT]->setTag(ROULETTE_MONSTER_ORDER::LEFT);
    teamMemberSprite[ROULETTE_MONSTER_ORDER::LEFT]->setAnchorPoint(ccp(1,0.5));
    this->addChild(teamMemberSprite[ROULETTE_MONSTER_ORDER::LEFT],2) ;

    float team_edit_team_member_sprite_right_height = team_edit_layer_roulette_center_sprite_height ; 
    float team_edit_team_member_sprite_right_width = team_edit_layer_roulette_center_sprite_width ;

    teamMemberSprite[ROULETTE_MONSTER_ORDER::RIGHT] = Sprite::create(CCString::createWithFormat("TeamMemberMonster/%d/Team_Member_Monster_%d_Right.png",gTeamMonsterCode[gCurrentSelectedTeam][ROULETTE_MONSTER_ORDER::RIGHT],gTeamMonsterCode[gCurrentSelectedTeam][ROULETTE_MONSTER_ORDER::RIGHT])->getCString()) ; 
    teamMemberRightRect = Rect(team_edit_team_member_sprite_left_width ,
        team_edit_team_member_sprite_right_height - teamMemberSprite[ROULETTE_MONSTER_ORDER::RIGHT]->getContentSize().height / 2 ,
         teamMemberSprite[ROULETTE_MONSTER_ORDER::RIGHT]->getContentSize().width, 
         teamMemberSprite[ROULETTE_MONSTER_ORDER::RIGHT]->getContentSize().height ) ;
    teamMemberSprite[ROULETTE_MONSTER_ORDER::RIGHT]->setPosition(Vec2(team_edit_team_member_sprite_right_width, team_edit_team_member_sprite_right_height )) ;
    teamMemberSprite[ROULETTE_MONSTER_ORDER::RIGHT]->setTag(ROULETTE_MONSTER_ORDER::RIGHT);
    teamMemberSprite[ROULETTE_MONSTER_ORDER::RIGHT]->setAnchorPoint(ccp(0,0.5));
    this->addChild(teamMemberSprite[ROULETTE_MONSTER_ORDER::RIGHT],2) ;

    float team_edit_team_member_sprite_up_width = team_edit_layer_roulette_center_sprite_width ; 
    float team_edit_team_member_sprite_up_height = team_edit_layer_roulette_center_sprite_height ; 
    teamMemberSprite[ROULETTE_MONSTER_ORDER::UP] = Sprite::create(CCString::createWithFormat("TeamMemberMonster/%d/Team_Member_Monster_%d_Up.png",gTeamMonsterCode[gCurrentSelectedTeam][ROULETTE_MONSTER_ORDER::UP],gTeamMonsterCode[gCurrentSelectedTeam][ROULETTE_MONSTER_ORDER::UP])->getCString()) ; 

    teamMemberUpRect = Rect(team_edit_team_member_sprite_up_width - teamMemberSprite[ROULETTE_MONSTER_ORDER::UP]->getContentSize().width / 2 ,
        team_edit_team_member_sprite_right_height ,
         teamMemberSprite[ROULETTE_MONSTER_ORDER::UP]->getContentSize().width, 
         teamMemberSprite[ROULETTE_MONSTER_ORDER::UP]->getContentSize().height ) ;

    teamMemberSprite[ROULETTE_MONSTER_ORDER::UP]->setPosition(Vec2(team_edit_team_member_sprite_up_width, team_edit_team_member_sprite_up_height )) ;
    teamMemberSprite[ROULETTE_MONSTER_ORDER::UP]->setAnchorPoint(ccp(0.5,0));
    teamMemberSprite[ROULETTE_MONSTER_ORDER::UP]->setTag(ROULETTE_MONSTER_ORDER::UP);
    this->addChild(teamMemberSprite[ROULETTE_MONSTER_ORDER::UP],2) ;

    float team_edit_team_member_sprite_down_width = team_edit_layer_roulette_center_sprite_width ; 
    float team_edit_team_member_sprite_down_height = team_edit_layer_roulette_center_sprite_height ;

    teamMemberSprite[ROULETTE_MONSTER_ORDER::DOWN] = Sprite::create(CCString::createWithFormat("TeamMemberMonster/%d/Team_Member_Monster_%d_Down.png",gTeamMonsterCode[gCurrentSelectedTeam][ROULETTE_MONSTER_ORDER::DOWN],gTeamMonsterCode[gCurrentSelectedTeam][ROULETTE_MONSTER_ORDER::DOWN])->getCString()) ; 

    teamMemberDownRect = Rect(team_edit_team_member_sprite_down_width - teamMemberSprite[ROULETTE_MONSTER_ORDER::DOWN]->getContentSize().width / 2,
        team_edit_team_member_sprite_right_height - teamMemberSprite[ROULETTE_MONSTER_ORDER::DOWN]->getContentSize().height,
         teamMemberSprite[ROULETTE_MONSTER_ORDER::DOWN]->getContentSize().width, 
         teamMemberSprite[ROULETTE_MONSTER_ORDER::DOWN]->getContentSize().height ) ;

    teamMemberSprite[ROULETTE_MONSTER_ORDER::DOWN]->setPosition(Vec2(team_edit_team_member_sprite_down_width, team_edit_team_member_sprite_down_height )) ;
    teamMemberSprite[ROULETTE_MONSTER_ORDER::DOWN]->setTag(ROULETTE_MONSTER_ORDER::DOWN);
    teamMemberSprite[ROULETTE_MONSTER_ORDER::DOWN]->setAnchorPoint(ccp(0.5,1));
    this->addChild(teamMemberSprite[ROULETTE_MONSTER_ORDER::DOWN],2) ;

    // log("gTeamMonsterCode=%d",gTeamMonsterCode[gCurrentSelectedTeam][gCurrentSelectTeamMember]);
    if (gIsFromMonsterBoxToTeamEdit )
    {
         teamMemberSprite[gCurrentSelectTeamMember]->setTexture(monsterTexture[gMonsterBoxClickedMonster][gCurrentSelectTeamMember]) ;
         gTeamMonsterCode[gCurrentSelectedTeam][gCurrentSelectTeamMember] = gMonsterBoxClickedMonster ;
         CCString *XMLName ; 
        if(gCurrentSelectTeamMember == ROULETTE_MONSTER_ORDER::UP){
            XMLName = CCString::createWithFormat("Team%cMemberUp",65+gCurrentSelectedTeam) ;
        }
        if(gCurrentSelectTeamMember == ROULETTE_MONSTER_ORDER::DOWN){
            XMLName = CCString::createWithFormat("Team%cMemberDown",65+gCurrentSelectedTeam) ;
        }
        if(gCurrentSelectTeamMember == ROULETTE_MONSTER_ORDER::LEFT){
            XMLName = CCString::createWithFormat("Team%cMemberLeft",65+gCurrentSelectedTeam) ;
        }
        if(gCurrentSelectTeamMember == ROULETTE_MONSTER_ORDER::RIGHT){
            XMLName = CCString::createWithFormat("Team%cMemberRight",65+gCurrentSelectedTeam) ;
        }
         // log("XMLNAME=%s",XMLName->getCString());
         SaveIntegerToXML(XMLName->getCString(),gMonsterBoxClickedMonster) ;
         FlushXML() ; 
         // SaveIntegerToXML("TeamBMemberUp",7);
         // log("gIsFromMonsterBoxToTeamEdit=TRUE gCurrentSelectTeamMember=%d gTeamMonsterCode=%d gCurrentSelectedTeam=%d",gCurrentSelectTeamMember,gTeamMonsterCode[gCurrentSelectedTeam][gCurrentSelectTeamMember],gCurrentSelectedTeam);
    }
    else
    {
        log("gIsFromMonsterBoxToTeamEdit=FALSE");
    }


    auto teamMemberListener = EventListenerTouchOneByOne::create();
   //  // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    teamMemberListener->setSwallowTouches(false);

   //  // 使用 lambda 实现 onTouchBegan 事件回调函数
    teamMemberListener->onTouchBegan = CC_CALLBACK_2(TeamEditLayer::teamMemberOnTouchBegan, this);

    // 触摸移动时触发
    teamMemberListener->onTouchMoved = CC_CALLBACK_2(TeamEditLayer::teamMemberOnTouchMoved, this);

    // 点击事件结束处理
    teamMemberListener->onTouchEnded = CC_CALLBACK_2(TeamEditLayer::teamMemberOnTouchEnded, this);


    dispatcher->addEventListenerWithSceneGraphPriority(teamMemberListener, teamMemberSprite[ROULETTE_MONSTER_ORDER::LEFT]);
    dispatcher->addEventListenerWithSceneGraphPriority(teamMemberListener->clone(), teamMemberSprite[ROULETTE_MONSTER_ORDER::RIGHT]);
    dispatcher->addEventListenerWithSceneGraphPriority(teamMemberListener->clone(), teamMemberSprite[ROULETTE_MONSTER_ORDER::UP]);
    dispatcher->addEventListenerWithSceneGraphPriority(teamMemberListener->clone(), teamMemberSprite[ROULETTE_MONSTER_ORDER::DOWN]);

    
     
    Sprite* teamLabelSprite [ 5 ] ;
    float team_label_width = 18 , team_label_height = MAIN_SCENE_LAYER_BOTTOM_HEIGHT ;
    for ( int i = 0 ; i < 5 ; i ++ )
    {

        teamLabelSprite [ i ] = Sprite::create("TeamEditLayer/Team_Edit_Layer_Team_A_Active.png") ; 
        teamLabelSprite [ i ]->setTag(11 + i);
        teamLabelSprite [ i ]->setAnchorPoint(ccp(0,0));
        teamLabelSprite [ i ] ->setPosition(Vec2(team_label_width,team_label_height)) ;
        int z_position  ; 
        if ( i == currentActiveTeam )
        {
            z_position = 2 ; 
            teamLabelSprite[ i ]->setTexture(teamLabelTexture[i][TEAM_STATUS::SELECTED]);
        }
        else
        {
            z_position = 1 ; 
            teamLabelSprite[ i ]->setTexture(teamLabelTexture[i][TEAM_STATUS::UNSELECTED]);
        }
        
        this->addChild(teamLabelSprite [ i ],z_position) ;
    }


    auto team_edit_layer_team_info_listener = EventListenerTouchOneByOne::create();
   //  // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    team_edit_layer_team_info_listener->setSwallowTouches(false);

   //  // 使用 lambda 实现 onTouchBegan 事件回调函数
    team_edit_layer_team_info_listener->onTouchBegan = CC_CALLBACK_2(TeamEditLayer::teamInfoOnTouchBegan, this);

    // 触摸移动时触发
    team_edit_layer_team_info_listener->onTouchMoved = CC_CALLBACK_2(TeamEditLayer::teamInfoOnTouchMoved, this);

    // 点击事件结束处理
    team_edit_layer_team_info_listener->onTouchEnded = CC_CALLBACK_2(TeamEditLayer::teamInfoOnTouchEnded, this);

    // 添加监听器
    

    team_info_label_width = 209 ;team_info_label_height = 61 ;
    team_info_label_x = 18 ; team_info_label_y = 370 ; 

    teamARect = Rect(team_info_label_x + team_info_label_width * 0 , team_info_label_y, team_info_label_width, team_info_label_height);
    teamBRect = Rect(team_info_label_x + team_info_label_width * 1, team_info_label_y, team_info_label_width, team_info_label_height);
    teamCRect = Rect(team_info_label_x + team_info_label_width * 2, team_info_label_y, team_info_label_width, team_info_label_height);
    teamDRect = Rect(team_info_label_x + team_info_label_width * 3, team_info_label_y, team_info_label_width, team_info_label_height);
    teamERect = Rect(team_info_label_x + team_info_label_width * 4, team_info_label_y, team_info_label_width, team_info_label_height);

    dispatcher->addEventListenerWithSceneGraphPriority(team_edit_layer_team_info_listener, teamLabelSprite[TEAM::A]);
    dispatcher->addEventListenerWithSceneGraphPriority(team_edit_layer_team_info_listener->clone(), teamLabelSprite[TEAM::B]);
    dispatcher->addEventListenerWithSceneGraphPriority(team_edit_layer_team_info_listener->clone(), teamLabelSprite[TEAM::C]);
    dispatcher->addEventListenerWithSceneGraphPriority(team_edit_layer_team_info_listener->clone(), teamLabelSprite[TEAM::D]);
    dispatcher->addEventListenerWithSceneGraphPriority(team_edit_layer_team_info_listener->clone(), teamLabelSprite[TEAM::E]);
    

    



    return true;
}

bool TeamEditLayer::rouletteRoundOnTouchBegan(Touch* touch, Event  *event){
    // log("TOUCHBEGAN");
    // touchStartLocation = touch->getLocation() ;
    return true ; 
}
void TeamEditLayer::rouletteRoundOnTouchMoved(Touch* touch, Event  *event){
    // log("TOUCHMOVED");
    // auto sprite_left = this->getChildByTag(1);
    // auto sprite_right = this->getChildByTag(2);
    // auto sprite_up = this->getChildByTag(3);
    // auto sprite_down = this->getChildByTag(4);

    // touchMovedLocation = touch->getLocation() ; 

    // auto x1 = rouletteRoundCenter.x , y1 = rouletteRoundCenter.y ,
    //     x2 = touchStartLocation.x , y2 = touchStartLocation.y , 
    //     x3 = touchMovedLocation.x , y3 = touchMovedLocation.y ;

    // if ( touchMovedLocation != touchStartLocation )
    // {
    //     // auto theta = acos ( ( ( x3 - x1 ) * ( x2 - x1 ) + ( y3 - y1 ) * ( y2 - y1 ) ) / ( sqrt ( ( x2 - x1 ) * ( x2 - x1 ) + ( y2 - y1 ) * ( y2 - y1 ) ) * sqrt ( ( x3 - x1 ) * ( x3 - x1 ) + ( y3 - y1 ) * ( y3 - y1 ) ) ) ) / ( 2 * PI ) * 360; 

    //     // log ( "theta = %f" , theta ) ;

    //     sprite_left->runAction(RotateBy::create(0.0f,10));
    //     sprite_right->runAction(RotateBy::create(0.0f,10));
    //     sprite_up->runAction(RotateBy::create(0.0f,10));
    //     sprite_down->runAction(RotateBy::create(0.0f,10));

    //     touchStartLocation = touchMovedLocation ; 

    // }


}
void TeamEditLayer::rouletteRoundOnTouchEnded(Touch* touch, Event  *event){
    // log("TOUCHENDED");
}


bool TeamEditLayer::teamInfoOnTouchBegan(Touch* touch, Event  *event){
    // log("TOUCHBEGAN");
    // touchStartLocation = touch->getLocation() ;
    return true ; 
}
void TeamEditLayer::teamInfoOnTouchMoved(Touch* touch, Event  *event){
    // log("TOUCHMOVED");
}
void TeamEditLayer::teamInfoOnTouchEnded(Touch* touch, Event  *event){
    // log("TOUCHENDED");

    Point touchPoint = convertTouchToNodeSpace ( touch ) ;

    // log("touchPoint:%f,%f",touchPoint.x,touchPoint.y);

    auto teamASprite = (Sprite*)this->getChildByTag(11);
    auto teamBSprite = (Sprite*)this->getChildByTag(12);
    auto teamCSprite = (Sprite*)this->getChildByTag(13);
    auto teamDSprite = (Sprite*)this->getChildByTag(14);
    auto teamESprite = (Sprite*)this->getChildByTag(15);

    auto monsterUpSprite = (Sprite*)this->getChildByTag(ROULETTE_MONSTER_ORDER::UP);
    auto monsterDownSprite = (Sprite*)this->getChildByTag(ROULETTE_MONSTER_ORDER::DOWN);
    auto monsterLeftSprite = (Sprite*)this->getChildByTag(ROULETTE_MONSTER_ORDER::LEFT);
    auto monsterRightSprite = (Sprite*)this->getChildByTag(ROULETTE_MONSTER_ORDER::RIGHT);

    if(teamARect.containsPoint(touchPoint) && currentActiveTeam != TEAM::A)
    {
        log("team_label_touch_A") ;
        teamASprite->setTexture(teamLabelTexture[TEAM::A][TEAM_STATUS::SELECTED]);
        teamBSprite->setTexture(teamLabelTexture[TEAM::B][TEAM_STATUS::UNSELECTED]);
        teamCSprite->setTexture(teamLabelTexture[TEAM::C][TEAM_STATUS::UNSELECTED]);
        teamDSprite->setTexture(teamLabelTexture[TEAM::D][TEAM_STATUS::UNSELECTED]);
        teamESprite->setTexture(teamLabelTexture[TEAM::E][TEAM_STATUS::UNSELECTED]);
        monsterUpSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::A][ROULETTE_MONSTER_ORDER::UP]][ROULETTE_MONSTER_ORDER::UP]);
        monsterDownSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::A][ROULETTE_MONSTER_ORDER::DOWN]][ROULETTE_MONSTER_ORDER::DOWN]);
        monsterLeftSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::A][ROULETTE_MONSTER_ORDER::LEFT]][ROULETTE_MONSTER_ORDER::LEFT]);
        monsterRightSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::A][ROULETTE_MONSTER_ORDER::RIGHT]][ROULETTE_MONSTER_ORDER::RIGHT]);
        this->reorderChild(teamASprite,2);
        this->reorderChild(teamBSprite,1);
        this->reorderChild(teamCSprite,1);
        this->reorderChild(teamDSprite,1);
        this->reorderChild(teamESprite,1);
        currentActiveTeam = TEAM::A ; 
        gCurrentSelectedTeam = TEAM::A ;
    }
    if(teamBRect.containsPoint(touchPoint) && currentActiveTeam != TEAM::B )
    {
        log("team_label_touch_B") ;
        teamASprite->setTexture(teamLabelTexture[TEAM::A][TEAM_STATUS::UNSELECTED]);
        teamBSprite->setTexture(teamLabelTexture[TEAM::B][TEAM_STATUS::SELECTED]);
        teamCSprite->setTexture(teamLabelTexture[TEAM::C][TEAM_STATUS::UNSELECTED]);
        teamDSprite->setTexture(teamLabelTexture[TEAM::D][TEAM_STATUS::UNSELECTED]);
        teamESprite->setTexture(teamLabelTexture[TEAM::E][TEAM_STATUS::UNSELECTED]);
        monsterUpSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::B][ROULETTE_MONSTER_ORDER::UP]][ROULETTE_MONSTER_ORDER::UP]);
        monsterDownSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::B][ROULETTE_MONSTER_ORDER::DOWN]][ROULETTE_MONSTER_ORDER::DOWN]);
        monsterLeftSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::B][ROULETTE_MONSTER_ORDER::LEFT]][ROULETTE_MONSTER_ORDER::LEFT]);
        monsterRightSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::B][ROULETTE_MONSTER_ORDER::RIGHT]][ROULETTE_MONSTER_ORDER::RIGHT]);
        this->reorderChild(teamASprite,1);
        this->reorderChild(teamBSprite,2);
        this->reorderChild(teamCSprite,1);
        this->reorderChild(teamDSprite,1);
        this->reorderChild(teamESprite,1);
        currentActiveTeam = TEAM::B ; 
        gCurrentSelectedTeam = TEAM::B ;
    }
    if(teamCRect.containsPoint(touchPoint) && currentActiveTeam != TEAM::C )
    {
        log("team_label_touch_C") ;
        teamASprite->setTexture(teamLabelTexture[TEAM::A][TEAM_STATUS::UNSELECTED]);
        teamBSprite->setTexture(teamLabelTexture[TEAM::B][TEAM_STATUS::UNSELECTED]);
        teamCSprite->setTexture(teamLabelTexture[TEAM::C][TEAM_STATUS::SELECTED]);
        teamDSprite->setTexture(teamLabelTexture[TEAM::D][TEAM_STATUS::UNSELECTED]);
        teamESprite->setTexture(teamLabelTexture[TEAM::E][TEAM_STATUS::UNSELECTED]);
        monsterUpSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::C][ROULETTE_MONSTER_ORDER::UP]][ROULETTE_MONSTER_ORDER::UP]);
        monsterDownSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::C][ROULETTE_MONSTER_ORDER::DOWN]][ROULETTE_MONSTER_ORDER::DOWN]);
        monsterLeftSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::C][ROULETTE_MONSTER_ORDER::LEFT]][ROULETTE_MONSTER_ORDER::LEFT]);
        monsterRightSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::C][ROULETTE_MONSTER_ORDER::RIGHT]][ROULETTE_MONSTER_ORDER::RIGHT]);
        this->reorderChild(teamASprite,1);
        this->reorderChild(teamBSprite,1);
        this->reorderChild(teamCSprite,2);
        this->reorderChild(teamDSprite,1);
        this->reorderChild(teamESprite,1);
        currentActiveTeam = TEAM::C ; 
        gCurrentSelectedTeam = TEAM::C ; 
    }
    if(teamDRect.containsPoint(touchPoint) && currentActiveTeam != TEAM::D )
    {
        log("team_label_touch_D") ;
        teamASprite->setTexture(teamLabelTexture[TEAM::A][TEAM_STATUS::UNSELECTED]);
        teamBSprite->setTexture(teamLabelTexture[TEAM::B][TEAM_STATUS::UNSELECTED]);
        teamCSprite->setTexture(teamLabelTexture[TEAM::C][TEAM_STATUS::UNSELECTED]);
        teamDSprite->setTexture(teamLabelTexture[TEAM::D][TEAM_STATUS::SELECTED]);
        teamESprite->setTexture(teamLabelTexture[TEAM::E][TEAM_STATUS::UNSELECTED]);
        monsterUpSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::D][ROULETTE_MONSTER_ORDER::UP]][ROULETTE_MONSTER_ORDER::UP]);
        monsterDownSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::D][ROULETTE_MONSTER_ORDER::DOWN]][ROULETTE_MONSTER_ORDER::DOWN]);
        monsterLeftSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::D][ROULETTE_MONSTER_ORDER::LEFT]][ROULETTE_MONSTER_ORDER::LEFT]);
        monsterRightSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::D][ROULETTE_MONSTER_ORDER::RIGHT]][ROULETTE_MONSTER_ORDER::RIGHT]);
        this->reorderChild(teamASprite,1);
        this->reorderChild(teamBSprite,1);
        this->reorderChild(teamCSprite,1);
        this->reorderChild(teamDSprite,2);
        this->reorderChild(teamESprite,1);
        currentActiveTeam = TEAM::D ; 
        gCurrentSelectedTeam = TEAM::D ; 
    }
    if(teamERect.containsPoint(touchPoint) && currentActiveTeam != TEAM::E )
    {
        log("team_label_touch_E") ;
        teamASprite->setTexture(teamLabelTexture[TEAM::A][TEAM_STATUS::UNSELECTED]);
        teamBSprite->setTexture(teamLabelTexture[TEAM::B][TEAM_STATUS::UNSELECTED]);
        teamCSprite->setTexture(teamLabelTexture[TEAM::C][TEAM_STATUS::UNSELECTED]);
        teamDSprite->setTexture(teamLabelTexture[TEAM::D][TEAM_STATUS::UNSELECTED]);
        teamESprite->setTexture(teamLabelTexture[TEAM::E][TEAM_STATUS::SELECTED]);
        monsterUpSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::E][ROULETTE_MONSTER_ORDER::UP]][ROULETTE_MONSTER_ORDER::UP]);
        monsterDownSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::E][ROULETTE_MONSTER_ORDER::DOWN]][ROULETTE_MONSTER_ORDER::DOWN]);
        monsterLeftSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::E][ROULETTE_MONSTER_ORDER::LEFT]][ROULETTE_MONSTER_ORDER::LEFT]);
        monsterRightSprite->setTexture(monsterTexture[gTeamMonsterCode[TEAM::E][ROULETTE_MONSTER_ORDER::RIGHT]][ROULETTE_MONSTER_ORDER::RIGHT]);
        this->reorderChild(teamASprite,1);
        this->reorderChild(teamBSprite,1);
        this->reorderChild(teamCSprite,1);
        this->reorderChild(teamDSprite,1);
        this->reorderChild(teamESprite,2);
        currentActiveTeam = TEAM::E ; 
        gCurrentSelectedTeam = TEAM::E ;
    }

    

}

bool TeamEditLayer::backButtonOnTouchBegan(Touch* touch, Event  *event){
    // log("TOUCHBEGAN");

    return true ; 
}
void TeamEditLayer::backButtonOnTouchMoved(Touch* touch, Event  *event){
    // log("TOUCHMoved");
}
void TeamEditLayer::backButtonOnTouchEnded(Touch* touch, Event  *event){

    // log("TOUCHENDED");

    auto backButtonSprite = (Sprite*)this->getChildByTag(100);

    Point touchPoint = convertTouchToNodeSpace ( touch ) ;

    // log("backButton") ;

    if(backButtonRect.containsPoint(touchPoint))
    {
        auto scene = Scene::create();
        MAIN_SCENE_OPENED_LAYER = MAIN_SCENE_LAYERS::MONSTERLAYER ; 
        MainScene *main_scene_layer = MainScene::create(); 
        scene->addChild(main_scene_layer) ;
        auto transitions = CCTransitionFade::create(2.0f, scene);
        Director::getInstance()->replaceScene( transitions );
        backButtonSprite->setOpacity(180);

    }

}

bool TeamEditLayer::teamMemberOnTouchBegan(Touch* touch, Event  *event){
    // log("TEAMMEMBERBEGAN");

    return true ; 
}
void TeamEditLayer::teamMemberOnTouchMoved(Touch* touch, Event  *event){
    // log("TEAMMEMBERMOVED");
}
void TeamEditLayer::teamMemberOnTouchEnded(Touch* touch, Event  *event){

    // log("TEAMMEMBERENDED");

    Point touchPoint = convertTouchToNodeSpace ( touch ) ;

    bool isTeamMemberTouched = false ; 

    if(teamMemberUpRect.containsPoint(touchPoint))
    {
        log("TEAMUpENDED");
        isTeamMemberTouched = true ; 
        gCurrentSelectTeamMember = ROULETTE_MONSTER_ORDER::UP ; 

    }
    if(teamMemberDownRect.containsPoint(touchPoint))
    {
        log("TEAMDownENDED");
        isTeamMemberTouched = true ; 
        gCurrentSelectTeamMember = ROULETTE_MONSTER_ORDER::DOWN ; 
    }
    if(teamMemberLeftRect.containsPoint(touchPoint))
    {
        log("TEAMLeftENDED");
        isTeamMemberTouched = true ; 
        gCurrentSelectTeamMember = ROULETTE_MONSTER_ORDER::LEFT ; 
    }
    if(teamMemberRightRect.containsPoint(touchPoint))
    {
        log("TEAMRightENDED");
        isTeamMemberTouched = true ; 
        gCurrentSelectTeamMember = ROULETTE_MONSTER_ORDER::RIGHT ; 
    }

    if ( isTeamMemberTouched )
    {
        gIsFromTeamEditToMonsterBox = true ; 
        auto scene = Scene::create();
        MAIN_SCENE_OPENED_LAYER = MAIN_SCENE_LAYERS::MONSTERBOXLAYER ; 
        MainScene *main_scene_layer = MainScene::create(); 
        scene->addChild(main_scene_layer) ;
        auto transitions = CCTransitionFade::create(1.0f, scene);
        Director::getInstance()->replaceScene( transitions );
    }


}

