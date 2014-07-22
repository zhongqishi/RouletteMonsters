/*
 * Monster.h
 *
 *  Created on: 2014-7-9
 *      Author: LarryShi
 */

#ifndef MONSTER_H_
#define MONSTER_H_
#include <string>
#include "AttackMessage.h"
using namespace std;
class Monster {
protected:
	string name="";
	string description="";
	string race="";
	string attack_effect_png="";
	int level=0;
	int monster_type;//1 是攻击型，2为辅助性
	int experence=0;
	int hp_point=0;
	int hp_total=0;
	int hp_now=0;
	int power=0;
	int power_point=0;
	int race_property=0;
	int speed=0;
	int dodge_rate=0;
	int critical_hit_rate=0;
	int times_power=0;
	int buff_time=0;
	bool buffed=false;
	bool alive=false;
	int spiral_burst_light=0;
	int energy=0;
	int energy_limit=0;
	int spiral_burst_limit=0;

public:
	Monster();
	void monster_setDescription(string description);
	void monster_setLevel(int level);
	string getName();
	string getAttackPng();
	int monster_get_hp_now();
	bool isAlive();
	void monster_setPower(float times_power, int buff_time);
	int monster_get_hp_total();
	int monster_get_mosnter_type();
	int monster_getRacePerporty();
	
	int monster_getEnergyLimit();
	int monster_getSpiralBurstLimit();
	virtual AttackMessage* monster_AttackOthers();
	virtual AttackMessage* monster_AttackOthers(AttackMessage* message);
	virtual bool monster_beAttackedBy(int number, int race_property, bool player);
	~Monster();
};

class SlimeFire :public Monster{
public:
	SlimeFire(bool enemy, int level);
	bool monster_beAttackedBy(int number, int race_property, bool player);
	AttackMessage* monster_AttackOthers();
};

class SlimeWater :public  Monster{
public:
	SlimeWater(bool enemy, int level);
	bool monster_beAttackedBy(int number, int race_property, bool player);
	AttackMessage* monster_AttackOthers();

};

class BlackDragonBaby :public  Monster{
public:
	BlackDragonBaby(bool enemy, int level);
	bool monster_beAttackedBy(int number, int race_property, bool player);
	AttackMessage* monster_AttackOthers();

};

class LvBu :public  Monster{

public:
	LvBu(bool enemy, int level);
	bool monster_beAttackedBy(int number, int race_property, bool player);
	AttackMessage* monster_AttackOthers();
};

class GodnessMinerva :public Monster{

public:
	GodnessMinerva(bool enemy, int level);
	bool monster_beAttackedBy(int number, int race_property, bool player);

	AttackMessage* monster_AttackOthers(AttackMessage* message);
};

class PrincessShieldWaerqili :public Monster{
public:
	PrincessShieldWaerqili(bool enemy, int level);
	bool monster_beAttackedBy(int number, int race_property, bool player);
	AttackMessage* monster_AttackOthers(AttackMessage* message);
};

class GoddessOfLoveVenus :public Monster{
public:
	GoddessOfLoveVenus(bool enemy, int level);
	bool monster_beAttackedBy(int number, int race_property, bool player);
	AttackMessage* monster_AttackOthers(AttackMessage* message);

};

class Archdemon :public Monster{
public:
	Archdemon(bool enemy, int level);
	bool monster_beAttackedBy(int number, int race_property, bool player);

	AttackMessage* monster_AttackOthers(AttackMessage* message);
};


#endif /* MONSTER_H_ */
