# define Math_PI           3.14159265358979323846  /* pi */
# define Level_0           0
# define Level_1           1
# define Level_2           2
# define Level_3           3
# define Level_4           4
# define Level_5           5
# define circlesToTurn     4
# define circleTurnTime    2

#include "SceneGame.h"
#include "SceneMainMenu.h"
#include "UtilFadeRotateRy.h"
#include "UtilBeingAttack.h"
#include "UtilAttackMove.h"
#include "Monster.h"
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>  

USING_NS_CC;

float scene_game_angle_rate = -5.0f;
float scene_game_scalNow,scene_game_scalZhuanPan;
float scene_game_scale_monster_bg;
float scene_game_scale_player_hp;
float scene_game_scale_monster1_hp;
float scene_game_scale_monster2_hp;
float scene_game_scale_monster3_hp;
float scene_game_scale_monster4_hp;
float scene_game_scale_monster5_hp;
float scene_game_zhuanpan_action_time = 3.2f;
float scene_game_position[2];
float scene_game_demage_fiex=1;
int scene_game_damage_counter = 0;
int scene_game_streak_radius=255;
int player_attack_counter=0;

/*计时器.....................*/
int scene_game_accumulated_timer = 0;
int scene_game_action_finished_timer = 0;
int scene_game_scene_timer=0;
int scene_game_attack_effect_timer = 0;
int scene_game_enemy_timer = 0;
int scene_game_boss_alert_timer = 0;
/*...........................*/
int scene_game_zhuanpan_center_level[4] = {4,3,2,1};
bool scene_game_bool_player_turn = false;
bool scene_game_bool_touched = false;
bool scene_game_bool_special_attack = false;
bool scene_game_bool_sprial_burst_menu_showed = false;

std::string spiral_number[] = {"","1","2","3","4","5","6","7","8"};
std::string string_light = "light";
std::string string_nolight = "noLight";



int skillbox_type[8] = {1,4,1,3,2,1,3,2};

enum
{	
	scene_game_int_tag_number_sprite_pins,
	scene_game_int_tag_number_sprite_pin_bg,
	scene_game_int_tag_number_sprite_pins_spiral_burst1,
	scene_game_int_tag_number_sprite_pins_spiral_burst2,
	scene_game_int_tag_number_sprite_pins_spiral_burst3,
	scene_game_int_tag_number_sprite_pins_spiral_burst4,

	scene_game_int_tag_number_sprite_zhuanpan_skillbox1_light,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox2_light,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox3_light,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox4_light,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox5_light,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox6_light,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox7_light,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox8_light,

	scene_game_int_tag_number_sprite_zhuanpan_skillbox1_nolight,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox2_nolight,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox3_nolight,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox4_nolight,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox5_nolight,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox6_nolight,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox7_nolight,
	scene_game_int_tag_number_sprite_zhuanpan_skillbox8_nolight,


	scene_game_int_tag_number_sprite_monster1,
	scene_game_int_tag_number_sprite_monster2,
	scene_game_int_tag_number_sprite_monster3,
	scene_game_int_tag_number_sprite_monster4,
	scene_game_int_tag_number_sprite_monster5,

	scene_game_int_tag_number_sprite_pin1_energy1,
	scene_game_int_tag_number_sprite_pin2_energy1,
	scene_game_int_tag_number_sprite_pin3_energy1,
	scene_game_int_tag_number_sprite_pin4_energy1,

	scene_game_int_tag_number_sprite_hp_player,

	scene_game_int_tag_number_sprite_hp_monster1,
	scene_game_int_tag_number_sprite_hp_monster2,
	scene_game_int_tag_number_sprite_hp_monster3,
	scene_game_int_tag_number_sprite_hp_monster4,
	scene_game_int_tag_number_sprite_hp_monster5,

	scene_game_int_tag_number_sprite_hp_monster1_bg,
	scene_game_int_tag_number_sprite_hp_monster1_left,
	scene_game_int_tag_number_sprite_hp_monster1_right,
	scene_game_int_tag_number_sprite_hp_monster2_bg,
	scene_game_int_tag_number_sprite_hp_monster2_left,
	scene_game_int_tag_number_sprite_hp_monster2_right,
	scene_game_int_tag_number_sprite_hp_monster3_bg,
	scene_game_int_tag_number_sprite_hp_monster3_left,
	scene_game_int_tag_number_sprite_hp_monster3_right,
	scene_game_int_tag_number_sprite_hp_monster4_bg,
	scene_game_int_tag_number_sprite_hp_monster4_left,
	scene_game_int_tag_number_sprite_hp_monster4_right,
	scene_game_int_tag_number_sprite_hp_monster5_bg,
	scene_game_int_tag_number_sprite_hp_monster5_left,
	scene_game_int_tag_number_sprite_hp_monster5_right,

	scene_game_int_tag_number_label_instruction_player_turn,
	scene_game_int_tag_number_label_hp_player_text,
	scene_game_int_tag_number_label_hp_player_recover,
	scene_game_int_tag_number_label_player_be_attacked1_text,
	scene_game_int_tag_number_label_player_be_attacked2_text,
	scene_game_int_tag_number_label_monster1_attack_text,
	scene_game_int_tag_number_label_monster2_attack_text,
	scene_game_int_tag_number_label_monster3_attack_text,
	scene_game_int_tag_number_label_monster4_attack_text,
	scene_game_int_tag_number_label_monster5_attack_text,

	scene_game_int_tag_number_sprite_animate_boss,

	scene_game_int_tag_number_attack_effect1,
	scene_game_int_tag_number_attack_effect2,
	scene_game_int_tag_number_attack_effect3,
	scene_game_int_tag_number_heal_effect,
	scene_game_int_tag_number_enhance_effect,
	scene_game_int_tag_number_debuff_effect,
	scene_game_int_tag_number_attack_effect_by_accumulate,
};

Scene* SceneGame::createScene(Monster* monster1, Monster* monster2, Monster* monster3, Monster* monster4)
{

	auto scene = Scene::create();

	auto layer = create(monster1, monster2, monster3, monster4);

	scene->addChild(layer);

	return scene;
}

Layer* SceneGame::create(Monster* monster1, Monster* monster2, Monster* monster3, Monster* monster4)
{
	SceneGame *ret = new SceneGame();
	if (ret && ret->init(monster1, monster2, monster3, monster4))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool SceneGame::init(Monster* player_monster1, Monster* player_monster2, Monster* player_monster3, Monster* player_monster4)
{

	if (!Layer::init())
	{
		return false;
	}



	msg = AttackMessage::createMessage();

	this->PlayerMonster1 = player_monster1;
	this->PlayerMonster2 = player_monster2;
	this->PlayerMonster3 = player_monster3;
	this->PlayerMonster4 = player_monster4;

	this->monster1 = new SlimeFire(true,100);
	this->monster2 = new SlimeWater(true,100);
	this->monster3 = new BlackDragonBaby(true,100);
	this->monster4 = new BlackDragonBaby(true, 100);;
	this->monster5 = new LvBu(true,100);

	playerHP = PlayerMonster1->monster_get_hp_total() + PlayerMonster2->monster_get_hp_total() + PlayerMonster3->monster_get_hp_total() + PlayerMonster4->monster_get_hp_total();
	player_hp_total = playerHP;

	int numOfAttack = PlayerMonster1->monster_get_mosnter_type() + PlayerMonster2->monster_get_mosnter_type() + PlayerMonster3->monster_get_mosnter_type() + PlayerMonster4->monster_get_mosnter_type();

	msg->setNumAttackMonster(8-numOfAttack);
	msg->setNumAssistMonster(numOfAttack-4);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SceneGame::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SceneGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"SceneGame/CloseNormal.png",
		"SceneGame/CloseSelected.png",
		CC_CALLBACK_1(SceneGame::menuCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 5,
		origin.y + visibleSize.height - closeItem->getContentSize().height));

	auto label2 = LabelTTF::create("", "Arial", 24);
	label2->setColor(ccColor3B::GREEN);
	label2->setPosition(Vec2(visibleSize.width * 7 / 8, visibleSize.height *3 / 5));
	label2->setOpacity(0);
	label2->setTag(scene_game_int_tag_number_label_instruction_player_turn);
	addChild(label2, Level_3);
	

	auto sprite_animate_boss = Sprite::create("SceneGame/animation/boss/Comp 1_00018.png");

	sprite_animate_boss->setTag(scene_game_int_tag_number_sprite_animate_boss);
	sprite_animate_boss->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	sprite_animate_boss->setScaleX(visibleSize.width / sprite_animate_boss->getContentSize().width);
	sprite_animate_boss->setScaleY(visibleSize.height / sprite_animate_boss->getContentSize().height);
	sprite_animate_boss->setOpacity(0);

	addChild(sprite_animate_boss,Level_5);

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ONE);
	this->addChild(menu, Level_1);
	/*初始化转盘*/
	initZhuanpan(PlayerMonster1->getName(), PlayerMonster2->getName(), PlayerMonster3->getName(), PlayerMonster4->getName());

	/*初始化Player HP*/
	initPlayerHP();

	/*初始化小怪兽*/
	initMonsters();

	scene_game_bool_player_turn = false;
	scene_game_scene_timer = 1;
	this->scheduleUpdate();
	return true;
}

void SceneGame::setEmitterPosition()
{
	auto s = Director::getInstance()->getWinSize();
	if (partical_system_zhuanpan_decorate != NULL)
	{
		partical_system_zhuanpan_decorate->setPosition(Vec2(s.width /3, s.height / 3));
	}
}

