#include "MainScene.h"
#include "AppMacros.h"
#include "LayerLevelSelection.h"

Scene* MainScene::createScene()
{

    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);



    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //鏁版嵁璇诲彇

    ReadUserData() ; 

    //鑳屾櫙
    auto background_sprite = Sprite::create("MainScene/Main_Scene_Background.png");
    background_sprite->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    background_sprite->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    background_sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(background_sprite, BACKGROUND_LEVEL);
    
    float currentHeight = visibleSize.height ; 
    float currentWidth = 0 ; 
    float menuWidth = 0 ;
    float menuHeight = 0 ;

    //鐜╁濮撳悕
    currentHeight -= 75 ; 
    auto main_scene_upper_bar_sprite = Sprite::create("MainScene/Main_Scene_Upper_Bar.png") ;
    main_scene_upper_bar_sprite->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    main_scene_upper_bar_sprite->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    main_scene_upper_bar_sprite->setPosition(Vec2(currentWidth, currentHeight));
    main_scene_upper_bar_sprite->setAnchorPoint(ccp(0,1));
    this->addChild(main_scene_upper_bar_sprite,GAME_LEVEL) ;

    //鐜╁鐘舵�
    // currentHeight -= main_scene_upper_bar_sprite->getContentSize().height ; 
    // auto player_status_sprite = Sprite::create("MainScene/Main_Scene_Player_Status.png") ;
    // player_status_sprite->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    // player_status_sprite->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    // player_status_sprite->setPosition(Vec2(currentWidth, currentHeight ));
    // player_status_sprite->setAnchorPoint(ccp(0,1));
    // this->addChild(player_status_sprite,GAME_LEVEL) ;

    // currentHeight -= player_status_sprite->getContentSize().height ; 

    HomeLayer *home_layer = HomeLayer::create() ; //0
    LayerLevelSelection * level_selection_layer = LayerLevelSelection::create();//1
    MonsterLayer *monster_layer = MonsterLayer::create();   //2
    MonsterBoxLayer *monster_box_layer = MonsterBoxLayer::create() ; //3
    TeamEditLayer *team_edit_layer = TeamEditLayer::create() ; //4

    layer_manager = LayerMultiplex::create(
        home_layer,
        level_selection_layer,
        monster_layer,
        monster_box_layer,
        team_edit_layer,
        NULL);

    log("OpenedLayer=%d",MAIN_SCENE_OPENED_LAYER);
    layer_manager->switchTo(MAIN_SCENE_OPENED_LAYER);

    this->addChild(layer_manager,1);

  // 搴曢儴鍔熻兘鑿滃崟
    MenuItemImage *function_menu_home_button = MenuItemImage::create(
        "MainScene/Main_Scene_Function_Menu_Home_Button.png",
        "MainScene/Main_Scene_Function_Menu_Home_Button.png",
        this,
        menu_selector(MainScene::FunctionHome));
    MenuItemImage *function_menu_quest_button = MenuItemImage::create(
        "MainScene/Main_Scene_Function_Menu_Quest_Button.png",
        "MainScene/Main_Scene_Function_Menu_Quest_Button.png",
        this,
        menu_selector(MainScene::FunctionQuest));
    MenuItemImage *function_menu_monster_button = MenuItemImage::create(
        "MainScene/Main_Scene_Function_Menu_Monster_Button.png",
        "MainScene/Main_Scene_Function_Menu_Monster_Button.png",
        this,
        menu_selector(MainScene::FunctionMonster));
    MenuItemImage *function_menu_friend_button = MenuItemImage::create(
        "MainScene/Main_Scene_Function_Menu_Friend_Button.png",
        "MainScene/Main_Scene_Function_Menu_Friend_Button.png",
        this,
        menu_selector(MainScene::FunctionFriend));
    MenuItemImage *function_menu_shop_button = MenuItemImage::create(
        "MainScene/Main_Scene_Function_Menu_Shop_Button.png",
        "MainScene/Main_Scene_Function_Menu_Shop_Button.png",
        this,
        menu_selector(MainScene::FunctionShop));
    MenuItemImage *function_menu_option_button = MenuItemImage::create(
        "MainScene/Main_Scene_Function_Menu_Option_Button.png",
        "MainScene/Main_Scene_Function_Menu_Option_Button.png",
        this,
        menu_selector(MainScene::FunctionOption));

    menuWidth = 0 ; 
    menuHeight = 0 ;

    function_menu_home_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    function_menu_home_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    function_menu_home_button->setPosition(menuWidth,menuHeight);
    function_menu_home_button->setAnchorPoint(ccp(0,0));

    menuWidth += function_menu_home_button->getContentSize().width ; 
    function_menu_quest_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    function_menu_quest_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    function_menu_quest_button->setPosition(menuWidth,menuHeight);
    function_menu_quest_button->setAnchorPoint(ccp(0,0));

    menuWidth += function_menu_quest_button->getContentSize().width ; 
    function_menu_monster_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    function_menu_monster_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    function_menu_monster_button->setPosition(menuWidth,menuHeight);
    function_menu_monster_button->setAnchorPoint(ccp(0,0));

    menuWidth += function_menu_monster_button->getContentSize().width ; 
    function_menu_friend_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    function_menu_friend_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    function_menu_friend_button->setPosition(menuWidth,menuHeight);
    function_menu_friend_button->setAnchorPoint(ccp(0,0));

    menuWidth += function_menu_friend_button->getContentSize().width ;
    function_menu_shop_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    function_menu_shop_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT)); 
    function_menu_shop_button->setPosition(menuWidth,menuHeight);
    function_menu_shop_button->setAnchorPoint(ccp(0,0));

    menuWidth += function_menu_shop_button->getContentSize().width ;
    function_menu_option_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    function_menu_option_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT)); 
    function_menu_option_button->setPosition(menuWidth,menuHeight);
    function_menu_option_button->setAnchorPoint(ccp(0,0));

    Menu *functionMenu = Menu::create(
        function_menu_home_button,
        function_menu_quest_button,
        function_menu_monster_button,
        function_menu_friend_button,
        function_menu_shop_button,
        function_menu_option_button,
        NULL);

    // functionMenu->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    // functionMenu->setScaleY((visibleSize.height/DESIGNED_HEIGHT)); 
    functionMenu->setPosition(Vec2(0,0)) ;

    this->addChild(functionMenu,GAME_LEVEL);  

    return true;
}

