#include "MonsterLayer.h"
#include "AppMacros.h"
#include "AllClassLists.h"


Scene* MonsterLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MonsterLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MonsterLayer::init()
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
    
    auto monster_info_sprite = Sprite::create("MonsterLayer/Monster_Layer_Monster_Label.png") ;
    monster_info_sprite->setPosition(Vec2(currentWidth, currentHeight )) ;
    monster_info_sprite->setAnchorPoint(ccp(0,1));
    this->addChild(monster_info_sprite,GAME_LEVEL) ;

    
    currentHeight -= monster_info_sprite->getContentSize().height * 1.3 ; 
    
    // ScrollView* scrollView =  ScrollView::create() ; 
    // auto scroll_view_layer = Layer::create() ; 


    MenuItemImage *monster_menu_team_edit_button = MenuItemImage::create(
        "MonsterLayer/Monster_Layer_Team_Edit_Button.png",
        "MonsterLayer/Monster_Layer_Team_Edit_Button.png",
        this,
        menu_selector(MonsterLayer::TeamEdit));
    MenuItemImage *monster_menu_enhance_synthesize_button = MenuItemImage::create(
        "MonsterLayer/Monster_Layer_Enhance_Synthesize.png",
        "MonsterLayer/Monster_Layer_Enhance_Synthesize.png",
        this,
        menu_selector(MonsterLayer::FunctionMonster));
    MenuItemImage *monster_menu_evolution_synthesize_button = MenuItemImage::create(
        "MonsterLayer/Monster_Layer_Evolution_Synthesize_Button.png",
        "MonsterLayer/Monster_Layer_Evolution_Synthesize_Button.png",
        this,
        menu_selector(MonsterLayer::FunctionMonster));
    MenuItemImage *monster_menu_sale_button = MenuItemImage::create(
        "MonsterLayer/Monster_Layer_Sale_Button.png",
        "MonsterLayer/Monster_Layer_Sale_Button.png",
        this,
        menu_selector(MonsterLayer::FunctionMonster));
    MenuItemImage *monster_menu_monster_box_button = MenuItemImage::create(
        "MonsterLayer/Monster_Layer_Monster_Box.png",
        "MonsterLayer/Monster_Layer_Monster_Box.png",
        this,
        menu_selector(MonsterLayer::MonsterBox));
    MenuItemImage *monster_menu_evolution_item_button = MenuItemImage::create(
        "MonsterLayer/Monster_Layer_Evolution_Item_Button.png",
        "MonsterLayer/Monster_Layer_Evolution_Item_Button.png",
        this,
        menu_selector(MonsterLayer::FunctionMonster));
    MenuItemImage *monster_menu_monster_gallery_button = MenuItemImage::create(
        "MonsterLayer/Monster_Layer_Monster_Gallery.png",
        "MonsterLayer/Monster_Layer_Monster_Gallery.png",
        this,
        menu_selector(MonsterLayer::FunctionMonster));
    

    menuWidth = (visibleSize.width - monster_menu_team_edit_button->getContentSize().width )/ 2 ; 
    menuHeight = currentHeight ;

    // monster_menu_team_edit_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    // monster_menu_team_edit_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    monster_menu_team_edit_button->setPosition(ccp(menuWidth,menuHeight));
    monster_menu_team_edit_button->setAnchorPoint(ccp(0,1));

    menuHeight -= monster_menu_team_edit_button->getContentSize().height ; 
    // monster_menu_enhance_synthesize_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    // monster_menu_enhance_synthesize_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    monster_menu_enhance_synthesize_button->setPosition(ccp(menuWidth,menuHeight));
    monster_menu_enhance_synthesize_button->setAnchorPoint(ccp(0,1));

    menuHeight -= monster_menu_enhance_synthesize_button->getContentSize().height ; 
    // monster_menu_evolution_synthesize_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    // monster_menu_evolution_synthesize_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    monster_menu_evolution_synthesize_button->setPosition(ccp(menuWidth,menuHeight));
    monster_menu_evolution_synthesize_button->setAnchorPoint(ccp(0,1));

    menuHeight -= monster_menu_evolution_synthesize_button->getContentSize().height ; 
    // monster_menu_sale_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    // monster_menu_sale_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT));
    monster_menu_sale_button->setPosition(ccp(menuWidth,menuHeight));
    monster_menu_sale_button->setAnchorPoint(ccp(0,1));

    menuHeight -= monster_menu_sale_button->getContentSize().height ;
    // monster_menu_monster_box_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    // monster_menu_monster_box_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT)); 
    monster_menu_monster_box_button->setPosition(ccp(menuWidth,menuHeight));
    monster_menu_monster_box_button->setAnchorPoint(ccp(0,1));

    menuHeight -= monster_menu_monster_box_button->getContentSize().height ;
    // monster_menu_evolution_item_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    // monster_menu_evolution_item_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT)); 
    monster_menu_evolution_item_button->setPosition(ccp(menuWidth,menuHeight));
    monster_menu_evolution_item_button->setAnchorPoint(ccp(0,1));

    menuHeight -= monster_menu_evolution_item_button->getContentSize().height ;
    // monster_menu_monster_gallery_button->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    // monster_menu_monster_gallery_button->setScaleY((visibleSize.height/DESIGNED_HEIGHT)); 
    monster_menu_monster_gallery_button->setPosition(ccp(menuWidth,menuHeight));
    monster_menu_monster_gallery_button->setAnchorPoint(ccp(0,1));

    Menu *monsterMenu = Menu::create(
        monster_menu_team_edit_button,
        monster_menu_enhance_synthesize_button,
        monster_menu_evolution_synthesize_button,
        monster_menu_sale_button,
        monster_menu_monster_box_button,
        monster_menu_evolution_item_button,
        monster_menu_monster_gallery_button,
        NULL);
    
    // functionMenu->setScaleX((visibleSize.width/DESIGNED_WIDTH));
    // functionMenu->setScaleY((visibleSize.height/DESIGNED_HEIGHT)); 
    // monsterMenu->setAnchorPoint(ccp(1,1));
     // log("currentHeight=%f",currentHeight);
    monsterMenu->setPosition(Point(0,0)) ;
    // monsterMenu->setPosition(Director::getInstance()->convertToGL(Point(0,currentHeight))) ;


    this->addChild(monsterMenu,1);
    // scroll_view_layer->addChild(monsterMenu,GAME_LEVEL);
    // scroll_view_layer->setAnchorPoint(ccp(0,1));
    // scroll_view_layer->setPosition(ccp(0,currentHeight));

    // this->addChild(scroll_view_layer);


    return true;
}


void MonsterLayer::FunctionMonster(Ref* pSender)
{
    log("MonsterScene");
    // manager->toMonsterScene() ; 
}

void MonsterLayer::MonsterBox(Ref* pSender)
{
    log("MonsterBox");
    gIsFromTeamEditToMonsterBox = false ; 
    auto scene = Scene::create();
    MAIN_SCENE_OPENED_LAYER = 2 ; 
    MainScene *main_scene_layer = MainScene::create(); 
    scene->addChild(main_scene_layer) ;
    auto transitions = CCTransitionFade::create(2.0f, scene);
    Director::getInstance()->replaceScene( transitions );
    // manager->toMonsterScene() ; 
}
void MonsterLayer::TeamEdit(Ref* pSender)
{
    log("TeamEdit");
    gIsFromMonsterBoxToTeamEdit = false ; 
    auto scene = Scene::create();
    MAIN_SCENE_OPENED_LAYER = MAIN_SCENE_LAYERS::TEAMEDITLAYER ; 
    MainScene *main_scene_layer = MainScene::create(); 
    scene->addChild(main_scene_layer) ;
    auto transitions = CCTransitionFade::create(2.0f, scene);
    Director::getInstance()->replaceScene( transitions );
    // manager->toMonsterScene() ; 
}