void SceneGame::update(float dt)
{
	if (scene_game_scene_timer != 0){	
		scene_game_scene_timer++;
		if (scene_game_scene_timer > 60){
			scene_game_scene_timer = 0;
			if (level == 0){
				getChildByTag(scene_game_int_tag_number_sprite_monster1)->runAction(FadeIn::create(0.5));
				getChildByTag(scene_game_int_tag_number_sprite_monster2)->runAction(FadeIn::create(0.5));
				show_monster1_hp(true);
				show_monster2_hp(true);
				scene_game_bool_player_turn = true;
				getChildByTag(scene_game_int_tag_number_label_instruction_player_turn)->runAction(FadeIn::create(0.4f));
			}
			
		}
	}
	if (scene_game_bool_player_turn){
		auto label = (LabelTTF*)getChildByTag(scene_game_int_tag_number_label_instruction_player_turn);
		label->setColor(Color3B::GREEN);
		label->setString("Player");
	}
	else{
   		auto label = (LabelTTF*)getChildByTag(scene_game_int_tag_number_label_instruction_player_turn);
		label->setColor(Color3B::RED);
		label->setString("Enemy");
	}

	if (scene_game_bool_touched){
		auto *s1 = getChildByTag(scene_game_int_tag_number_sprite_pins);
		this->removeChildByTag(scene_game_int_tag_number_attack_effect1);
		this->removeChildByTag(scene_game_int_tag_number_attack_effect2);

		if (s1->numberOfRunningActions() == 0){
			scene_game_bool_touched = false;
			scene_game_attack_effect_timer = 1;
			monster1_energy_accumulate();
			monster2_energy_accumulate();
			monster3_energy_accumulate();
			monster4_energy_accumulate();
		}
	}
	if (scene_game_attack_effect_timer != 0){
		scene_game_attack_effect_timer++;
		//确保每个数字比下面的timer大。。。为了显示攻击怪物的效果...
		switch (scene_game_attack_effect_timer){
		case 15:
		case 25:
		case 35:
		case 45:updateMonsterHP(); upadtePlayerHP();
			break;
		}
		if (scene_game_attack_effect_timer == 10){
			player_attack_counter++;
			zhuanpanActionFinished();		
		}
		if (scene_game_attack_effect_timer == 20){
			player_attack_counter++;
			zhuanpanActionFinished();
		}
		if (scene_game_attack_effect_timer == 30){
			player_attack_counter++;
			zhuanpanActionFinished();	
		}
		if (scene_game_attack_effect_timer == 40){
			player_attack_counter++;
			zhuanpanActionFinished();
				
		}
		if (scene_game_attack_effect_timer > 50){

			scene_game_action_finished_timer = 1;
			scene_game_attack_effect_timer = 0;
			player_attack_counter = 0;
		}

	}
	if (scene_game_accumulated_timer != 0){
		scene_game_bool_special_attack = true;
		scene_game_accumulated_timer++;
		if (scene_game_accumulated_timer == 25){
			if (level == 0 && monster1->monster_get_hp_now() >= 0)
				getChildByTag(scene_game_int_tag_number_sprite_hp_monster1)->runAction(ScaleTo::create(0.1f, (scene_game_scale_monster1_hp*(monster1->monster_get_hp_now()) / monster1->monster_get_hp_total()), scene_game_scalZhuanPan));
			if (level == 0 && monster2->monster_get_hp_now() >= 0)
				getChildByTag(scene_game_int_tag_number_sprite_hp_monster2)->runAction(ScaleTo::create(0.1f, (scene_game_scale_monster2_hp*(monster2->monster_get_hp_now()) / monster2->monster_get_hp_total()), scene_game_scalZhuanPan));
			if (level == 1 && monster3->monster_get_hp_now() >= 0)
				getChildByTag(scene_game_int_tag_number_sprite_hp_monster3)->runAction(ScaleTo::create(0.1f, (scene_game_scale_monster3_hp*(monster3->monster_get_hp_now()) / monster3->monster_get_hp_total()), scene_game_scalZhuanPan));
			if (level == 1 && monster4->monster_get_hp_now() >= 0)
				getChildByTag(scene_game_int_tag_number_sprite_hp_monster4)->runAction(ScaleTo::create(0.1f, (scene_game_scale_monster4_hp*(monster4->monster_get_hp_now()) / monster4->monster_get_hp_total()), scene_game_scalZhuanPan));
			if (level == 2 && monster5->monster_get_hp_now() >= 0)
				getChildByTag(scene_game_int_tag_number_sprite_hp_monster5)->runAction(ScaleTo::create(0.1f, (scene_game_scale_monster5_hp*(monster5->monster_get_hp_now()) / monster5->monster_get_hp_total()), scene_game_scalZhuanPan));
		}
		if (scene_game_accumulated_timer > 51){
			scene_game_accumulated_timer = 0;
			scene_game_bool_special_attack = false;
			removeChildByTag(scene_game_int_tag_number_attack_effect_by_accumulate);

			if (level == 0){
				if (monster1->monster_get_hp_now() <= 0){
					show_monster1_hp(false);
					getChildByTag(scene_game_int_tag_number_sprite_monster1)->runAction(FadeOut::create(0.2));
				}
				if (monster2->monster_get_hp_now() <= 0){
					show_monster2_hp(false);
					getChildByTag(scene_game_int_tag_number_sprite_monster2)->runAction(FadeOut::create(0.2));
				}
			}
			if (level == 1){

				if (monster3->monster_get_hp_now() <= 0){
					show_monster3_hp(false);
					getChildByTag(scene_game_int_tag_number_sprite_monster3)->runAction(FadeOut::create(0.2));
				}
				if (monster4->monster_get_hp_now() <= 0){
					show_monster4_hp(false);
					getChildByTag(scene_game_int_tag_number_sprite_monster4)->runAction(FadeOut::create(0.2));
				}

			}

			if (level == 0 && monster1->monster_get_hp_now() <= 0 && monster2->monster_get_hp_now() <= 0){
				level=1;
				show_monster3_hp(true);
				show_monster4_hp(true);

				getChildByTag(scene_game_int_tag_number_sprite_monster3)->runAction(FadeIn::create(0.2));
				getChildByTag(scene_game_int_tag_number_sprite_monster4)->runAction(FadeIn::create(0.2));
			}
		
			if (level == 1 && monster3->monster_get_hp_now() <= 0 && monster4->monster_get_hp_now() <= 0){
				show_monster5_hp(true);
				level=2;
				removeChildByTag(scene_game_int_tag_number_sprite_monster1);
				removeChildByTag(scene_game_int_tag_number_sprite_monster2);
				scene_game_boss_alert_timer = 1;
				
			}


			if (level == 2 && monster5->monster_get_hp_now() <= 0){
				level = 3;
				show_monster5_hp(false);
				removeChildByTag(scene_game_int_tag_number_sprite_monster3);
				removeChildByTag(scene_game_int_tag_number_sprite_monster4);
				getChildByTag(scene_game_int_tag_number_sprite_monster5)->runAction(FadeOut::create(0.2));
				auto spriteWin = Sprite::create("SceneGame/win.png");
				this->addChild(spriteWin, Level_3);
				spriteWin->setPosition(Vec2(scene_game_position[0], scene_game_position[1]));
				spriteWin->runAction(FadeIn::create(0.2));
			}

		}
	}
	if (scene_game_boss_alert_timer != 0){
		scene_game_boss_alert_timer++;
		scene_game_bool_special_attack = true;
		if (scene_game_boss_alert_timer == 2){
			auto bossAnimation_tmp = Animation::create();
			for (int i = 18; i<112; i++)
			{
				char szName[100] = { 0 };
				sprintf(szName, "SceneGame/animation/boss/Comp 1_%05d.png", i);
				bossAnimation_tmp->addSpriteFrameWithFile(szName);
			}

			// should last 2.8 seconds. And there are 14 frames. 
			bossAnimation_tmp->setDelayPerUnit(3.9f / 94.0f);
			bossAnimation_tmp->setRestoreOriginalFrame(true);
			getChildByTag(scene_game_int_tag_number_sprite_animate_boss)->runAction(Animate::create(bossAnimation_tmp));
			getChildByTag(scene_game_int_tag_number_sprite_animate_boss)->setOpacity(255);

		}
		if (scene_game_boss_alert_timer == 120){
			getChildByTag(scene_game_int_tag_number_sprite_monster5)->runAction(FadeIn::create(0.2));
		}
		if (scene_game_boss_alert_timer > 140){
			scene_game_boss_alert_timer = 0;
			getChildByTag(scene_game_int_tag_number_sprite_animate_boss)->setOpacity(0);
			scene_game_bool_special_attack = false;
		}
	}


	if (scene_game_enemy_timer != 0){
		scene_game_enemy_timer++;
		
		scene_game_bool_player_turn = false;
		if (scene_game_enemy_timer==4)
			AttackByEnemy();
			
		if (scene_game_enemy_timer == 10){
			removeChildByTag(scene_game_int_tag_number_heal_effect);
			removeChildByTag(scene_game_int_tag_number_enhance_effect);
			removeChildByTag(scene_game_int_tag_number_debuff_effect);
			getChildByTag(scene_game_int_tag_number_sprite_pin_bg)->runAction(UtilBeingAttack::create(0.2f, scene_game_scalZhuanPan));
		}
		if (scene_game_enemy_timer>60 && getChildByTag(scene_game_int_tag_number_sprite_pin_bg)->numberOfRunningActions() == 0){
			scene_game_enemy_timer = 0;
			scene_game_bool_player_turn = true;

				removeChildByTag(scene_game_int_tag_number_label_monster1_attack_text);
				removeChildByTag(scene_game_int_tag_number_label_monster2_attack_text);
				removeChildByTag(scene_game_int_tag_number_label_monster3_attack_text);
				removeChildByTag(scene_game_int_tag_number_label_monster4_attack_text);
				removeChildByTag(scene_game_int_tag_number_label_monster5_attack_text);
				removeChildByTag(scene_game_int_tag_number_label_hp_player_recover);
		}
		if (playerHP <= 0){
			auto spriteWin = Sprite::create("SceneGame/lose.png");
			this->addChild(spriteWin, Level_3);
			spriteWin->setPosition(Vec2(scene_game_position[0], scene_game_position[1]));
			spriteWin->runAction(FadeIn::create(0.2));
		}
	}
	if (scene_game_action_finished_timer != 0){
		scene_game_action_finished_timer++;
		
		if (scene_game_action_finished_timer > 11){
			scene_game_action_finished_timer = 0;
			scene_game_bool_player_turn = false;
			scene_game_enemy_timer = 1;
			removeChildByTag(scene_game_int_tag_number_label_player_be_attacked1_text);
			removeChildByTag(scene_game_int_tag_number_label_player_be_attacked2_text);
			if (spiral_light_num<8)
			spiral_light_num++;
			spiral_burst_light_turn_on(true);

			if (level == 0){
				if (monster1->monster_get_hp_now() <= 0){
					show_monster1_hp(false);
					getChildByTag(scene_game_int_tag_number_sprite_monster1)->runAction(FadeOut::create(0.2));
				}
				if (monster2->monster_get_hp_now() <= 0){
					show_monster2_hp(false);
					getChildByTag(scene_game_int_tag_number_sprite_monster2)->runAction(FadeOut::create(0.2));
				}
			}
			if (level == 1){

				if (monster3->monster_get_hp_now() <= 0){
					show_monster3_hp(false);
					getChildByTag(scene_game_int_tag_number_sprite_monster3)->runAction(FadeOut::create(0.2));
				}
				if (monster4->monster_get_hp_now() <= 0){
					show_monster4_hp(false);
					getChildByTag(scene_game_int_tag_number_sprite_monster4)->runAction(FadeOut::create(0.2));
				}

			}

			if (level == 0 && monster1->monster_get_hp_now() <= 0 && monster2->monster_get_hp_now() <= 0){
				level = 1;
				show_monster3_hp(true);
				show_monster4_hp(true);
				scene_game_enemy_timer = 0;
				scene_game_bool_player_turn = true;
				getChildByTag(scene_game_int_tag_number_sprite_monster3)->runAction(FadeIn::create(0.2));
				getChildByTag(scene_game_int_tag_number_sprite_monster4)->runAction(FadeIn::create(0.2));
			}

			if (level == 1 && monster3->monster_get_hp_now() <= 0 && monster4->monster_get_hp_now() <= 0){
				show_monster5_hp(true);
				scene_game_enemy_timer = 0;
				scene_game_bool_player_turn = true;
				level = 2;
				removeChildByTag(scene_game_int_tag_number_sprite_monster1);
				removeChildByTag(scene_game_int_tag_number_sprite_monster2);
				scene_game_boss_alert_timer = 1;
				
			}


			if (level == 2 && monster5->monster_get_hp_now() <= 0){
				level = 3;
				show_monster5_hp(false);
				removeChildByTag(scene_game_int_tag_number_sprite_monster3);
				removeChildByTag(scene_game_int_tag_number_sprite_monster4);
				getChildByTag(scene_game_int_tag_number_sprite_monster5)->runAction(FadeOut::create(0.2));
				auto spriteWin = Sprite::create("SceneGame/win.png");
				this->addChild(spriteWin, Level_3);
				spriteWin->setPosition(Vec2(scene_game_position[0], scene_game_position[1]));
				spriteWin->runAction(FadeIn::create(0.2));
			}

		}
	}
	if (level == 3){
		removeChildByTag(scene_game_int_tag_number_sprite_monster5);
	}
}

bool SceneGame::onTouchBegan(Touch* touch, Event  *event)
{
	if (!scene_game_bool_player_turn || scene_game_bool_special_attack)
		return false;
	if (scene_game_bool_touched)
		return false;
	
	if (scene_game_bool_sprial_burst_menu_showed)
		spiral_burst_pin_show();
	return true;
}

void SceneGame::onTouchEnded(Touch* touch, Event  *event)
{
	if (monster5->monster_get_hp_now()>0&&playerHP>0) {

		getChildByTag(scene_game_int_tag_number_sprite_pins)->stopAllActions();

		float at = rand()%360;

		accumulated_angle += at;

		getChildByTag(scene_game_int_tag_number_sprite_pins)->runAction(UtilFadeRotateRy::create(at, scene_game_zhuanpan_action_time));
		getChildByTag(scene_game_int_tag_number_sprite_pins_spiral_burst1)->runAction(UtilFadeRotateRy::create(at, scene_game_zhuanpan_action_time));
		getChildByTag(scene_game_int_tag_number_sprite_pins_spiral_burst2)->runAction(UtilFadeRotateRy::create(at, scene_game_zhuanpan_action_time));
		getChildByTag(scene_game_int_tag_number_sprite_pins_spiral_burst3)->runAction(UtilFadeRotateRy::create(at, scene_game_zhuanpan_action_time));
		getChildByTag(scene_game_int_tag_number_sprite_pins_spiral_burst4)->runAction(UtilFadeRotateRy::create(at, scene_game_zhuanpan_action_time));

		getChildByTag(scene_game_int_tag_number_sprite_pin1_energy1)->runAction(UtilFadeRotateRy::create(at, scene_game_zhuanpan_action_time));

		getChildByTag(scene_game_int_tag_number_sprite_pin2_energy1)->runAction(UtilFadeRotateRy::create(at, scene_game_zhuanpan_action_time));

		getChildByTag(scene_game_int_tag_number_sprite_pin3_energy1)->runAction(UtilFadeRotateRy::create(at, scene_game_zhuanpan_action_time));

		getChildByTag(scene_game_int_tag_number_sprite_pin4_energy1)->runAction(UtilFadeRotateRy::create(at, scene_game_zhuanpan_action_time));

		scene_game_bool_touched = true;
	}
	else{
		menuCallback(NULL);
	}

	
	
}

void SceneGame::menuCallback(cocos2d::Ref* pSender){
	if (!scene_game_bool_player_turn)
		return;
	auto s = SceneMainMenu::createScene();
	
	Director::sharedDirector()->replaceScene(TransitionFade::create(1, s));
	
}

void SceneGame::monster1_energy_accumulate(){

	Player_monster1_energy++;
	getChildByTag(scene_game_int_tag_number_sprite_pin1_energy1)->setOpacity(0);

	if (Player_monster1_energy > PlayerMonster1->monster_getEnergyLimit()){
		Player_monster1_energy = PlayerMonster1->monster_getEnergyLimit();
	}
	if (Player_monster1_energy == PlayerMonster1->monster_getEnergyLimit())
		getChildByTag(scene_game_int_tag_number_sprite_pin1_energy1)->runAction(RepeatForever::create(Sequence::createWithTwoActions(FadeOut::create(0.5f), FadeIn::create(0.5f))));

}

void SceneGame::monster2_energy_accumulate(){
	Player_monster2_energy++;
	getChildByTag(scene_game_int_tag_number_sprite_pin2_energy1)->setOpacity(0);

	if (Player_monster2_energy > PlayerMonster2->monster_getEnergyLimit()){
		Player_monster2_energy = PlayerMonster2->monster_getEnergyLimit();
	}
	if (Player_monster2_energy == PlayerMonster2->monster_getEnergyLimit())
		getChildByTag(scene_game_int_tag_number_sprite_pin2_energy1)->runAction(RepeatForever::create(Sequence::createWithTwoActions(FadeOut::create(0.5f), FadeIn::create(0.5f))));

	
}

void SceneGame::monster3_energy_accumulate(){
	Player_monster3_energy++;
	getChildByTag(scene_game_int_tag_number_sprite_pin3_energy1)->setOpacity(0);

	if (Player_monster3_energy > PlayerMonster3->monster_getEnergyLimit()){
		Player_monster3_energy = PlayerMonster3->monster_getEnergyLimit();
	}
	if (Player_monster3_energy == PlayerMonster3->monster_getEnergyLimit())
		getChildByTag(scene_game_int_tag_number_sprite_pin3_energy1)->runAction(RepeatForever::create(Sequence::createWithTwoActions(FadeOut::create(0.5f), FadeIn::create(0.5f))));

}

void SceneGame::monster4_energy_accumulate(){
	Player_monster4_energy++;
	getChildByTag(scene_game_int_tag_number_sprite_pin4_energy1)->setOpacity(0);

	if (Player_monster4_energy > PlayerMonster4->monster_getEnergyLimit()){
		Player_monster4_energy = PlayerMonster4->monster_getEnergyLimit();
	}
	if (Player_monster4_energy == PlayerMonster4->monster_getEnergyLimit())
		getChildByTag(scene_game_int_tag_number_sprite_pin4_energy1)->runAction(RepeatForever::create(Sequence::createWithTwoActions(FadeOut::create(0.5f), FadeIn::create(0.5f))));

}

void SceneGame::monster1_pin_Callback(cocos2d::Ref* pSender){
	if (!scene_game_bool_player_turn || scene_game_bool_special_attack)
		return;
	if (scene_game_bool_touched)
		return;

	if (scene_game_bool_sprial_burst_menu_showed){
		spiral_burst_pin_show();
		if (PlayerMonster1->monster_getSpiralBurstLimit() <= spiral_light_num){
			spiral_light_num -= PlayerMonster1->monster_getSpiralBurstLimit();
			spiral_burst_light_turn_on(false);
			msg->setType(5);
			specialAttack(PlayerMonster1->monster_AttackOthers(msg),PlayerMonster1);
		}
	}
	else if (Player_monster1_energy == PlayerMonster1->monster_getEnergyLimit()){
		getChildByTag(scene_game_int_tag_number_sprite_pin1_energy1)->stopAllActions();
		getChildByTag(scene_game_int_tag_number_sprite_pin1_energy1)->setOpacity(0);
		Player_monster1_energy = 0;
		msg->setType(4);
		specialAttack(PlayerMonster1->monster_AttackOthers(msg), PlayerMonster1);
	}

}

void SceneGame::monster2_pin_Callback(cocos2d::Ref* pSender){
	if (!scene_game_bool_player_turn || scene_game_bool_special_attack)
		return;
	if (scene_game_bool_touched)
		return;
	if (scene_game_bool_sprial_burst_menu_showed){
		spiral_burst_pin_show();
		if (PlayerMonster2->monster_getSpiralBurstLimit() <= spiral_light_num){
			spiral_light_num -= PlayerMonster2->monster_getSpiralBurstLimit();
			spiral_burst_light_turn_on(false);
			msg->setType(5);
			specialAttack(PlayerMonster2->monster_AttackOthers(msg), PlayerMonster2);
		}
	}
	else  if (Player_monster2_energy == PlayerMonster2->monster_getEnergyLimit()){
		getChildByTag(scene_game_int_tag_number_sprite_pin2_energy1)->stopAllActions();
		getChildByTag(scene_game_int_tag_number_sprite_pin2_energy1)->setOpacity(0);
		Player_monster2_energy = 0;
		msg->setType(4);
		specialAttack(PlayerMonster2->monster_AttackOthers(msg),  PlayerMonster2);
	}
	
}

void SceneGame::monster3_pin_Callback(cocos2d::Ref* pSender){
	if (!scene_game_bool_player_turn || scene_game_bool_special_attack)
		return;
	if (scene_game_bool_touched)
		return;
	if (scene_game_bool_sprial_burst_menu_showed){
		spiral_burst_pin_show();
		if (PlayerMonster3->monster_getSpiralBurstLimit() <= spiral_light_num){
			spiral_light_num -= PlayerMonster3->monster_getSpiralBurstLimit();
			spiral_burst_light_turn_on(false);
			msg->setType(5);
			specialAttack(PlayerMonster3->monster_AttackOthers(msg), PlayerMonster3);
		}
	} else
		if (Player_monster3_energy == PlayerMonster3->monster_getEnergyLimit()){
		getChildByTag(scene_game_int_tag_number_sprite_pin3_energy1)->stopAllActions();
		getChildByTag(scene_game_int_tag_number_sprite_pin3_energy1)->setOpacity(0);
		Player_monster3_energy = 0;
		msg->setType(4);
		specialAttack(PlayerMonster3->monster_AttackOthers(msg), PlayerMonster3);
	}
	
}

