#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"
#include "string"
#include "Monster.h"
#include "AttackMessage.h"
USING_NS_CC;

class SceneGame : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene(Monster* monster1, Monster* monster2, Monster* monster3, Monster* monster4);
	static cocos2d::Layer* create(Monster* monster1, Monster* monster2, Monster* monster3, Monster* monster4);
	virtual bool init(Monster* player_monster1, Monster* player_monster2, Monster* player_monster3, Monster* player_monster4);

	bool onTouchBegan(Touch* touch, Event  *event);
	void onTouchEnded(Touch* touch, Event  *event);
	
	void menuCallback(cocos2d::Ref* pSender);

	bool toucheTheCenterOfZhuanpanThePosition(float x,float y);
	void setPlayerWin();
	void setPlayerLose();
	void setEmitterPosition();
	virtual void update(float dt);
	
	// implement the "static create()" method manually

private:
	AttackMessage* msg;

	Monster* PlayerMonster1;
	Monster* PlayerMonster2;
	Monster* PlayerMonster3;
	Monster* PlayerMonster4;

	Monster* monster1;
	Monster* monster2;
	Monster* monster3;
	Monster* monster4;
	Monster* monster5;
	
	
	int accumulated_angle=0;
	int level = 0;
	int spiral_light_num = 0;
	int playerHP = 100;
	int player_hp_total = 100;

	int Player_monster1_energy = 0;
	int Player_monster2_energy = 0;
	int Player_monster3_energy = 0;
	int Player_monster4_energy = 0;

	std::string skillbox1 = "attack";
	std::string skillbox2 = "charge";
	std::string skillbox3 = "attack";
	std::string skillbox4 = "sub";
	std::string skillbox5 = "main";
	std::string skillbox6 = "attack";
	std::string skillbox7 = "sub";
	std::string skillbox8 = "main";
	
	SpriteBatchNode * CrystalPin;
	ParticleSystemQuad*    partical_system_zhuanpan_decorate;
	MotionStreak * streak;
	Vec2 gs_MotionStreak_center;
	


	bool start();


	float gs_MotionStreak_radius;
	float gs_MotionStreak_angle;

	void initZhuanpan(std::string scene_game_monster_pin1, std::string scene_game_monster_pin2, std::string scene_game_monster_pin3, std::string scene_game_monster_pin4);
	void initPlayerHP();
	void initMonsters();

	void monster1_energy_accumulate();
	void monster2_energy_accumulate();
	void monster3_energy_accumulate();
	void monster4_energy_accumulate();

	void monster1_pin_Callback(cocos2d::Ref* pSender);
	void monster2_pin_Callback(cocos2d::Ref* pSender);
	void monster3_pin_Callback(cocos2d::Ref* pSender);
	void monster4_pin_Callback(cocos2d::Ref* pSender);
	void zhuanpan_center_Callback(cocos2d::Ref* pSender);


	void spiral_burst_pin_show();
	void spiral_burst_light_turn_on(bool turn_on);

	void show_monster1_hp(bool show);
	void show_monster2_hp(bool show);
	void show_monster3_hp(bool show);
	void show_monster4_hp(bool show);
	void show_monster5_hp(bool show);

	void enterLevelOne();
	void enterLevelTwo();
	void enterLevelThree();

	void nomralZhuanPanSkillAction(AttackMessage* received_msg);
	void specialAttack(AttackMessage* received_msg, Monster* monster);
	void AttackByEnemy();
	void zhuanpanActionFinished();

	void effect_Heal(Size visibleSize);
	void effect_Enhance(Size visibleSize);
	void effect_Debuff(Size visibleSize);

	void updateMonsterHP();
	void upadtePlayerHP();
	
};

#endif // __Game_SCENE_H__