void MainScene::FunctionHome(Ref* pSender)
{
    log("1");
    layer_manager->switchTo(MAIN_SCENE_LAYERS::HOMELAYER);
}
//Quest
void MainScene::FunctionQuest(Ref* pSender)
{
    log("QuestScene");
     layer_manager->switchTo(MAIN_SCENE_LAYERS::QUESTLAYER);
    // manager->toMonsterScene() ; 
}
void MainScene::FunctionMonster(Ref* pSender)
{
    log("MonsterScene");
    layer_manager->switchTo(MAIN_SCENE_LAYERS::MONSTERLAYER);
}
void MainScene::FunctionFriend(Ref* pSender)
{
    log("ShopScene");
    
}
//Option
void MainScene::FunctionShop(Ref* pSender)
{
    log("1");
}

void MainScene::FunctionOption(Ref* pSender)
{
    log("1");
}


void MainScene::ReadUserData()
{

    if(LoadBooleanFromXML("UserDataFlag",false) )
    {
        log ( "UserDataFlag=True");

        gTotalMonsterAmount = LoadIntegerFromXML("TotalMonsterAmount") ;


        gTeamMonsterCode[TEAM::A] [ ROULETTE_MONSTER_ORDER:: UP ] = LoadIntegerFromXML("TeamAMemberUp") ;
        gTeamMonsterCode[TEAM::A] [ ROULETTE_MONSTER_ORDER:: DOWN ] = LoadIntegerFromXML("TeamAMemberDown") ;
        gTeamMonsterCode[TEAM::A] [ ROULETTE_MONSTER_ORDER:: LEFT ] = LoadIntegerFromXML("TeamAMemberLeft") ;
        gTeamMonsterCode[TEAM::A] [ ROULETTE_MONSTER_ORDER:: RIGHT ] = LoadIntegerFromXML("TeamAMemberRight") ;

        gTeamMonsterCode[TEAM::B] [ ROULETTE_MONSTER_ORDER:: UP ] = LoadIntegerFromXML("TeamBMemberUp") ;
        gTeamMonsterCode[TEAM::B] [ ROULETTE_MONSTER_ORDER:: DOWN ] = LoadIntegerFromXML("TeamBMemberDown") ;
        gTeamMonsterCode[TEAM::B] [ ROULETTE_MONSTER_ORDER:: LEFT ] = LoadIntegerFromXML("TeamBMemberLeft") ;
        gTeamMonsterCode[TEAM::B] [ ROULETTE_MONSTER_ORDER:: RIGHT ] = LoadIntegerFromXML("TeamBMemberRight") ;

        gTeamMonsterCode[TEAM::C] [ ROULETTE_MONSTER_ORDER:: UP ] = LoadIntegerFromXML("TeamCMemberUp") ;
        gTeamMonsterCode[TEAM::C] [ ROULETTE_MONSTER_ORDER:: DOWN ] = LoadIntegerFromXML("TeamCMemberDown") ;
        gTeamMonsterCode[TEAM::C] [ ROULETTE_MONSTER_ORDER:: LEFT ] = LoadIntegerFromXML("TeamCMemberLeft") ;
        gTeamMonsterCode[TEAM::C] [ ROULETTE_MONSTER_ORDER:: RIGHT ] = LoadIntegerFromXML("TeamCMemberRight") ;

        gTeamMonsterCode[TEAM::D] [ ROULETTE_MONSTER_ORDER:: UP ] = LoadIntegerFromXML("TeamDMemberUp") ;
        gTeamMonsterCode[TEAM::D] [ ROULETTE_MONSTER_ORDER:: DOWN ] = LoadIntegerFromXML("TeamDMemberDown") ;
        gTeamMonsterCode[TEAM::D] [ ROULETTE_MONSTER_ORDER:: LEFT ] = LoadIntegerFromXML("TeamDMemberLeft") ;
        gTeamMonsterCode[TEAM::D] [ ROULETTE_MONSTER_ORDER:: RIGHT ] = LoadIntegerFromXML("TeamDMemberRight") ;

        gTeamMonsterCode[TEAM::E] [ ROULETTE_MONSTER_ORDER:: UP ] = LoadIntegerFromXML("TeamEMemberUp") ;
        gTeamMonsterCode[TEAM::E] [ ROULETTE_MONSTER_ORDER:: DOWN ] = LoadIntegerFromXML("TeamEMemberDown") ;
        gTeamMonsterCode[TEAM::E] [ ROULETTE_MONSTER_ORDER:: LEFT ] = LoadIntegerFromXML("TeamEMemberLeft") ;
        gTeamMonsterCode[TEAM::E] [ ROULETTE_MONSTER_ORDER:: RIGHT ] = LoadIntegerFromXML("TeamEMemberRight") ;

        
    }
    else
    {
        log ( "UserDataFlag=False");

        SaveIntegerToXML("TotalMonsterAmount",35);

        SaveIntegerToXML("TeamAMemberUp",10);
        SaveIntegerToXML("TeamAMemberDown",2);
        SaveIntegerToXML("TeamAMemberLeft",8);
        SaveIntegerToXML("TeamAMemberRight",4);

        SaveIntegerToXML("TeamBMemberUp",7);
        SaveIntegerToXML("TeamBMemberDown",8);
        SaveIntegerToXML("TeamBMemberLeft",6);
        SaveIntegerToXML("TeamBMemberRight",9);

        SaveIntegerToXML("TeamCMemberUp",10);
        SaveIntegerToXML("TeamCMemberDown",9);
        SaveIntegerToXML("TeamCMemberLeft",8);
        SaveIntegerToXML("TeamCMemberRight",2);

        SaveIntegerToXML("TeamDMemberUp",7);
        SaveIntegerToXML("TeamDMemberDown",4);
        SaveIntegerToXML("TeamDMemberLeft",6);
        SaveIntegerToXML("TeamDMemberRight",8);

        SaveIntegerToXML("TeamEMemberUp",3);
        SaveIntegerToXML("TeamEMemberDown",9);
        SaveIntegerToXML("TeamEMemberLeft",5);
        SaveIntegerToXML("TeamEMemberRight",1);

        
        SaveBooleanToXML("UserDataFlag", true);        
        FlushXML() ;    

        gTotalMonsterAmount = LoadIntegerFromXML("TotalMonsterAmount") ;


        gTeamMonsterCode[TEAM::A] [ ROULETTE_MONSTER_ORDER:: UP ] = LoadIntegerFromXML("TeamAMemberUp") ;
        gTeamMonsterCode[TEAM::A] [ ROULETTE_MONSTER_ORDER:: DOWN ] = LoadIntegerFromXML("TeamAMemberDown") ;
        gTeamMonsterCode[TEAM::A] [ ROULETTE_MONSTER_ORDER:: LEFT ] = LoadIntegerFromXML("TeamAMemberLeft") ;
        gTeamMonsterCode[TEAM::A] [ ROULETTE_MONSTER_ORDER:: RIGHT ] = LoadIntegerFromXML("TeamAMemberRight") ;

        gTeamMonsterCode[TEAM::B] [ ROULETTE_MONSTER_ORDER:: UP ] = LoadIntegerFromXML("TeamBMemberUp") ;
        gTeamMonsterCode[TEAM::B] [ ROULETTE_MONSTER_ORDER:: DOWN ] = LoadIntegerFromXML("TeamBMemberDown") ;
        gTeamMonsterCode[TEAM::B] [ ROULETTE_MONSTER_ORDER:: LEFT ] = LoadIntegerFromXML("TeamBMemberLeft") ;
        gTeamMonsterCode[TEAM::B] [ ROULETTE_MONSTER_ORDER:: RIGHT ] = LoadIntegerFromXML("TeamBMemberRight") ;

        gTeamMonsterCode[TEAM::C] [ ROULETTE_MONSTER_ORDER:: UP ] = LoadIntegerFromXML("TeamCMemberUp") ;
        gTeamMonsterCode[TEAM::C] [ ROULETTE_MONSTER_ORDER:: DOWN ] = LoadIntegerFromXML("TeamCMemberDown") ;
        gTeamMonsterCode[TEAM::C] [ ROULETTE_MONSTER_ORDER:: LEFT ] = LoadIntegerFromXML("TeamCMemberLeft") ;
        gTeamMonsterCode[TEAM::C] [ ROULETTE_MONSTER_ORDER:: RIGHT ] = LoadIntegerFromXML("TeamCMemberRight") ;

        gTeamMonsterCode[TEAM::D] [ ROULETTE_MONSTER_ORDER:: UP ] = LoadIntegerFromXML("TeamDMemberUp") ;
        gTeamMonsterCode[TEAM::D] [ ROULETTE_MONSTER_ORDER:: DOWN ] = LoadIntegerFromXML("TeamDMemberDown") ;
        gTeamMonsterCode[TEAM::D] [ ROULETTE_MONSTER_ORDER:: LEFT ] = LoadIntegerFromXML("TeamDMemberLeft") ;
        gTeamMonsterCode[TEAM::D] [ ROULETTE_MONSTER_ORDER:: RIGHT ] = LoadIntegerFromXML("TeamDMemberRight") ;

        gTeamMonsterCode[TEAM::E] [ ROULETTE_MONSTER_ORDER:: UP ] = LoadIntegerFromXML("TeamEMemberUp") ;
        gTeamMonsterCode[TEAM::E] [ ROULETTE_MONSTER_ORDER:: DOWN ] = LoadIntegerFromXML("TeamEMemberDown") ;
        gTeamMonsterCode[TEAM::E] [ ROULETTE_MONSTER_ORDER:: LEFT ] = LoadIntegerFromXML("TeamEMemberLeft") ;
        gTeamMonsterCode[TEAM::E] [ ROULETTE_MONSTER_ORDER:: RIGHT ] = LoadIntegerFromXML("TeamEMemberRight") ;


        
    }


}