void SceneGame::monster4_pin_Callback(cocos2d::Ref* pSender){
	if (!scene_game_bool_player_turn || scene_game_bool_special_attack)
		return;
	if (scene_game_bool_touched)
		return;
	if (scene_game_bool_sprial_burst_menu_showed){
		spiral_burst_pin_show();
		if (PlayerMonster4->monster_getSpiralBurstLimit() <= spiral_light_num){
			spiral_light_num -= PlayerMonster4->monster_getSpiralBurstLimit();
		spiral_burst_light_turn_on(false);
		msg->setType(5);
		specialAttack(PlayerMonster4->monster_AttackOthers(msg), PlayerMonster4);
		}
	} else
		if (Player_monster4_energy == PlayerMonster4->monster_getEnergyLimit()){
		getChildByTag(scene_game_int_tag_number_sprite_pin4_energy1)->stopAllActions();
		getChildByTag(scene_game_int_tag_number_sprite_pin4_energy1)->setOpacity(0);
		Player_monster4_energy = 0;
		msg->setType(4);
		specialAttack(PlayerMonster4->monster_AttackOthers(msg),  PlayerMonster4);
	}

}

void SceneGame::zhuanpan_center_Callback(cocos2d::Ref* pSender){
	if (!scene_game_bool_player_turn)
		return;
	if (scene_game_bool_touched)
		return;
	spiral_burst_pin_show();

}

void SceneGame::spiral_burst_pin_show(){
	if (scene_game_bool_sprial_burst_menu_showed){
		if (PlayerMonster1->monster_getSpiralBurstLimit() <= spiral_light_num)
			getChildByTag(scene_game_int_tag_number_sprite_pins_spiral_burst1)->runAction(FadeOut::create(0.5f));
		if (PlayerMonster2->monster_getSpiralBurstLimit() <= spiral_light_num)
			getChildByTag(scene_game_int_tag_number_sprite_pins_spiral_burst2)->runAction(FadeOut::create(0.5f));
		if (PlayerMonster3->monster_getSpiralBurstLimit() <= spiral_light_num)
			getChildByTag(scene_game_int_tag_number_sprite_pins_spiral_burst3)->runAction(FadeOut::create(0.5f));
		if (PlayerMonster4->monster_getSpiralBurstLimit() <= spiral_light_num)
			getChildByTag(scene_game_int_tag_number_sprite_pins_spiral_burst4)->runAction(FadeOut::create(0.5f));

	}
	else{
		if (PlayerMonster1->monster_getSpiralBurstLimit() <= spiral_light_num)
			getChildByTag(scene_game_int_tag_number_sprite_pins_spiral_burst1)->runAction(FadeIn::create(0.5f));
		if (PlayerMonster2->monster_getSpiralBurstLimit() <= spiral_light_num)
			getChildByTag(scene_game_int_tag_number_sprite_pins_spiral_burst2)->runAction(FadeIn::create(0.5f));
		if (PlayerMonster3->monster_getSpiralBurstLimit() <= spiral_light_num)
			getChildByTag(scene_game_int_tag_number_sprite_pins_spiral_burst3)->runAction(FadeIn::create(0.5f));
		if (PlayerMonster4->monster_getSpiralBurstLimit() <= spiral_light_num)
			getChildByTag(scene_game_int_tag_number_sprite_pins_spiral_burst4)->runAction(FadeIn::create(0.5f));
	}
	scene_game_bool_sprial_burst_menu_showed = !scene_game_bool_sprial_burst_menu_showed;
}

void SceneGame::spiral_burst_light_turn_on(bool turn_on){
	if (turn_on){

		switch (spiral_light_num){
		case 8:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox8_light)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox8_nolight)->setOpacity(0); break;
		case 7:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox7_light)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox7_nolight)->setOpacity(0); break;
		case 6:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox6_light)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox6_nolight)->setOpacity(0); break;
		case 5:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox5_light)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox5_nolight)->setOpacity(0); break;
		case 4:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox4_light)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox4_nolight)->setOpacity(0); break;
		case 3:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox3_light)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox3_nolight)->setOpacity(0); break;
		case 2:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox2_light)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox2_nolight)->setOpacity(0); break;
		case 1:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox1_light)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox1_nolight)->setOpacity(0); break;
			break;
		case 0:break;
		}

	}
	else{

		switch (8-spiral_light_num){
		case 8:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox1_nolight)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox1_light)->setOpacity(0);
		case 7:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox2_nolight)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox2_light)->setOpacity(0); 
		case 6:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox3_nolight)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox3_light)->setOpacity(0);
		case 5:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox4_nolight)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox4_light)->setOpacity(0); 
		case 4:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox5_nolight)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox5_light)->setOpacity(0);
		case 3:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox6_nolight)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox6_light)->setOpacity(0); 
		case 2:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox7_nolight)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox7_light)->setOpacity(0);
		case 1:
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox8_nolight)->runAction(FadeIn::create(0.1f));
			getChildByTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox8_light)->setOpacity(0);
			break;
		case 0:break;
		}

	}

}

void SceneGame::initPlayerHP(){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*
	Player血条
	*/
	auto sprite_player_hp_bg = Sprite::create("SceneGame/HP/player/bg_body.png");
	auto sprite_player_hp_bg_left = Sprite::create("SceneGame/HP/player/bg_left.png");
	auto sprite_player_hp_bg_right = Sprite::create("SceneGame/HP/player/bg_right.png");


	sprite_player_hp_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 13 / 20));
	sprite_player_hp_bg_left->setPosition(Vec2(sprite_player_hp_bg_left->getContentSize().width*scene_game_scalZhuanPan / 2, visibleSize.height * 13 / 20));
	sprite_player_hp_bg_right->setPosition(Vec2(visibleSize.width - sprite_player_hp_bg_right->getContentSize().width*scene_game_scalZhuanPan / 2, visibleSize.height * 13 / 20));

	sprite_player_hp_bg->setScale(scene_game_scalZhuanPan);
	sprite_player_hp_bg_left->setScale(scene_game_scalZhuanPan);
	sprite_player_hp_bg_right->setScale(scene_game_scalZhuanPan);

	this->addChild(sprite_player_hp_bg, Level_1);
	this->addChild(sprite_player_hp_bg_left, Level_3);
	this->addChild(sprite_player_hp_bg_right, Level_3);

	auto sprite_player_hp_body = Sprite::create("SceneGame/HP/player/greenbody.png");

	float left_head = sprite_player_hp_bg_left->getContentSize().width*scene_game_scalZhuanPan * 2 / 3;
	float right_head = sprite_player_hp_bg_right->getContentSize().width*scene_game_scalZhuanPan / 2;

	sprite_player_hp_body->setTag(scene_game_int_tag_number_sprite_hp_player);
	sprite_player_hp_body->setPosition(Vec2(left_head, visibleSize.height * 13 / 20));
	sprite_player_hp_body->setScaleY(scene_game_scalZhuanPan);
	scene_game_scale_player_hp = ((visibleSize.width - left_head - right_head) / sprite_player_hp_body->getContentSize().width);
	sprite_player_hp_body->setScaleX(scene_game_scale_player_hp);
	sprite_player_hp_body->setAnchorPoint(Vec2(0, 0.5));

	std::stringstream temp;
	temp << playerHP;
	std::string s = temp.str();
	auto label = LabelTTF::create(s + "/" + s, "Arial", 15);
	label->setTag(scene_game_int_tag_number_label_hp_player_text);
	// position the label on the center of the screen
	label->setPosition(Vec2(visibleSize.width*2 / 3, visibleSize.height * 13 / 20));
	this->addChild(label, Level_3);

	this->addChild(sprite_player_hp_body, Level_2);

}

void SceneGame::initZhuanpan(std::string scene_game_monster_pin1, std::string scene_game_monster_pin2, std::string scene_game_monster_pin3, std::string scene_game_monster_pin4){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*
	画出转盘！并计算相关的 Scal
	*/

	auto sprite_zhuanpanOutSide = Sprite::create("SceneGame/outside.png");
	sprite_zhuanpanOutSide->setTag(scene_game_int_tag_number_sprite_pin_bg);
	auto zhuanpan_center = Vec2(visibleSize.width / 2, visibleSize.height / 3);
	scene_game_position[0] = visibleSize.width / 2 + origin.x;
	scene_game_position[1] = 5*visibleSize.height / 6 + origin.y;
	sprite_zhuanpanOutSide->setPosition(zhuanpan_center);
	float  scal_ZhuanPan = 0.6*visibleSize.height / sprite_zhuanpanOutSide->getContentSize().height;
	float radius = 0.69 *  visibleSize.height / 3;
	if (visibleSize.width / 2<visibleSize.height / 3){
		scal_ZhuanPan = visibleSize.width / sprite_zhuanpanOutSide->getContentSize().width;
		radius = 0.69  * visibleSize.width / 2;
	}
	scene_game_scalZhuanPan = scal_ZhuanPan;
	sprite_zhuanpanOutSide->setScale(scal_ZhuanPan);
	addChild(sprite_zhuanpanOutSide, Level_1);


	/**
	画出指针！并计算相关的 Scal
	*/
	auto sprite_pin1 = MenuItemImage::create(
		"SceneGame/pin/pin_" + scene_game_monster_pin1 + ".png",
		"SceneGame/pin/pin_" + scene_game_monster_pin1 + ".png",
		CC_CALLBACK_1(SceneGame::monster1_pin_Callback, this));

	auto sprite_pin2 = MenuItemImage::create(
		"SceneGame/pin/pin_" + scene_game_monster_pin2 + ".png",
		"SceneGame/pin/pin_" + scene_game_monster_pin2 + ".png",
		CC_CALLBACK_1(SceneGame::monster2_pin_Callback, this));
	auto sprite_pin3 = MenuItemImage::create(
		"SceneGame/pin/pin_" + scene_game_monster_pin3 + ".png",
		"SceneGame/pin/pin_" + scene_game_monster_pin3 + ".png",
		CC_CALLBACK_1(SceneGame::monster3_pin_Callback, this));
	auto sprite_pin4 = MenuItemImage::create(
		"SceneGame/pin/pin_" + scene_game_monster_pin4 + ".png",
		"SceneGame/pin/pin_" + scene_game_monster_pin4 + ".png",
		CC_CALLBACK_1(SceneGame::monster4_pin_Callback, this));

	sprite_pin1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	sprite_pin2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	sprite_pin3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	sprite_pin4->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));

	sprite_pin1->setAnchorPoint(Vec2(0.5, -0.09));
	sprite_pin2->setAnchorPoint(Vec2(0.5, -0.09));
	sprite_pin3->setAnchorPoint(Vec2(0.5, -0.09));
	sprite_pin4->setAnchorPoint(Vec2(0.5, -0.09));

	sprite_pin1->setScale(scal_ZhuanPan);
	sprite_pin2->setScale(scal_ZhuanPan);
	sprite_pin3->setScale(scal_ZhuanPan);
	sprite_pin4->setScale(scal_ZhuanPan);

	sprite_pin2->setRotation(90.0f);
	sprite_pin3->setRotation(180.0f);
	sprite_pin4->setRotation(270.0f);


	auto pin_menu = Menu::create(sprite_pin1, sprite_pin2, sprite_pin3, sprite_pin4, NULL);

	pin_menu->setTag(scene_game_int_tag_number_sprite_pins);

	pin_menu->setAnchorPoint(Vec2(0.5f, 0.33333f));
	this->addChild(pin_menu, Level_3);
	pin_menu->setPosition(Vec2::ZERO);
	/*指针结束*/
	/*转盘中心按键，显示Sprial Burst*/
	auto sprite_zhuanpan_center = MenuItemImage::create(
		"SceneGame/pin/zhuanpan_center.png",
		"SceneGame/pin/zhuanpan_center.png",
		CC_CALLBACK_1(SceneGame::zhuanpan_center_Callback, this));

	sprite_zhuanpan_center->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	sprite_zhuanpan_center->setScale(scal_ZhuanPan);
	auto center_menu = Menu::create(sprite_zhuanpan_center, NULL);
	center_menu->setPosition(Vec2::ZERO);
	this->addChild(center_menu, Level_3);
	/*Sprial Burst 指针的Menu*/


	auto sprite_pin1_spiral_burst = MenuItemImage::create(
		"SceneGame/pin/" + spiral_number[PlayerMonster1->monster_getSpiralBurstLimit()] + ".png",
		"SceneGame/pin/" + spiral_number[PlayerMonster1->monster_getSpiralBurstLimit()] + ".png",
		CC_CALLBACK_1(SceneGame::monster1_pin_Callback, this));

	auto sprite_pin2_spiral_burst = MenuItemImage::create(
		"SceneGame/pin/" + spiral_number[PlayerMonster2->monster_getSpiralBurstLimit()] + ".png",
		"SceneGame/pin/" + spiral_number[PlayerMonster2->monster_getSpiralBurstLimit()] + ".png",
		CC_CALLBACK_1(SceneGame::monster2_pin_Callback, this));
	auto sprite_pin3_spiral_burst = MenuItemImage::create(
		"SceneGame/pin/" + spiral_number[PlayerMonster3->monster_getSpiralBurstLimit()] + ".png",
		"SceneGame/pin/" + spiral_number[PlayerMonster3->monster_getSpiralBurstLimit()] + ".png",
		CC_CALLBACK_1(SceneGame::monster3_pin_Callback, this));
	auto sprite_pin4_spiral_burst = MenuItemImage::create(
		"SceneGame/pin/" + spiral_number[PlayerMonster4->monster_getSpiralBurstLimit()] + ".png",
		"SceneGame/pin/" + spiral_number[PlayerMonster4->monster_getSpiralBurstLimit()] + ".png",
		CC_CALLBACK_1(SceneGame::monster4_pin_Callback, this));

	sprite_pin1_spiral_burst->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	sprite_pin2_spiral_burst->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	sprite_pin3_spiral_burst->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	sprite_pin4_spiral_burst->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));

	sprite_pin1_spiral_burst->setAnchorPoint(Vec2(0.5, -0.09));
	sprite_pin2_spiral_burst->setAnchorPoint(Vec2(0.5, -0.09));
	sprite_pin3_spiral_burst->setAnchorPoint(Vec2(0.5, -0.09));
	sprite_pin4_spiral_burst->setAnchorPoint(Vec2(0.5, -0.09));

	sprite_pin1_spiral_burst->setScale(scal_ZhuanPan);
	sprite_pin2_spiral_burst->setScale(scal_ZhuanPan);
	sprite_pin3_spiral_burst->setScale(scal_ZhuanPan);
	sprite_pin4_spiral_burst->setScale(scal_ZhuanPan);

	sprite_pin2_spiral_burst->setRotation(90.0f);
	sprite_pin3_spiral_burst->setRotation(180.0f);
	sprite_pin4_spiral_burst->setRotation(270.0f);


	auto pin_menu_spiral_burst1 = Menu::create(sprite_pin1_spiral_burst, NULL);
	auto pin_menu_spiral_burst2 = Menu::create(sprite_pin2_spiral_burst, NULL);
	auto pin_menu_spiral_burst3 = Menu::create(sprite_pin3_spiral_burst, NULL);
	auto pin_menu_spiral_burst4 = Menu::create(sprite_pin4_spiral_burst, NULL);

	pin_menu_spiral_burst1->setTag(scene_game_int_tag_number_sprite_pins_spiral_burst1);
	pin_menu_spiral_burst2->setTag(scene_game_int_tag_number_sprite_pins_spiral_burst2);
	pin_menu_spiral_burst3->setTag(scene_game_int_tag_number_sprite_pins_spiral_burst3);
	pin_menu_spiral_burst4->setTag(scene_game_int_tag_number_sprite_pins_spiral_burst4);

	pin_menu_spiral_burst1->setOpacity(0);
	pin_menu_spiral_burst2->setOpacity(0);
	pin_menu_spiral_burst3->setOpacity(0);
	pin_menu_spiral_burst4->setOpacity(0);

	pin_menu_spiral_burst1->setAnchorPoint(Vec2(0.5f, 0.33333f));
	pin_menu_spiral_burst2->setAnchorPoint(Vec2(0.5f, 0.33333f));
	pin_menu_spiral_burst3->setAnchorPoint(Vec2(0.5f, 0.33333f));
	pin_menu_spiral_burst4->setAnchorPoint(Vec2(0.5f, 0.33333f));

	pin_menu_spiral_burst1->setPosition(Vec2::ZERO);
	pin_menu_spiral_burst2->setPosition(Vec2::ZERO);
	pin_menu_spiral_burst3->setPosition(Vec2::ZERO);
	pin_menu_spiral_burst4->setPosition(Vec2::ZERO);

	this->addChild(pin_menu_spiral_burst1, Level_4);
	this->addChild(pin_menu_spiral_burst2, Level_4);
	this->addChild(pin_menu_spiral_burst3, Level_4);
	this->addChild(pin_menu_spiral_burst4, Level_4);
	/*指针结束*/

	/*技能盒*/



	auto sprite_zhuanpan_nolight_skillbox1 = Sprite::create("SceneGame/zhuanpan/" + string_nolight + "/1/" + skillbox1 + ".png");
	auto sprite_zhuanpan_nolight_skillbox2 = Sprite::create("SceneGame/zhuanpan/" + string_nolight + "/2/" + skillbox2 + ".png");
	auto sprite_zhuanpan_nolight_skillbox3 = Sprite::create("SceneGame/zhuanpan/" + string_nolight + "/3/" + skillbox3 + ".png");
	auto sprite_zhuanpan_nolight_skillbox4 = Sprite::create("SceneGame/zhuanpan/" + string_nolight + "/4/" + skillbox4 + ".png");
	auto sprite_zhuanpan_nolight_skillbox5 = Sprite::create("SceneGame/zhuanpan/" + string_nolight + "/5/" + skillbox5 + ".png");
	auto sprite_zhuanpan_nolight_skillbox6 = Sprite::create("SceneGame/zhuanpan/" + string_nolight + "/6/" + skillbox6 + ".png");
	auto sprite_zhuanpan_nolight_skillbox7 = Sprite::create("SceneGame/zhuanpan/" + string_nolight + "/7/" + skillbox7 + ".png");
	auto sprite_zhuanpan_nolight_skillbox8 = Sprite::create("SceneGame/zhuanpan/" + string_nolight + "/8/" + skillbox8 + ".png");

	float cos22_5 = 0.9f;
	float sin22_5 = 0.42f;

	addChild(sprite_zhuanpan_nolight_skillbox1, Level_2);
	addChild(sprite_zhuanpan_nolight_skillbox2, Level_2);
	addChild(sprite_zhuanpan_nolight_skillbox3, Level_2);
	addChild(sprite_zhuanpan_nolight_skillbox4, Level_2);
	addChild(sprite_zhuanpan_nolight_skillbox5, Level_2);
	addChild(sprite_zhuanpan_nolight_skillbox6, Level_2);
	addChild(sprite_zhuanpan_nolight_skillbox7, Level_2);
	addChild(sprite_zhuanpan_nolight_skillbox8, Level_2);

	sprite_zhuanpan_nolight_skillbox1->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox1_nolight);
	sprite_zhuanpan_nolight_skillbox2->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox2_nolight);
	sprite_zhuanpan_nolight_skillbox3->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox3_nolight);
	sprite_zhuanpan_nolight_skillbox4->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox4_nolight);
	sprite_zhuanpan_nolight_skillbox5->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox5_nolight);
	sprite_zhuanpan_nolight_skillbox6->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox6_nolight);
	sprite_zhuanpan_nolight_skillbox7->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox7_nolight);
	sprite_zhuanpan_nolight_skillbox8->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox8_nolight);

	sprite_zhuanpan_nolight_skillbox1->setScale(scal_ZhuanPan);
	sprite_zhuanpan_nolight_skillbox2->setScale(scal_ZhuanPan);
	sprite_zhuanpan_nolight_skillbox3->setScale(scal_ZhuanPan);
	sprite_zhuanpan_nolight_skillbox4->setScale(scal_ZhuanPan);
	sprite_zhuanpan_nolight_skillbox5->setScale(scal_ZhuanPan);
	sprite_zhuanpan_nolight_skillbox6->setScale(scal_ZhuanPan);
	sprite_zhuanpan_nolight_skillbox7->setScale(scal_ZhuanPan);
	sprite_zhuanpan_nolight_skillbox8->setScale(scal_ZhuanPan);

	sprite_zhuanpan_nolight_skillbox1->setPosition(Vec2(visibleSize.width / 2 + radius*sin22_5, visibleSize.height / 3 + radius*cos22_5));
	sprite_zhuanpan_nolight_skillbox2->setPosition(Vec2(visibleSize.width / 2 + radius*cos22_5, visibleSize.height / 3 + radius*sin22_5));
	sprite_zhuanpan_nolight_skillbox3->setPosition(Vec2(visibleSize.width / 2 + radius*cos22_5, visibleSize.height / 3 - radius*sin22_5));
	sprite_zhuanpan_nolight_skillbox4->setPosition(Vec2(visibleSize.width / 2 + radius*sin22_5, visibleSize.height / 3 - radius*cos22_5));
	sprite_zhuanpan_nolight_skillbox5->setPosition(Vec2(visibleSize.width / 2 - radius*sin22_5, visibleSize.height / 3 - radius*cos22_5));
	sprite_zhuanpan_nolight_skillbox6->setPosition(Vec2(visibleSize.width / 2 - radius*cos22_5, visibleSize.height / 3 - radius*sin22_5));
	sprite_zhuanpan_nolight_skillbox7->setPosition(Vec2(visibleSize.width / 2 - radius*cos22_5, visibleSize.height / 3 + radius*sin22_5));
	sprite_zhuanpan_nolight_skillbox8->setPosition(Vec2(visibleSize.width / 2 - radius*sin22_5, visibleSize.height / 3 + radius*cos22_5));

	/**********************************************************************************************/
	auto sprite_zhuanpan_light_skillbox1 = Sprite::create("SceneGame/zhuanpan/" + string_light + "/1/" + skillbox1 + ".png");
	auto sprite_zhuanpan_light_skillbox2 = Sprite::create("SceneGame/zhuanpan/" + string_light + "/2/" + skillbox2 + ".png");
	auto sprite_zhuanpan_light_skillbox3 = Sprite::create("SceneGame/zhuanpan/" + string_light + "/3/" + skillbox3 + ".png");
	auto sprite_zhuanpan_light_skillbox4 = Sprite::create("SceneGame/zhuanpan/" + string_light + "/4/" + skillbox4 + ".png");
	auto sprite_zhuanpan_light_skillbox5 = Sprite::create("SceneGame/zhuanpan/" + string_light + "/5/" + skillbox5 + ".png");
	auto sprite_zhuanpan_light_skillbox6 = Sprite::create("SceneGame/zhuanpan/" + string_light + "/6/" + skillbox6 + ".png");
	auto sprite_zhuanpan_light_skillbox7 = Sprite::create("SceneGame/zhuanpan/" + string_light + "/7/" + skillbox7 + ".png");
	auto sprite_zhuanpan_light_skillbox8 = Sprite::create("SceneGame/zhuanpan/" + string_light + "/8/" + skillbox8 + ".png");

	addChild(sprite_zhuanpan_light_skillbox1, Level_2);
	addChild(sprite_zhuanpan_light_skillbox2, Level_2);
	addChild(sprite_zhuanpan_light_skillbox3, Level_2);
	addChild(sprite_zhuanpan_light_skillbox4, Level_2);
	addChild(sprite_zhuanpan_light_skillbox5, Level_2);
	addChild(sprite_zhuanpan_light_skillbox6, Level_2);
	addChild(sprite_zhuanpan_light_skillbox7, Level_2);
	addChild(sprite_zhuanpan_light_skillbox8, Level_2);

	sprite_zhuanpan_light_skillbox1->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox1_light);
	sprite_zhuanpan_light_skillbox2->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox2_light);
	sprite_zhuanpan_light_skillbox3->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox3_light);
	sprite_zhuanpan_light_skillbox4->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox4_light);
	sprite_zhuanpan_light_skillbox5->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox5_light);
	sprite_zhuanpan_light_skillbox6->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox6_light);
	sprite_zhuanpan_light_skillbox7->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox7_light);
	sprite_zhuanpan_light_skillbox8->setTag(scene_game_int_tag_number_sprite_zhuanpan_skillbox8_light);

	sprite_zhuanpan_light_skillbox1->setScale(scal_ZhuanPan);
	sprite_zhuanpan_light_skillbox2->setScale(scal_ZhuanPan);
	sprite_zhuanpan_light_skillbox3->setScale(scal_ZhuanPan);
	sprite_zhuanpan_light_skillbox4->setScale(scal_ZhuanPan);
	sprite_zhuanpan_light_skillbox5->setScale(scal_ZhuanPan);
	sprite_zhuanpan_light_skillbox6->setScale(scal_ZhuanPan);
	sprite_zhuanpan_light_skillbox7->setScale(scal_ZhuanPan);
	sprite_zhuanpan_light_skillbox8->setScale(scal_ZhuanPan);

	sprite_zhuanpan_light_skillbox1->setOpacity(0);
	sprite_zhuanpan_light_skillbox2->setOpacity(0);
	sprite_zhuanpan_light_skillbox3->setOpacity(0);
	sprite_zhuanpan_light_skillbox4->setOpacity(0);
	sprite_zhuanpan_light_skillbox5->setOpacity(0);
	sprite_zhuanpan_light_skillbox6->setOpacity(0);
	sprite_zhuanpan_light_skillbox7->setOpacity(0);
	sprite_zhuanpan_light_skillbox8->setOpacity(0);

	sprite_zhuanpan_light_skillbox1->setPosition(Vec2(visibleSize.width / 2 + radius*sin22_5, visibleSize.height / 3 + radius*cos22_5));
	sprite_zhuanpan_light_skillbox2->setPosition(Vec2(visibleSize.width / 2 + radius*cos22_5, visibleSize.height / 3 + radius*sin22_5));
	sprite_zhuanpan_light_skillbox3->setPosition(Vec2(visibleSize.width / 2 + radius*cos22_5, visibleSize.height / 3 - radius*sin22_5));
	sprite_zhuanpan_light_skillbox4->setPosition(Vec2(visibleSize.width / 2 + radius*sin22_5, visibleSize.height / 3 - radius*cos22_5));
	sprite_zhuanpan_light_skillbox5->setPosition(Vec2(visibleSize.width / 2 - radius*sin22_5, visibleSize.height / 3 - radius*cos22_5));
	sprite_zhuanpan_light_skillbox6->setPosition(Vec2(visibleSize.width / 2 - radius*cos22_5, visibleSize.height / 3 - radius*sin22_5));
	sprite_zhuanpan_light_skillbox7->setPosition(Vec2(visibleSize.width / 2 - radius*cos22_5, visibleSize.height / 3 + radius*sin22_5));
	sprite_zhuanpan_light_skillbox8->setPosition(Vec2(visibleSize.width / 2 - radius*sin22_5, visibleSize.height / 3 + radius*cos22_5));

	/*技能盒结束*/

	/*指针能量槽*/
	auto sprite_pin1_energy1 = Sprite::create("SceneGame/pin/skill_bisha.png");
	auto sprite_pin2_energy1 = Sprite::create("SceneGame/pin/skill_bisha.png");
	auto sprite_pin3_energy1 = Sprite::create("SceneGame/pin/skill_bisha.png");
	auto sprite_pin4_energy1 = Sprite::create("SceneGame/pin/skill_bisha.png");

	sprite_pin1_energy1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	sprite_pin2_energy1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	sprite_pin3_energy1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	sprite_pin4_energy1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));

	sprite_pin1_energy1->setAnchorPoint(Vec2(0.5, -0.09));
	sprite_pin2_energy1->setAnchorPoint(Vec2(0.5, -0.09));
	sprite_pin3_energy1->setAnchorPoint(Vec2(0.5, -0.09));
	sprite_pin4_energy1->setAnchorPoint(Vec2(0.5, -0.09));

	sprite_pin1_energy1->setScale(scal_ZhuanPan);
	sprite_pin2_energy1->setScale(scal_ZhuanPan);
	sprite_pin3_energy1->setScale(scal_ZhuanPan);
	sprite_pin4_energy1->setScale(scal_ZhuanPan);

	sprite_pin1_energy1->setTag(scene_game_int_tag_number_sprite_pin1_energy1);
	sprite_pin2_energy1->setTag(scene_game_int_tag_number_sprite_pin2_energy1);
	sprite_pin3_energy1->setTag(scene_game_int_tag_number_sprite_pin3_energy1);
	sprite_pin4_energy1->setTag(scene_game_int_tag_number_sprite_pin4_energy1);

	sprite_pin1_energy1->setOpacity(0);
	sprite_pin2_energy1->setOpacity(0);
	sprite_pin3_energy1->setOpacity(0);
	sprite_pin4_energy1->setOpacity(0);

	sprite_pin2_energy1->setRotation(90.0f);
	sprite_pin3_energy1->setRotation(180.0f);
	sprite_pin4_energy1->setRotation(270.0f);

	this->addChild(sprite_pin1_energy1, Level_2);
	this->addChild(sprite_pin2_energy1, Level_2);
	this->addChild(sprite_pin3_energy1, Level_2);
	this->addChild(sprite_pin4_energy1, Level_2);

	/*指针能量槽结束*/
	/*
	转盘背景
	*/
	auto spriteBg = Sprite::create("SceneGame/zhuanpan/back.png");

	spriteBg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 3));
	spriteBg->setScale(scal_ZhuanPan);
	this->addChild(spriteBg, Level_0);
	

	auto sprite_monster_bg = Sprite::create("SceneGame/monsterbg.png");
	sprite_monster_bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height *5 / 6));

	scene_game_scale_monster_bg = spriteBg->getContentSize().width / sprite_monster_bg->getContentSize().width *scal_ZhuanPan;
	sprite_monster_bg->setScale(scene_game_scale_monster_bg);
	this->addChild(sprite_monster_bg, Level_0);
	/*
	转盘结束！
	*/
}

void SceneGame::initMonsters(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*
	小怪兽~
	*/
	auto sprite_monster1 = Sprite::create("SceneGame/monster/" + monster1->getName() + ".png");
	auto sprite_monster2 = Sprite::create("SceneGame/monster/" + monster2->getName() + ".png");
	auto sprite_monster3 = Sprite::create("SceneGame/monster/" + monster3->getName() + ".png");
	auto sprite_monster4 = Sprite::create("SceneGame/monster/" + monster4->getName() + ".png");
	auto sprite_monster5 = Sprite::create("SceneGame/monster/" + monster5->getName() + ".png");

	sprite_monster1->setTag(scene_game_int_tag_number_sprite_monster1);
	sprite_monster2->setTag(scene_game_int_tag_number_sprite_monster2);
	sprite_monster3->setTag(scene_game_int_tag_number_sprite_monster3);
	sprite_monster4->setTag(scene_game_int_tag_number_sprite_monster4);
	sprite_monster5->setTag(scene_game_int_tag_number_sprite_monster5);

	float  scal = (visibleSize.height / 4) / sprite_monster5->getContentSize().height;
	sprite_monster1->setScale(scal);
	sprite_monster2->setScale(scal);
	sprite_monster3->setScale(scal);
	sprite_monster4->setScale(scal);
	sprite_monster5->setScale(scal*1.1);
	sprite_monster5->setOpacity(0);
	sprite_monster1->setOpacity(0);
	sprite_monster2->setOpacity(0);
	sprite_monster3->setOpacity(0);
	sprite_monster4->setOpacity(0);
	scene_game_scalNow = scal;

	sprite_monster1->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height * 5 / 6));
	sprite_monster2->setPosition(Vec2(visibleSize.width * 4 / 5 + origin.x, visibleSize.height * 5 / 6));
	sprite_monster3->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height * 5 / 6));
	sprite_monster4->setPosition(Vec2(visibleSize.width * 4 / 5 + origin.x, visibleSize.height * 5 / 6));
	sprite_monster5->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 5 / 6));

	sprite_monster1->setAnchorPoint(Vec2(0.5, 0.5));
	sprite_monster2->setAnchorPoint(Vec2(0.5, 0.5));
	sprite_monster3->setAnchorPoint(Vec2(0.5, 0.5));
	sprite_monster4->setAnchorPoint(Vec2(0.5, 0.5));
	sprite_monster5->setAnchorPoint(Vec2(0.5, 0.50));

	this->addChild(sprite_monster1, Level_1);
	this->addChild(sprite_monster2, Level_1);
	this->addChild(sprite_monster3, Level_1);
	this->addChild(sprite_monster4, Level_1);
	this->addChild(sprite_monster5, Level_1);
	

	/*Boss 血条..*>.<*/
	auto sprite_monster5_hp_bg = Sprite::create("SceneGame/HP/boss/bg_body.png");
	auto sprite_monster5_hp_bg_left = Sprite::create("SceneGame/HP/boss/bg_left.png");
	auto sprite_monster5_hp_bg_right = Sprite::create("SceneGame/HP/boss/bg_right.png");
	auto sprite_monster5_hp_body = Sprite::create("SceneGame/HP/boss/body.png");

	float left_head = sprite_monster5_hp_bg_left->getContentSize().width / 2;
	float right_head = sprite_monster5_hp_bg_right->getContentSize().width / 2;
	float monster_hp_height = visibleSize.height * 5 / 6 - sprite_monster5->getContentSize().height * scal / 2;
	float monster_hp_left = visibleSize.width / 2 - sprite_monster5_hp_bg->getContentSize().width*scene_game_scalZhuanPan / 2 + sprite_monster5_hp_bg_left->getContentSize().width*scene_game_scalZhuanPan / 4;
	float mosnter_hp_right = visibleSize.width / 2 + sprite_monster5_hp_bg->getContentSize().width*scene_game_scalZhuanPan / 2 - sprite_monster5_hp_bg_right->getContentSize().width*scene_game_scalZhuanPan / 4;
	scene_game_scale_monster5_hp = ((sprite_monster5_hp_bg->getContentSize().width - left_head - right_head)*scene_game_scalZhuanPan / (sprite_monster5_hp_body->getContentSize().width));

	sprite_monster5_hp_bg->setScale(scene_game_scalZhuanPan);
	sprite_monster5_hp_bg_left->setScale(scene_game_scalZhuanPan);
	sprite_monster5_hp_bg_right->setScale(scene_game_scalZhuanPan);
	sprite_monster5_hp_body->setScaleX(scene_game_scale_monster5_hp);
	sprite_monster5_hp_body->setScaleY(scene_game_scalZhuanPan);

	sprite_monster5_hp_bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, monster_hp_height));
	sprite_monster5_hp_bg_left->setPosition(Vec2(monster_hp_left + origin.x, monster_hp_height));
	sprite_monster5_hp_bg_right->setPosition(Vec2(mosnter_hp_right + origin.x, monster_hp_height));
	sprite_monster5_hp_body->setPosition(Vec2(monster_hp_left + left_head*scene_game_scalZhuanPan, monster_hp_height));

	sprite_monster5_hp_bg->setTag(scene_game_int_tag_number_sprite_hp_monster5_bg);
	sprite_monster5_hp_bg_left->setTag(scene_game_int_tag_number_sprite_hp_monster5_left);
	sprite_monster5_hp_bg_right->setTag(scene_game_int_tag_number_sprite_hp_monster5_right);
	sprite_monster5_hp_body->setTag(scene_game_int_tag_number_sprite_hp_monster5);


	sprite_monster5_hp_bg->setOpacity(0);
	sprite_monster5_hp_body->setOpacity(0);
	sprite_monster5_hp_bg_left->setOpacity(0);
	sprite_monster5_hp_bg_right->setOpacity(0);

	sprite_monster5_hp_body->setAnchorPoint(Vec2(0, 0.5));

	addChild(sprite_monster5_hp_body, Level_2);
	addChild(sprite_monster5_hp_bg, Level_1);
	addChild(sprite_monster5_hp_bg_left, Level_3);
	addChild(sprite_monster5_hp_bg_right, Level_3);

	/*小怪兽血条~~*/

	auto sprite_monster1_hp_bg = Sprite::create("SceneGame/HP/normalMonster/bg_body.png");
	auto sprite_monster1_hp_bg_left = Sprite::create("SceneGame/HP/normalMonster/bg_left.png");
	auto sprite_monster1_hp_bg_right = Sprite::create("SceneGame/HP/normalMonster/bg_right.png");
	auto sprite_monster1_hp_body = Sprite::create("SceneGame/HP/normalMonster/body.png");

	left_head = sprite_monster1_hp_bg_left->getContentSize().width / 2;
	right_head = sprite_monster1_hp_bg_right->getContentSize().width / 2;
	monster_hp_height = visibleSize.height * 5 / 6 - sprite_monster1->getContentSize().height *  scal / 2;
	monster_hp_left = visibleSize.width / 5 - sprite_monster1_hp_bg->getContentSize().width*scene_game_scalZhuanPan / 2 + sprite_monster1_hp_bg_left->getContentSize().width*scene_game_scalZhuanPan / 6;
	mosnter_hp_right = visibleSize.width / 5 + sprite_monster1_hp_bg->getContentSize().width*scene_game_scalZhuanPan / 2 - sprite_monster1_hp_bg_right->getContentSize().width*scene_game_scalZhuanPan / 6;
	scene_game_scale_monster1_hp = ((sprite_monster1_hp_bg->getContentSize().width - left_head - right_head)*scene_game_scalZhuanPan / (sprite_monster1_hp_body->getContentSize().width));

	sprite_monster1_hp_bg->setScale(scene_game_scalZhuanPan);
	sprite_monster1_hp_bg_left->setScale(scene_game_scalZhuanPan);
	sprite_monster1_hp_bg_right->setScale(scene_game_scalZhuanPan);
	sprite_monster1_hp_body->setScaleX(scene_game_scale_monster1_hp);
	sprite_monster1_hp_body->setScaleY(scene_game_scalZhuanPan);

	sprite_monster1_hp_bg->setPosition(Vec2(visibleSize.width / 5 + origin.x, monster_hp_height));
	sprite_monster1_hp_bg_left->setPosition(Vec2(monster_hp_left + origin.x, monster_hp_height));
	sprite_monster1_hp_bg_right->setPosition(Vec2(mosnter_hp_right + origin.x, monster_hp_height));
	sprite_monster1_hp_body->setPosition(Vec2(monster_hp_left + left_head*scene_game_scalZhuanPan / 2, monster_hp_height));

	sprite_monster1_hp_bg->setTag(scene_game_int_tag_number_sprite_hp_monster1_bg);
	sprite_monster1_hp_bg_left->setTag(scene_game_int_tag_number_sprite_hp_monster1_left);
	sprite_monster1_hp_bg_right->setTag(scene_game_int_tag_number_sprite_hp_monster1_right);
	sprite_monster1_hp_body->setTag(scene_game_int_tag_number_sprite_hp_monster1);

	sprite_monster1_hp_body->setAnchorPoint(Vec2(0, 0.5));

	sprite_monster1_hp_bg->setOpacity(0);
	sprite_monster1_hp_body->setOpacity(0);
	sprite_monster1_hp_bg_left->setOpacity(0);
	sprite_monster1_hp_bg_right->setOpacity(0);

	addChild(sprite_monster1_hp_body, Level_2);
	addChild(sprite_monster1_hp_bg, Level_1);
	addChild(sprite_monster1_hp_bg_left, Level_3);
	addChild(sprite_monster1_hp_bg_right, Level_3);

	auto sprite_monster2_hp_bg = Sprite::create("SceneGame/HP/normalMonster/bg_body.png");
	auto sprite_monster2_hp_bg_left = Sprite::create("SceneGame/HP/normalMonster/bg_left.png");
	auto sprite_monster2_hp_bg_right = Sprite::create("SceneGame/HP/normalMonster/bg_right.png");
	auto sprite_monster2_hp_body = Sprite::create("SceneGame/HP/normalMonster/body.png");

	left_head = sprite_monster2_hp_bg_left->getContentSize().width / 2;
	right_head = sprite_monster2_hp_bg_right->getContentSize().width / 2;
	monster_hp_height = visibleSize.height * 5 / 6 - sprite_monster2->getContentSize().height *  scal / 2;
	monster_hp_left = visibleSize.width * 4 / 5 - sprite_monster2_hp_bg->getContentSize().width*scene_game_scalZhuanPan / 2 + sprite_monster2_hp_bg_left->getContentSize().width*scene_game_scalZhuanPan / 6;
	mosnter_hp_right = visibleSize.width * 4 / 5 + sprite_monster2_hp_bg->getContentSize().width*scene_game_scalZhuanPan / 2 - sprite_monster2_hp_bg_right->getContentSize().width*scene_game_scalZhuanPan / 6;
	scene_game_scale_monster2_hp = ((sprite_monster2_hp_bg->getContentSize().width - left_head - right_head)*scene_game_scalZhuanPan / (sprite_monster2_hp_body->getContentSize().width));

	sprite_monster2_hp_bg->setScale(scene_game_scalZhuanPan);
	sprite_monster2_hp_bg_left->setScale(scene_game_scalZhuanPan);
	sprite_monster2_hp_bg_right->setScale(scene_game_scalZhuanPan);
	sprite_monster2_hp_body->setScaleX(scene_game_scale_monster2_hp);
	sprite_monster2_hp_body->setScaleY(scene_game_scalZhuanPan);

	sprite_monster2_hp_bg->setPosition(Vec2(visibleSize.width * 4 / 5 + origin.x, monster_hp_height));
	sprite_monster2_hp_bg_left->setPosition(Vec2(monster_hp_left + origin.x, monster_hp_height));
	sprite_monster2_hp_bg_right->setPosition(Vec2(mosnter_hp_right + origin.x, monster_hp_height));
	sprite_monster2_hp_body->setPosition(Vec2(monster_hp_left + left_head*scene_game_scalZhuanPan / 2, monster_hp_height));

	sprite_monster2_hp_bg->setTag(scene_game_int_tag_number_sprite_hp_monster2_bg);
	sprite_monster2_hp_bg_left->setTag(scene_game_int_tag_number_sprite_hp_monster2_left);
	sprite_monster2_hp_bg_right->setTag(scene_game_int_tag_number_sprite_hp_monster2_right);
	sprite_monster2_hp_body->setTag(scene_game_int_tag_number_sprite_hp_monster2);

	sprite_monster2_hp_body->setAnchorPoint(Vec2(0, 0.5));

	sprite_monster2_hp_bg->setOpacity(0);
	sprite_monster2_hp_body->setOpacity(0);
	sprite_monster2_hp_bg_left->setOpacity(0);
	sprite_monster2_hp_bg_right->setOpacity(0);

	addChild(sprite_monster2_hp_body, Level_2);
	addChild(sprite_monster2_hp_bg, Level_1);
	addChild(sprite_monster2_hp_bg_left, Level_3);
	addChild(sprite_monster2_hp_bg_right, Level_3);


	auto sprite_monster3_hp_bg = Sprite::create("SceneGame/HP/normalMonster/bg_body.png");
	auto sprite_monster3_hp_bg_left = Sprite::create("SceneGame/HP/normalMonster/bg_left.png");
	auto sprite_monster3_hp_bg_right = Sprite::create("SceneGame/HP/normalMonster/bg_right.png");
	auto sprite_monster3_hp_body = Sprite::create("SceneGame/HP/normalMonster/body.png");

	left_head = sprite_monster3_hp_bg_left->getContentSize().width / 2;
	right_head = sprite_monster3_hp_bg_right->getContentSize().width / 2;
	monster_hp_height = visibleSize.height * 5 / 6 - sprite_monster3->getContentSize().height *  scal / 2;
	monster_hp_left = visibleSize.width / 5 - sprite_monster3_hp_bg->getContentSize().width*scene_game_scalZhuanPan / 2 + sprite_monster3_hp_bg_left->getContentSize().width*scene_game_scalZhuanPan / 6;
	mosnter_hp_right = visibleSize.width / 5 + sprite_monster3_hp_bg->getContentSize().width*scene_game_scalZhuanPan / 2 - sprite_monster3_hp_bg_right->getContentSize().width*scene_game_scalZhuanPan / 6;
	scene_game_scale_monster3_hp = ((sprite_monster3_hp_bg->getContentSize().width - left_head - right_head)*scene_game_scalZhuanPan / (sprite_monster3_hp_body->getContentSize().width));

	sprite_monster3_hp_bg->setScale(scene_game_scalZhuanPan);
	sprite_monster3_hp_bg_left->setScale(scene_game_scalZhuanPan);
	sprite_monster3_hp_bg_right->setScale(scene_game_scalZhuanPan);
	sprite_monster3_hp_body->setScaleX(scene_game_scale_monster3_hp);
	sprite_monster3_hp_body->setScaleY(scene_game_scalZhuanPan);

	sprite_monster3_hp_bg->setPosition(Vec2(visibleSize.width / 5 + origin.x, monster_hp_height));
	sprite_monster3_hp_bg_left->setPosition(Vec2(monster_hp_left + origin.x, monster_hp_height));
	sprite_monster3_hp_bg_right->setPosition(Vec2(mosnter_hp_right + origin.x, monster_hp_height));
	sprite_monster3_hp_body->setPosition(Vec2(monster_hp_left + left_head*scene_game_scalZhuanPan / 2, monster_hp_height));

	sprite_monster3_hp_bg->setTag(scene_game_int_tag_number_sprite_hp_monster3_bg);
	sprite_monster3_hp_bg_left->setTag(scene_game_int_tag_number_sprite_hp_monster3_left);
	sprite_monster3_hp_bg_right->setTag(scene_game_int_tag_number_sprite_hp_monster3_right);
	sprite_monster3_hp_body->setTag(scene_game_int_tag_number_sprite_hp_monster3);

	sprite_monster3_hp_body->setAnchorPoint(Vec2(0, 0.5));

	sprite_monster3_hp_bg->setOpacity(0);
	sprite_monster3_hp_body->setOpacity(0);
	sprite_monster3_hp_bg_left->setOpacity(0);
	sprite_monster3_hp_bg_right->setOpacity(0);

	addChild(sprite_monster3_hp_body, Level_2);
	addChild(sprite_monster3_hp_bg, Level_1);
	addChild(sprite_monster3_hp_bg_left, Level_3);
	addChild(sprite_monster3_hp_bg_right, Level_3);

	auto sprite_monster4_hp_bg = Sprite::create("SceneGame/HP/normalMonster/bg_body.png");
	auto sprite_monster4_hp_bg_left = Sprite::create("SceneGame/HP/normalMonster/bg_left.png");
	auto sprite_monster4_hp_bg_right = Sprite::create("SceneGame/HP/normalMonster/bg_right.png");
	auto sprite_monster4_hp_body = Sprite::create("SceneGame/HP/normalMonster/body.png");

	left_head = sprite_monster4_hp_bg_left->getContentSize().width / 2;
	right_head = sprite_monster4_hp_bg_right->getContentSize().width / 2;
	monster_hp_height = visibleSize.height * 5 / 6 - sprite_monster4->getContentSize().height *  scal / 2;
	monster_hp_left = visibleSize.width * 4 / 5 - sprite_monster4_hp_bg->getContentSize().width*scene_game_scalZhuanPan / 2 + sprite_monster4_hp_bg_left->getContentSize().width*scene_game_scalZhuanPan / 6;
	mosnter_hp_right = visibleSize.width * 4 / 5 + sprite_monster4_hp_bg->getContentSize().width*scene_game_scalZhuanPan / 2 - sprite_monster4_hp_bg_right->getContentSize().width*scene_game_scalZhuanPan / 6;
	scene_game_scale_monster4_hp = ((sprite_monster4_hp_bg->getContentSize().width - left_head - right_head)*scene_game_scalZhuanPan / (sprite_monster4_hp_body->getContentSize().width));

	sprite_monster4_hp_bg->setScale(scene_game_scalZhuanPan);
	sprite_monster4_hp_bg_left->setScale(scene_game_scalZhuanPan);
	sprite_monster4_hp_bg_right->setScale(scene_game_scalZhuanPan);
	sprite_monster4_hp_body->setScaleX(scene_game_scale_monster4_hp);
	sprite_monster4_hp_body->setScaleY(scene_game_scalZhuanPan);

	sprite_monster4_hp_bg->setPosition(Vec2(visibleSize.width * 4 / 5 + origin.x, monster_hp_height));
	sprite_monster4_hp_bg_left->setPosition(Vec2(monster_hp_left + origin.x, monster_hp_height));
	sprite_monster4_hp_bg_right->setPosition(Vec2(mosnter_hp_right + origin.x, monster_hp_height));
	sprite_monster4_hp_body->setPosition(Vec2(monster_hp_left + left_head*scene_game_scalZhuanPan / 2, monster_hp_height));

	sprite_monster4_hp_bg->setTag(scene_game_int_tag_number_sprite_hp_monster4_bg);
	sprite_monster4_hp_bg_left->setTag(scene_game_int_tag_number_sprite_hp_monster4_left);
	sprite_monster4_hp_bg_right->setTag(scene_game_int_tag_number_sprite_hp_monster4_right);
	sprite_monster4_hp_body->setTag(scene_game_int_tag_number_sprite_hp_monster4);

	sprite_monster4_hp_body->setAnchorPoint(Vec2(0, 0.5));

	sprite_monster4_hp_bg->setOpacity(0);
	sprite_monster4_hp_body->setOpacity(0);
	sprite_monster4_hp_bg_left->setOpacity(0);
	sprite_monster4_hp_bg_right->setOpacity(0);

	addChild(sprite_monster4_hp_body, Level_2);
	addChild(sprite_monster4_hp_bg, Level_1);
	addChild(sprite_monster4_hp_bg_left, Level_3);
	addChild(sprite_monster4_hp_bg_right, Level_3);

}

void SceneGame::show_monster1_hp(bool show){
	if (show){
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster1_bg)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster1_left)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster1_right)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster1)->runAction(FadeIn::create(0.2f));
	}
	else{
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster1_bg)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster1_left)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster1_right)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster1)->runAction(FadeOut::create(0.2f));
	}
}

void SceneGame::show_monster2_hp(bool show){
	if (show){
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster2_bg)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster2_left)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster2_right)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster2)->runAction(FadeIn::create(0.2f));
	}
	else{
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster2_bg)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster2_left)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster2_right)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster2)->runAction(FadeOut::create(0.2f));
	}
}

void SceneGame::show_monster3_hp(bool show){
	if (show){
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster3_bg)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster3_left)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster3_right)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster3)->runAction(FadeIn::create(0.2f));
	}
	else{
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster3_bg)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster3_left)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster3_right)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster3)->runAction(FadeOut::create(0.2f));
	}
}

void SceneGame::show_monster4_hp(bool show){
	if (show){
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster4_bg)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster4_left)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster4_right)->runAction(FadeIn::create(0.2f));
getChildByTag(scene_game_int_tag_number_sprite_hp_monster4)->runAction(FadeIn::create(0.2f));
	}
	else{
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster4_bg)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster4_left)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster4_right)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster4)->runAction(FadeOut::create(0.2f));
	}
}

void SceneGame::show_monster5_hp(bool show){
	if (show){
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster5_bg)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster5_left)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster5_right)->runAction(FadeIn::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster5)->runAction(FadeIn::create(0.2f));
	}
	else{
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster5_bg)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster5_left)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster5_right)->runAction(FadeOut::create(0.2f));
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster5)->runAction(FadeOut::create(0.2f));
	}
}

void SceneGame::zhuanpanActionFinished(){
	scene_game_bool_touched = false;
	int index_of_skill_box_monster1 = (accumulated_angle / 45) % 8;
	int index_of_skill_box_monster2 = ((accumulated_angle + 90) / 45) % 8;
	int index_of_skill_box_monster3 = ((accumulated_angle + 180) / 45) % 8;
	int index_of_skill_box_monster4 = ((accumulated_angle + 270) / 45) % 8;
	switch (player_attack_counter){
	case 1:	
		if (skillbox_type[index_of_skill_box_monster1] != 4){
			msg->setType(skillbox_type[index_of_skill_box_monster1]);
			nomralZhuanPanSkillAction(PlayerMonster1->monster_AttackOthers(msg));
		}
		else{
			monster1_energy_accumulate();
		}
		break;
	case 2:
		if (skillbox_type[index_of_skill_box_monster2] != 4){
			msg->setType(skillbox_type[index_of_skill_box_monster2]);
			nomralZhuanPanSkillAction(PlayerMonster2->monster_AttackOthers(msg));
		}
		else{
			monster2_energy_accumulate();
		}
		break;
	case 3:
		if (skillbox_type[index_of_skill_box_monster3] != 4){
			msg->setType(skillbox_type[index_of_skill_box_monster3]);
			nomralZhuanPanSkillAction(PlayerMonster3->monster_AttackOthers(msg));
		}
		else{
			monster3_energy_accumulate();
		}
		break;
	case 4:
		if (skillbox_type[index_of_skill_box_monster4] != 4){
			msg->setType(skillbox_type[index_of_skill_box_monster4]);
			nomralZhuanPanSkillAction(PlayerMonster4->monster_AttackOthers(msg));
		}
		else{
			monster4_energy_accumulate();
		}
		break;
	}
}

void SceneGame::nomralZhuanPanSkillAction(AttackMessage* received_msg){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto splade1 = MotionStreak::create(1.0f, 9.0f, 9.0f, Color3B(255, 255, 255), "SceneGame/MotionStreak.png");
	removeChildByTag(scene_game_int_tag_number_attack_effect2);
	removeChildByTag(scene_game_int_tag_number_attack_effect3);
	std::stringstream str_stream_temp;
	std::string str_temp;
	int temp = rand() % 100;
	float a = visibleSize.height - 200 + temp;
	float b = visibleSize.width/2;
	this->addChild(splade1, Level_2);
	splade1->setPosition(Vec2(b, visibleSize.height - temp));
	splade1->setTag(scene_game_int_tag_number_attack_effect1);
	
	switch (this->level){
	case 0:{
		//0:nothing, 1：攻击 2:恢复 3: 减少伤害 4: 增加power 5: 按百分比攻击 6： 按百分比回复
		switch (received_msg->getSkillEffectNo()){
		case 0: break;
		case 1:
			if (monster1->isAlive()){
				if(monster1->monster_beAttackedBy(received_msg->getEffect(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);;
				getChildByTag(scene_game_int_tag_number_sprite_monster1)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
				splade1->runAction(UtilAttackMove::create(0.5f, b, visibleSize.height - temp, 0, a));


				str_stream_temp << "-" << received_msg->getEffect();
				str_temp = str_stream_temp.str();

				auto label1 = LabelTTF::create(str_temp, "Arial", 24);
				label1->setColor(ccColor3B::RED);
				label1->setPosition(Vec2(visibleSize.width / 5, visibleSize.height * 7 / 8));
				label1->setOpacity(0);
				label1->setTag(scene_game_int_tag_number_label_monster1_attack_text);
				addChild(label1, Level_3);
				label1->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}
			else
				if (monster2->isAlive()){
				if(monster2->monster_beAttackedBy(received_msg->getEffect(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);;
				getChildByTag(scene_game_int_tag_number_sprite_monster2)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
				splade1->runAction(UtilAttackMove::create(0.5f, b, visibleSize.height - temp, b * 2, a));


				str_stream_temp << "-" << received_msg->getEffect();
				str_temp = str_stream_temp.str();

				auto label2 = LabelTTF::create(str_temp, "Arial", 24);
				label2->setColor(ccColor3B::RED);
				label2->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 7 / 8));
				label2->setOpacity(0);
				label2->setTag(scene_game_int_tag_number_label_monster2_attack_text);
				addChild(label2, Level_3);
				label2->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
				}
			break;
		case 2:
			playerHP += received_msg->getEffect();
			effect_Heal(visibleSize);
			str_stream_temp << "+" << received_msg->getEffect()*player_hp_total;

			str_temp = str_stream_temp.str();
			if (true){
				auto label_recover1 = LabelTTF::create(str_temp, "Arial", 24);
				label_recover1->setColor(ccColor3B::GREEN);
				label_recover1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
				label_recover1->setOpacity(0);
				label_recover1->setTag(scene_game_int_tag_number_label_hp_player_recover);
				addChild(label_recover1, Level_3);
				label_recover1->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}
			if (playerHP > player_hp_total)
				playerHP = player_hp_total;
			break;
		case 3:
			scene_game_demage_fiex = received_msg->getEffect();
			scene_game_damage_counter = received_msg->getEffectiveTime();
			effect_Debuff(visibleSize);
			break;
		case 4:
			if (PlayerMonster1->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster1->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster2->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster2->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster3->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster3->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster4->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster4->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			effect_Enhance(visibleSize);
			break;
			
		case 5:
			if (monster1->isAlive()){
				if(monster1->monster_beAttackedBy(received_msg->getEffect()*monster1->monster_get_hp_total(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);;
				getChildByTag(scene_game_int_tag_number_sprite_monster1)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
				splade1->runAction(UtilAttackMove::create(0.5f, b, visibleSize.height - temp, 0, a));

				str_stream_temp << "-" << received_msg->getEffect()*monster1->monster_get_hp_total();
				str_temp = str_stream_temp.str();

				auto label1 = LabelTTF::create(str_temp, "Arial", 24);
				label1->setColor(ccColor3B::RED);
				label1->setPosition(Vec2(visibleSize.width / 5, visibleSize.height * 7 / 8));
				label1->setOpacity(0);
				label1->setTag(scene_game_int_tag_number_label_monster1_attack_text);
				addChild(label1, Level_3);
				label1->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));

			}
			else
				if (monster2->isAlive()){
					if(monster2->monster_beAttackedBy(received_msg->getEffect()*monster2->monster_get_hp_total(), received_msg->getSkillProperty(), false))
						received_msg->setEffect(received_msg->getEffect() * 2);;
					getChildByTag(scene_game_int_tag_number_sprite_monster2)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
					splade1->runAction(UtilAttackMove::create(0.5f, b, visibleSize.height - temp, b * 2, a));
					

					str_stream_temp << "-" << received_msg->getEffect()*monster2->monster_get_hp_total();
					str_temp = str_stream_temp.str();

					auto label2 = LabelTTF::create(str_temp, "Arial", 24);
					label2->setColor(ccColor3B::RED);
					label2->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 7 / 8));
					label2->setOpacity(0);
					label2->setTag(scene_game_int_tag_number_label_monster2_attack_text);
					addChild(label2, Level_3);
					label2->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
				}
			break;
		case 6:
			playerHP += received_msg->getEffect()*player_hp_total;

			str_stream_temp << "+" << received_msg->getEffect()*player_hp_total;
			effect_Heal(visibleSize);
			str_temp = str_stream_temp.str();

			auto label_recover2 = LabelTTF::create(str_temp, "Arial", 24);
			label_recover2->setColor(ccColor3B::GREEN);
			label_recover2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
			label_recover2->setOpacity(0);
			label_recover2->setTag(scene_game_int_tag_number_label_hp_player_recover);
			addChild(label_recover2, Level_3);
			label_recover2->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));

			if (playerHP > player_hp_total)
				playerHP = player_hp_total;
			break;
		}
		break;
	}
	case 1:{
		switch (received_msg->getSkillEffectNo()){
		case 0: break;
		case 1:
			if (monster3->isAlive()){
				if (monster3->monster_beAttackedBy(received_msg->getEffect(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect()*2);
				getChildByTag(scene_game_int_tag_number_sprite_monster3)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
				splade1->runAction(UtilAttackMove::create(0.5f, b, visibleSize.height - temp, 0, a));

				str_stream_temp << "-" << received_msg->getEffect();
				str_temp = str_stream_temp.str();

				auto label3 = LabelTTF::create(str_temp, "Arial", 24);
				label3->setColor(ccColor3B::RED);
				label3->setPosition(Vec2(visibleSize.width / 5, visibleSize.height * 7 / 8));
				label3->setOpacity(0);
				label3->setTag(scene_game_int_tag_number_label_monster3_attack_text);
				addChild(label3, Level_3);
				label3->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}
			else
				if (monster4->isAlive()){
				if(monster4->monster_beAttackedBy(received_msg->getEffect(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);;
				getChildByTag(scene_game_int_tag_number_sprite_monster4)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
				splade1->runAction(UtilAttackMove::create(0.5f, b, visibleSize.height - temp, b * 2, a));

				str_stream_temp << "-" << received_msg->getEffect();
				str_temp = str_stream_temp.str();

				auto label4 = LabelTTF::create(str_temp, "Arial", 24);
				label4->setColor(ccColor3B::RED);
				label4->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 7 / 8));
				label4->setOpacity(0);
				label4->setTag(scene_game_int_tag_number_label_monster4_attack_text);
				addChild(label4, Level_3);
				label4->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));

				}
			break;
		case 2:
			playerHP += received_msg->getEffect();
			str_stream_temp << "+" << received_msg->getEffect()*player_hp_total;
			effect_Heal(visibleSize);
			str_temp = str_stream_temp.str();
			if (true){
				auto label_recover3 = LabelTTF::create(str_temp, "Arial", 24);
				label_recover3->setColor(ccColor3B::GREEN);
				label_recover3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
				label_recover3->setOpacity(0);
				label_recover3->setTag(scene_game_int_tag_number_label_hp_player_recover);
				addChild(label_recover3, Level_3);
				label_recover3->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}

			if (playerHP > player_hp_total)
				playerHP = player_hp_total;
			break;
		case 3:
			scene_game_demage_fiex = received_msg->getEffect();
			scene_game_damage_counter = received_msg->getEffectiveTime();
			effect_Debuff(visibleSize);
			break;
		case 4:
			if (PlayerMonster1->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster1->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster2->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster2->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster3->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster3->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster4->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster4->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			effect_Enhance(visibleSize);
			break;

		case 5:
			if (monster3->isAlive()){
				if(monster3->monster_beAttackedBy(received_msg->getEffect()*monster3->monster_get_hp_total(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);;
				getChildByTag(scene_game_int_tag_number_sprite_monster3)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
				splade1->runAction(UtilAttackMove::create(0.5f, b, visibleSize.height - temp, 0, a));

				str_stream_temp << "-" << received_msg->getEffect()*monster3->monster_get_hp_total();
				str_temp = str_stream_temp.str();

				auto label3 = LabelTTF::create(str_temp, "Arial", 24);
				label3->setColor(ccColor3B::RED);
				label3->setPosition(Vec2(visibleSize.width / 5, visibleSize.height * 7 / 8));
				label3->setOpacity(0);
				label3->setTag(scene_game_int_tag_number_label_monster3_attack_text);
				addChild(label3, Level_3);
				label3->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}
			else
				if (monster4->isAlive()){
				if(monster4->monster_beAttackedBy(received_msg->getEffect()*monster4->monster_get_hp_total(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);;

				getChildByTag(scene_game_int_tag_number_sprite_monster4)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
				splade1->runAction(UtilAttackMove::create(0.5f, b, visibleSize.height - temp, b * 2, a));
				
				str_stream_temp << "-" << received_msg->getEffect()*monster4->monster_get_hp_total();
				str_temp = str_stream_temp.str();

				auto label4 = LabelTTF::create(str_temp, "Arial", 24);
				label4->setColor(ccColor3B::RED);
				label4->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height *7 / 8));
				label4->setOpacity(0);
				label4->setTag(scene_game_int_tag_number_label_monster4_attack_text);
				addChild(label4, Level_3);
				label4->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
				}
			break;
		case 6:
			playerHP += received_msg->getEffect()*player_hp_total;
			str_stream_temp << "+" << received_msg->getEffect()*player_hp_total;
			effect_Heal(visibleSize);
			str_temp = str_stream_temp.str();

			auto label_recover6 = LabelTTF::create(str_temp, "Arial", 24);
			label_recover6->setColor(ccColor3B::GREEN);
			label_recover6->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
			label_recover6->setOpacity(0);
			label_recover6->setTag(scene_game_int_tag_number_label_hp_player_recover);
			addChild(label_recover6, Level_3);
			label_recover6->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			if (playerHP > player_hp_total)
				playerHP = player_hp_total;
			break;
		}
		break;
	}
	case 2:{
		switch (received_msg->getSkillEffectNo()){
		case 0: break;
		case 1:
			if (monster5->isAlive()){
				if(monster5->monster_beAttackedBy(received_msg->getEffect(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);
				getChildByTag(scene_game_int_tag_number_sprite_monster5)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
				splade1->runAction(UtilAttackMove::create(0.5f, 0, visibleSize.height - temp, b * 2, a));

				str_stream_temp << "-" << received_msg->getEffect();
				str_temp = str_stream_temp.str();

				auto label5 = LabelTTF::create(str_temp, "Arial", 24);
				label5->setColor(ccColor3B::RED);
				label5->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 7 / 8));
				label5->setOpacity(0);
				label5->setTag(scene_game_int_tag_number_label_monster5_attack_text);
				addChild(label5, Level_3);
				label5->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}

			break;
		case 2:
			playerHP += received_msg->getEffect();
			str_stream_temp << "+" << received_msg->getEffect();

			str_temp = str_stream_temp.str();
			if (true){
				auto label_recover7 = LabelTTF::create(str_temp, "Arial", 24);
				label_recover7->setColor(ccColor3B::GREEN);
				label_recover7->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
				label_recover7->setOpacity(0);
				label_recover7->setTag(scene_game_int_tag_number_label_hp_player_recover);
				addChild(label_recover7, Level_3);
				label_recover7->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}
			effect_Heal(visibleSize);
			if (playerHP > player_hp_total)
				playerHP = player_hp_total;
			break;
		case 3:
			scene_game_demage_fiex = received_msg->getEffect();
			scene_game_damage_counter = received_msg->getEffectiveTime();
			effect_Debuff(visibleSize);
			break;
		case 4:
			if (PlayerMonster1->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster1->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster2->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster2->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster3->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster3->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster4->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster4->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			effect_Enhance(visibleSize);
			break;
		case 5:
			if (monster5->isAlive()){
				if(monster5->monster_beAttackedBy(received_msg->getEffect()*monster5->monster_get_hp_total(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);
				getChildByTag(scene_game_int_tag_number_sprite_monster5)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
				splade1->runAction(UtilAttackMove::create(0.5f, b, visibleSize.height - temp, 0, a));
				
				str_stream_temp << "-" << received_msg->getEffect()*monster5->monster_get_hp_total();
				str_temp = str_stream_temp.str();

				auto label5 = LabelTTF::create(str_temp, "Arial", 24);
				label5->setColor(ccColor3B::RED);
				label5->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 7 / 8));
				label5->setOpacity(0);
				label5->setTag(scene_game_int_tag_number_label_monster5_attack_text);
				addChild(label5, Level_3);
				label5->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}
			break;
		case 6:
			playerHP += received_msg->getEffect()*player_hp_total;
			str_stream_temp << "+" << received_msg->getEffect()*player_hp_total;

			str_temp = str_stream_temp.str();

			effect_Heal(visibleSize);

			auto label_recover9 = LabelTTF::create(str_temp, "Arial", 24);
			label_recover9->setColor(ccColor3B::GREEN);
			label_recover9->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
			label_recover9->setOpacity(0);
			label_recover9->setTag(scene_game_int_tag_number_label_hp_player_recover);
			addChild(label_recover9, Level_3);
			label_recover9->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));

			if (playerHP > player_hp_total)
				playerHP = player_hp_total;
			break;
		}
		break;
	}
	}
}

void SceneGame::AttackByEnemy(){
	std::stringstream str_stream_temp;
	std::stringstream str_stream_temp2;
	std::string str_temp;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	std::string attackEffect1="enemy_attack_effect", attackEffect2="enemy_attack_effect";
	if (level == 0){
		attackEffect1 = monster1->getAttackPng();
		attackEffect2 = monster2->getAttackPng();
	}
	if (level == 1){
		attackEffect1 = monster3->getAttackPng();
		attackEffect2 = monster4->getAttackPng();
	}
	if (level == 2){
		attackEffect1 = monster5->getAttackPng();
		attackEffect2 = monster5->getAttackPng();
	}

	auto splade2 = MotionStreak::create(1.0f, 4.0f, 25.0f, Color3B(255, 255, 255), "SceneGame/attack/" + attackEffect1 + ".png");
	auto splade3 = MotionStreak::create(1.0f, 4.0f, 25.0f, Color3B(255, 255, 255), "SceneGame/attack/" + attackEffect2 + ".png");
	
	this->addChild(splade2, Level_2);
	this->addChild(splade3, Level_2);
	splade2->setPosition(Vec2(visibleSize.width/5, visibleSize.height*5/6));
	splade3->setPosition(Vec2(visibleSize.width*4/5, visibleSize.height*5/6));
	splade2->setTag(scene_game_int_tag_number_attack_effect2);
	splade3->setTag(scene_game_int_tag_number_attack_effect3);

	switch (level)
	{
	case 0:
		if (monster1->isAlive()){
			msg = monster1->monster_AttackOthers();
			playerHP -= msg->getEffect()*scene_game_demage_fiex;
			if (scene_game_demage_fiex != 1){
				scene_game_damage_counter--;
				if (scene_game_damage_counter <= 0){
					scene_game_demage_fiex = 1;
				}
			
			}
			str_stream_temp << "-" << msg->getEffect()*scene_game_demage_fiex;
			str_temp = str_stream_temp.str();

			auto label1 = LabelTTF::create(str_temp, "Arial", 24);
			label1->setColor(ccColor3B::RED);
			label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *  3 / 4));
			label1->setOpacity(0);
			label1->setTag(scene_game_int_tag_number_label_player_be_attacked1_text);
			addChild(label1, Level_3);
			label1->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			splade2->runAction(UtilAttackMove::create(0.5f, 0, visibleSize.height, visibleSize.width/2, visibleSize.height / 3));
		}
		if (monster2->isAlive()){
			msg = monster2->monster_AttackOthers();
			playerHP -= msg->getEffect()*scene_game_demage_fiex;
			if (scene_game_demage_fiex != 1){
				scene_game_damage_counter--;
				if (scene_game_damage_counter < 0){
					scene_game_demage_fiex = 1;
				}
			}
			
			str_stream_temp2 << "-" << msg->getEffect()*scene_game_demage_fiex;
			str_temp = str_stream_temp2.str();
			auto label1 = LabelTTF::create(str_temp, "Arial", 24);
			label1->setColor(ccColor3B::RED);
			label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 11 / 16));
			label1->setOpacity(0);
			label1->setTag(scene_game_int_tag_number_label_player_be_attacked2_text);
			addChild(label1, Level_3);
			label1->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			splade3->runAction(UtilAttackMove::create(0.5f, visibleSize.width, visibleSize.height, visibleSize.width / 2, visibleSize.height / 3));
		}
		break;
	case 1:
		if (monster3->isAlive()){
			msg = monster3->monster_AttackOthers();
			playerHP -= msg->getEffect()*scene_game_demage_fiex;
			if (scene_game_demage_fiex != 1){
				scene_game_damage_counter--;
				if (scene_game_damage_counter < 0){
					scene_game_demage_fiex = 1;
					
				}

			}
			str_stream_temp << "-" << msg->getEffect()*scene_game_demage_fiex;
			str_temp = str_stream_temp.str();

			auto label1 = LabelTTF::create(str_temp, "Arial", 24);
			label1->setColor(ccColor3B::RED);
			label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *  3 / 4));
			label1->setOpacity(0);
			label1->setTag(scene_game_int_tag_number_label_player_be_attacked1_text);
			addChild(label1, Level_3);
			label1->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			splade2->runAction(UtilAttackMove::create(0.8f, 0, visibleSize.height, visibleSize.width / 2, visibleSize.height / 3));
		}
		if (monster4->isAlive()){
			msg = monster4->monster_AttackOthers();
			playerHP -= msg->getEffect()*scene_game_demage_fiex;
		
			if (scene_game_demage_fiex != 1){
				scene_game_damage_counter--;
				if (scene_game_damage_counter < 0){
					scene_game_demage_fiex = 1;
				}
			}

			str_stream_temp2 << "-" << msg->getEffect()*scene_game_demage_fiex;
			str_temp = str_stream_temp2.str();
			auto label1 = LabelTTF::create(str_temp, "Arial", 24);
			label1->setColor(ccColor3B::RED);
			label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 11 / 16));
			label1->setOpacity(0);
			label1->setTag(scene_game_int_tag_number_label_player_be_attacked2_text);
			addChild(label1, Level_3);
			label1->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			splade3->runAction(UtilAttackMove::create(0.8f, visibleSize.width, visibleSize.height, visibleSize.width / 2, visibleSize.height / 3));
		}
		break;
	case 2:
		if (monster5->isAlive()){
			msg = monster5->monster_AttackOthers();
			playerHP -= msg->getEffect()*scene_game_demage_fiex;
			if (scene_game_demage_fiex != 1){
				scene_game_damage_counter--;
				if (scene_game_damage_counter < 0){
					scene_game_demage_fiex = 1;
				}
			}
			str_stream_temp << "-" << msg->getEffect()*scene_game_demage_fiex;
			str_temp = str_stream_temp.str();
			auto label1 = LabelTTF::create(str_temp, "Arial", 24);
			label1->setColor(ccColor3B::RED);
			label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *  3 / 4));
			label1->setOpacity(0);
			label1->setTag(scene_game_int_tag_number_label_player_be_attacked2_text);
			addChild(label1, Level_3);
			label1->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));

			splade2->runAction(UtilAttackMove::create(0.5f, 0, visibleSize.height, visibleSize.width / 2, visibleSize.height / 3));
			splade3->runAction(UtilAttackMove::create(0.5f, visibleSize.width, visibleSize.height, visibleSize.width / 2, visibleSize.height / 3));

		}
	}
	upadtePlayerHP();
}

void SceneGame::specialAttack(AttackMessage* received_msg, Monster* monster){
	std::stringstream str_stream_temp;
	std::string str_temp;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto _emitter = ParticleFlower::create();
	_emitter->setTag(scene_game_int_tag_number_attack_effect_by_accumulate);
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("stars.png"));
	_emitter->setLifeVar(0);
	_emitter->setLife(2);
	_emitter->setSpeed(100);
	_emitter->setSpeedVar(0);
	_emitter->setEmissionRate(10000);
	this->addChild(_emitter, 10);
	_emitter->setPosition(Vec2(visibleSize.width / 2, 5 * visibleSize.height / 6));
	scene_game_accumulated_timer = 1;

	switch (this->level){
	case 0:{
			switch (received_msg->getSkillEffectNo()){
			case 0: break;
			case 1:
				if (monster1->isAlive()){
					if(monster1->monster_beAttackedBy(received_msg->getEffect(), received_msg->getSkillProperty(), false))
						received_msg->setEffect(received_msg->getEffect() * 2);;
					getChildByTag(scene_game_int_tag_number_sprite_monster1)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));

					str_stream_temp << "-" << received_msg->getEffect();
					str_temp = str_stream_temp.str();

					auto label1 = LabelTTF::create(str_temp, "Arial", 24);
					label1->setColor(ccColor3B::RED);
					label1->setPosition(Vec2(visibleSize.width / 5, visibleSize.height * 7 / 8));
					label1->setOpacity(0);
					label1->setTag(scene_game_int_tag_number_label_monster1_attack_text);
					addChild(label1, Level_3);
					label1->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
				}
				else
					if (monster2->isAlive()){
					if(monster2->monster_beAttackedBy(received_msg->getEffect(), received_msg->getSkillProperty(), false))
						received_msg->setEffect(received_msg->getEffect() * 2);;
					getChildByTag(scene_game_int_tag_number_sprite_monster2)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));

					str_stream_temp << "-" << received_msg->getEffect();
					str_temp = str_stream_temp.str();

					auto label2 = LabelTTF::create(str_temp, "Arial", 24);
					label2->setColor(ccColor3B::RED);
					label2->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 7 / 8));
					label2->setOpacity(0);
					label2->setTag(scene_game_int_tag_number_label_monster2_attack_text);
					addChild(label2, Level_3);
					label2->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
					}
				break;
			case 2:
				playerHP += received_msg->getEffect();
				effect_Heal(visibleSize);
				str_stream_temp << "+" << received_msg->getEffect()*player_hp_total;

				str_temp = str_stream_temp.str();
				if (true){
					auto label_recover1 = LabelTTF::create(str_temp, "Arial", 24);
					label_recover1->setColor(ccColor3B::GREEN);
					label_recover1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
					label_recover1->setOpacity(0);
					label_recover1->setTag(scene_game_int_tag_number_label_hp_player_recover);
					addChild(label_recover1, Level_3);
					label_recover1->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
				}
				if (playerHP > player_hp_total)
					playerHP = player_hp_total;
				break;
			case 3:
				scene_game_demage_fiex = received_msg->getEffect();
				scene_game_damage_counter = received_msg->getEffectiveTime();
				effect_Debuff(visibleSize);
				break;
			case 4:
				if (PlayerMonster1->monster_getRacePerporty() == received_msg->getSkillProperty()){
					PlayerMonster1->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
				}
				if (PlayerMonster2->monster_getRacePerporty() == received_msg->getSkillProperty()){
					PlayerMonster2->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
				}
				if (PlayerMonster3->monster_getRacePerporty() == received_msg->getSkillProperty()){
					PlayerMonster3->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
				}
				if (PlayerMonster4->monster_getRacePerporty() == received_msg->getSkillProperty()){
					PlayerMonster4->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
				}
				effect_Enhance(visibleSize);
				break;
			case 5:
				if (monster1->isAlive()){
					if(monster1->monster_beAttackedBy(received_msg->getEffect()*monster1->monster_get_hp_total(), received_msg->getSkillProperty(), false))
						received_msg->setEffect(received_msg->getEffect() * 2);;
					getChildByTag(scene_game_int_tag_number_sprite_monster1)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));

					str_stream_temp << "-" << received_msg->getEffect()*monster1->monster_get_hp_total();
					str_temp = str_stream_temp.str();

					auto label1 = LabelTTF::create(str_temp, "Arial", 24);
					label1->setColor(ccColor3B::RED);
					label1->setPosition(Vec2(visibleSize.width / 5, visibleSize.height * 7 / 8));
					label1->setOpacity(0);
					label1->setTag(scene_game_int_tag_number_label_monster1_attack_text);
					addChild(label1, Level_3);
					label1->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));

				}
				else
					if (monster2->isAlive()){
					if(monster2->monster_beAttackedBy(received_msg->getEffect()*monster2->monster_get_hp_total(), received_msg->getSkillProperty(), false))
						received_msg->setEffect(received_msg->getEffect() * 2);;
					getChildByTag(scene_game_int_tag_number_sprite_monster2)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
				
					str_stream_temp << "-" << received_msg->getEffect()*monster2->monster_get_hp_total();
					str_temp = str_stream_temp.str();

					auto label2 = LabelTTF::create(str_temp, "Arial", 24);
					label2->setColor(ccColor3B::RED);
					label2->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 7 / 8));
					label2->setOpacity(0);
					label2->setTag(scene_game_int_tag_number_label_monster2_attack_text);
					addChild(label2, Level_3);
					label2->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
					}
				break;
			case 6:
				playerHP += received_msg->getEffect()*player_hp_total;

				str_stream_temp << "+" << received_msg->getEffect()*player_hp_total;
				effect_Heal(visibleSize);
				str_temp = str_stream_temp.str();

				auto label_recover2 = LabelTTF::create(str_temp, "Arial", 24);
				label_recover2->setColor(ccColor3B::GREEN);
				label_recover2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
				label_recover2->setOpacity(0);
				label_recover2->setTag(scene_game_int_tag_number_label_hp_player_recover);
				addChild(label_recover2, Level_3);
				label_recover2->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));

				if (playerHP > player_hp_total)
					playerHP = player_hp_total;
				break;
			}

		break;
	}
	case 1:{

		switch (received_msg->getSkillEffectNo()){
		case 0: break;
		case 1:
			if (monster3->isAlive()){
				if(monster3->monster_beAttackedBy(received_msg->getEffect(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);;
				getChildByTag(scene_game_int_tag_number_sprite_monster3)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
			
				str_stream_temp << "-" << received_msg->getEffect();
				str_temp = str_stream_temp.str();

				auto label3 = LabelTTF::create(str_temp, "Arial", 24);
				label3->setColor(ccColor3B::RED);
				label3->setPosition(Vec2(visibleSize.width / 5, visibleSize.height * 7 / 8));
				label3->setOpacity(0);
				label3->setTag(scene_game_int_tag_number_label_monster3_attack_text);
				addChild(label3, Level_3);
				label3->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}
			else
				if (monster4->isAlive()){
				if(monster4->monster_beAttackedBy(received_msg->getEffect(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);;
				getChildByTag(scene_game_int_tag_number_sprite_monster4)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
			
				str_stream_temp << "-" << received_msg->getEffect();
				str_temp = str_stream_temp.str();

				auto label4 = LabelTTF::create(str_temp, "Arial", 24);
				label4->setColor(ccColor3B::RED);
				label4->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 7 / 8));
				label4->setOpacity(0);
				label4->setTag(scene_game_int_tag_number_label_monster4_attack_text);
				addChild(label4, Level_3);
				label4->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));

				}
			break;
		case 2:
			playerHP += received_msg->getEffect();
			str_stream_temp << "+" << received_msg->getEffect()*player_hp_total;
			effect_Heal(visibleSize);
			str_temp = str_stream_temp.str();
			if (true){
				auto label_recover3 = LabelTTF::create(str_temp, "Arial", 24);
				label_recover3->setColor(ccColor3B::GREEN);
				label_recover3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
				label_recover3->setOpacity(0);
				label_recover3->setTag(scene_game_int_tag_number_label_hp_player_recover);
				addChild(label_recover3, Level_3);
				label_recover3->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}

			if (playerHP > player_hp_total)
				playerHP = player_hp_total;
			break;
		case 3:
			scene_game_demage_fiex = received_msg->getEffect();
			scene_game_damage_counter = received_msg->getEffectiveTime();
			effect_Debuff(visibleSize);
			break;
		case 4:
			if (PlayerMonster1->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster1->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster2->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster2->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster3->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster3->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster4->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster4->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			effect_Enhance(visibleSize);
			break;

		case 5:
			if (monster3->isAlive()){
				if(monster3->monster_beAttackedBy(received_msg->getEffect()*monster3->monster_get_hp_total(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);;
				getChildByTag(scene_game_int_tag_number_sprite_monster3)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));

				str_stream_temp << "-" << received_msg->getEffect()*monster3->monster_get_hp_total();
				str_temp = str_stream_temp.str();

				auto label3 = LabelTTF::create(str_temp, "Arial", 24);
				label3->setColor(ccColor3B::RED);
				label3->setPosition(Vec2(visibleSize.width / 5, visibleSize.height * 7 / 8));
				label3->setOpacity(0);
				label3->setTag(scene_game_int_tag_number_label_monster3_attack_text);
				addChild(label3, Level_3);
				label3->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}
			else
				if (monster4->isAlive()){
				if(monster4->monster_beAttackedBy(received_msg->getEffect()*monster4->monster_get_hp_total(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);;
				getChildByTag(scene_game_int_tag_number_sprite_monster4)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
			
				str_stream_temp << "-" << received_msg->getEffect()*monster4->monster_get_hp_total();
				str_temp = str_stream_temp.str();

				auto label4 = LabelTTF::create(str_temp, "Arial", 24);
				label4->setColor(ccColor3B::RED);
				label4->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 7 / 8));
				label4->setOpacity(0);
				label4->setTag(scene_game_int_tag_number_label_monster4_attack_text);
				addChild(label4, Level_3);
				label4->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
				}
			break;
		case 6:
			playerHP += received_msg->getEffect()*player_hp_total;
			str_stream_temp << "+" << received_msg->getEffect()*player_hp_total;
			effect_Heal(visibleSize);
			str_temp = str_stream_temp.str();

			auto label_recover6 = LabelTTF::create(str_temp, "Arial", 24);
			label_recover6->setColor(ccColor3B::GREEN);
			label_recover6->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
			label_recover6->setOpacity(0);
			label_recover6->setTag(scene_game_int_tag_number_label_hp_player_recover);
			addChild(label_recover6, Level_3);
			label_recover6->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			if (playerHP > player_hp_total)
				playerHP = player_hp_total;
			break;
		}
		break;

		break;
	}
	case 2:{
		switch (received_msg->getSkillEffectNo()){
		case 0: break;
		case 1:
			if (monster5->isAlive()){
				if(monster5->monster_beAttackedBy(received_msg->getEffect(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);;
				getChildByTag(scene_game_int_tag_number_sprite_monster5)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));

				str_stream_temp << "-" << received_msg->getEffect();
				str_temp = str_stream_temp.str();

				auto label5 = LabelTTF::create(str_temp, "Arial", 24);
				label5->setColor(ccColor3B::RED);
				label5->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 7 / 8));
				label5->setOpacity(0);
				label5->setTag(scene_game_int_tag_number_label_monster5_attack_text);
				addChild(label5, Level_3);
				label5->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}

			break;
		case 2:
			playerHP += received_msg->getEffect();
			str_stream_temp << "+" << received_msg->getEffect();

			str_temp = str_stream_temp.str();
			if (true){
				auto label_recover7 = LabelTTF::create(str_temp, "Arial", 24);
				label_recover7->setColor(ccColor3B::GREEN);
				label_recover7->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
				label_recover7->setOpacity(0);
				label_recover7->setTag(scene_game_int_tag_number_label_hp_player_recover);
				addChild(label_recover7, Level_3);
				label_recover7->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}
			effect_Heal(visibleSize);
			if (playerHP > player_hp_total)
				playerHP = player_hp_total;
			break;
		case 3:
			scene_game_demage_fiex = received_msg->getEffect();
			scene_game_damage_counter = received_msg->getEffectiveTime();
			effect_Debuff(visibleSize);
			break;
		case 4:
			if (PlayerMonster1->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster1->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster2->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster2->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster3->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster3->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			if (PlayerMonster4->monster_getRacePerporty() == received_msg->getSkillProperty()){
				PlayerMonster4->monster_setPower(received_msg->getEffect(), received_msg->getEffectiveTime());
			}
			effect_Enhance(visibleSize);
			break;
		case 5:
			if (monster5->isAlive()){
				if(monster5->monster_beAttackedBy(received_msg->getEffect()*monster5->monster_get_hp_total(), received_msg->getSkillProperty(), false))
					received_msg->setEffect(received_msg->getEffect() * 2);;
				getChildByTag(scene_game_int_tag_number_sprite_monster5)->runAction(UtilBeingAttack::create(0.5f, scene_game_scalNow));
			
				str_stream_temp << "-" << received_msg->getEffect()*monster5->monster_get_hp_total();
				str_temp = str_stream_temp.str();

				auto label5 = LabelTTF::create(str_temp, "Arial", 24);
				label5->setColor(ccColor3B::RED);
				label5->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 7 / 8));
				label5->setOpacity(0);
				label5->setTag(scene_game_int_tag_number_label_monster5_attack_text);
				addChild(label5, Level_3);
				label5->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));
			}
			break;
		case 6:
			playerHP += received_msg->getEffect()*player_hp_total;
			str_stream_temp << "+" << received_msg->getEffect()*player_hp_total;

			str_temp = str_stream_temp.str();

			effect_Heal(visibleSize);

			auto label_recover9 = LabelTTF::create(str_temp, "Arial", 24);
			label_recover9->setColor(ccColor3B::GREEN);
			label_recover9->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
			label_recover9->setOpacity(0);
			label_recover9->setTag(scene_game_int_tag_number_label_hp_player_recover);
			addChild(label_recover9, Level_3);
			label_recover9->runAction(Sequence::createWithTwoActions(FadeIn::create(0.4f), FadeOut::create(1.0f)));

			if (playerHP > player_hp_total)
				playerHP = player_hp_total;
			break;
		}
		break;
	}
	}
}

void SceneGame::updateMonsterHP(){
	if (level == 0 && monster1->monster_get_hp_now() >= 0){
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster1)->runAction(ScaleTo::create(0.1f, (scene_game_scale_monster1_hp*(monster1->monster_get_hp_now()) / monster1->monster_get_hp_total()), scene_game_scalZhuanPan));

	}
	if (level == 0 && monster2->monster_get_hp_now() >= 0){
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster2)->runAction(ScaleTo::create(0.1f, (scene_game_scale_monster2_hp*(monster2->monster_get_hp_now()) / monster2->monster_get_hp_total()), scene_game_scalZhuanPan));
	}
	if (level == 1 && monster3->monster_get_hp_now() >= 0){
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster3)->runAction(ScaleTo::create(0.1f, (scene_game_scale_monster3_hp*(monster3->monster_get_hp_now()) / monster3->monster_get_hp_total()), scene_game_scalZhuanPan));
	}
	if (level == 1 && monster4->monster_get_hp_now() >= 0){
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster4)->runAction(ScaleTo::create(0.1f, (scene_game_scale_monster4_hp*(monster4->monster_get_hp_now()) / monster4->monster_get_hp_total()), scene_game_scalZhuanPan));
	}
	if (level == 2 && monster5->monster_get_hp_now() >= 0){
		getChildByTag(scene_game_int_tag_number_sprite_hp_monster5)->runAction(ScaleTo::create(0.1f, (scene_game_scale_monster5_hp*(monster5->monster_get_hp_now()) / monster5->monster_get_hp_total()), scene_game_scalZhuanPan));
	}
	
}

void SceneGame::upadtePlayerHP(){

	getChildByTag(scene_game_int_tag_number_sprite_hp_player)->runAction(ScaleTo::create(0.2f, (scene_game_scale_player_hp*(playerHP) / player_hp_total), scene_game_scalZhuanPan));

	auto  label = (LabelTTF*)getChildByTag(scene_game_int_tag_number_label_hp_player_text);

	std::stringstream temp;
	temp << playerHP<<"/"<<player_hp_total;
	std::string s = temp.str();

	label->setString(s);


}

void SceneGame::effect_Heal(Size visibleSize){
	removeChildByTag(scene_game_int_tag_number_heal_effect);
	auto _emitter = ParticleFlower::create();
	_emitter->setTag(scene_game_int_tag_number_heal_effect);
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("SceneGame/skill/heal.png"));
	_emitter->setLifeVar(0);
	_emitter->setLife(40);
	_emitter->setSpeed(200);
	_emitter->setSpeedVar(50);
	_emitter->setEmissionRate(200);
	this->addChild(_emitter, 10);
	_emitter->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
}

void SceneGame::effect_Enhance(Size visibleSize){
	removeChildByTag(scene_game_int_tag_number_enhance_effect);
	auto _emitter = ParticleFlower::create();
	_emitter->setTag(scene_game_int_tag_number_enhance_effect);
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("SceneGame/skill/enhance.png"));
	_emitter->setLifeVar(0);
	_emitter->setLife(40);
	_emitter->setSpeed(200);
	_emitter->setSpeedVar(50);
	_emitter->setEmissionRate(200);
	this->addChild(_emitter, 10);
	_emitter->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
}

void SceneGame::effect_Debuff(Size visibleSize){
	removeChildByTag(scene_game_int_tag_number_debuff_effect);
	auto _emitter = ParticleFlower::create();
	_emitter->setTag(scene_game_int_tag_number_debuff_effect);
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("SceneGame/skill/debuff.png"));
	_emitter->setLifeVar(0);
	_emitter->setLife(40);
	_emitter->setSpeed(200);
	_emitter->setSpeedVar(50);
	_emitter->setEmissionRate(200);
	this->addChild(_emitter, 10);
	_emitter->setPosition(Vec2(visibleSize.width / 2, 5* visibleSize.height / 6));
}