/*
 * Monster.cpp
 *
 *  Created on: 2014-7-9
 *      Author: LarryShi
 */


#include "Monster.h"
#include "AttackMessage.h"
#include <cstdlib>


/*
Monster
*/
int normal_attack = 20;
int property_enhance = 2;
int enemy_enhance = 2;
Monster::Monster(){
	this->alive = true;
}
void Monster::monster_setDescription(string description){

}
void Monster::monster_setLevel(int level){

}

int Monster::monster_get_mosnter_type(){
	return this->monster_type;
}

string Monster::getAttackPngName(){
	return this->attack_effect_png;
}

string Monster::getSprialBurstPngName(){
	return this->spiral_burst_effect_png;
}

string Monster::getBishaPngName(){
	return this->bisha_effect_png;
}


string Monster::getName(){
	return this->name;
}
int Monster::monster_get_hp_now(){
	return this->hp_now;
}
int Monster::monster_get_hp_total(){
	return this->hp_total;
}

bool Monster::isAlive(){
	return this->alive;
}

void Monster::monster_setPower(float times_power, int buff_time){
	this->power = this->power*times_power;
	this->buff_time = buff_time;
	this->buffed = true;
}

int Monster::monster_getEnergyLimit(){
	return this->energy_limit;
}

int Monster::monster_getSpiralBurstLimit(){
	return this->spiral_burst_limit;
}


int Monster::monster_getRacePerporty(){
	return this->race_property;
}


AttackMessage* Monster::monster_AttackOthers(){
	return NULL;
}

AttackMessage* Monster::monster_AttackOthers(AttackMessage* message){
	return message;
}

bool Monster::monster_beAttackedBy(int number, int race_property, bool player){
	return false;
}

Monster::~Monster(){
}

/*
Slime

队伍HP为所有HP实际值相加
HP实际值公式：HP实际值=（HP*2+LV）*LV/10+1000
P实际值公式：P实际值=（P*2+5）*LV/10
伤害公式：伤害=LV*技能威力*P*1.1/（(P+10)*5）
若克制敌人属性，则伤害翻倍
队伍在攻击BOSS和小野怪时候，考虑属性要素。
比如光属性怪打暗属性boss时候，光属性怪兽打来的伤害X2。
但是BOSS和小野怪攻击队伍时，不考虑属性要素。

敌人HP实际值为HP实际值公式乘以2倍，其余相同

1 火，2 水，3 风，4 地， 5 光， 6 暗
*/
SlimeFire::SlimeFire(bool enemy, int level):Monster(){
	name = "SlimeFire";
	attack_effect_png = "fire";
	this->level = 100;
	race_property = 1;
	hp_point = 25;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * enemy_enhance;
	}
	hp_total = hp_now;
	power_point = 25;
	power = (power_point * 2 + 5)*level / 10;


}

bool SlimeFire::monster_beAttackedBy(int number, int race_property, bool player){
	if (race_property == 2&&!player)
		hp_now = hp_now - number * property_enhance;
	else
		hp_now = hp_now - number;
	if (hp_now <= 0){
		hp_now = 0;
		this->alive = false;
	}
	return (race_property == 2 && !player);
}

AttackMessage* SlimeFire::monster_AttackOthers(){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}
	AttackMessage* msg = AttackMessage::createMessage();
	msg->setType(1);
	msg->setEffect(normal_attack*level*1.1 *power / ((power + 10) * 5));

	return msg;
}

/* 史莱姆 水*/

SlimeWater::SlimeWater(bool enemy, int level) :Monster(){
	
	name = "SlimeWater";
	attack_effect_png = "water";
	this->level = 100;
	race_property =2;
	hp_point = 25;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * enemy_enhance;
	}
	hp_total = hp_now;
	power_point = 25;
	power = (power_point * 2 + 5)*level / 10;


}

bool SlimeWater::monster_beAttackedBy(int number, int race_property, bool player){
	if (race_property == 3 && !player)
		hp_now = hp_now - number * property_enhance;
	else
		hp_now = hp_now - number;
	if (hp_now <= 0){
		hp_now = 0;
		this->alive = false;
	}
	return (race_property == 3 && !player);
}

AttackMessage* SlimeWater::monster_AttackOthers(){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}

	AttackMessage* msg = AttackMessage::createMessage();
	msg->setType(1);
	msg->setEffect(normal_attack*level*1.1 *power / ((power + 10) * 5));

	return msg;

}

/*黑龙宝宝*/
BlackDragonBaby::BlackDragonBaby(bool enemy, int level) :Monster(){
	name = "BlackDragonBaby";
	attack_effect_png = "dark";
	this->level = 100;
	race_property = 6;
	hp_point = 30;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * enemy_enhance;
	}
	hp_total = hp_now;
	power_point = 30;
	power = (power_point * 2 + 5)*level / 10;
}

bool BlackDragonBaby::monster_beAttackedBy(int number, int race_property, bool player){
	if (race_property == 5 && !player)
		hp_now = hp_now - number * property_enhance;
	else
		hp_now = hp_now - number;
	if (hp_now <= 0){
		hp_now = 0;
		this->alive = false;
	}
	return (race_property == 5 && !player);
}

AttackMessage* BlackDragonBaby::monster_AttackOthers(){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}
	AttackMessage* msg = AttackMessage::createMessage();
	msg->setType(1);
	msg->setEffect(normal_attack*level*1.1 *power / ((power + 10) * 5));

	return msg;
	
}

/*吕布*/

LvBu::LvBu(bool enemy, int level) :Monster(){
	name = "LvBu";
	spiral_burst_effect_png = "sb_LvBu";
	bisha_effect_png = "bisha_LvBu";
	energy = 0;
	spiral_burst_light = 0;
	energy_limit = 3;
	attack_effect_png = "lvbu";
	monster_type = 1;
	spiral_burst_limit = 5;
	this->level = 100;
	race_property = 6;
	hp_point = 60;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * enemy_enhance;
	}
	hp_total = hp_now;
	power_point = 70;
	power = (power_point * 2 + 5)*level / 10;
}

bool LvBu::monster_beAttackedBy(int number, int race_property, bool player){
	if (race_property == 5 && !player)
		hp_now = hp_now - number * property_enhance;
	else
		hp_now = hp_now - number;
	if (hp_now <= 0){
		hp_now = 0;
		this->alive = false;
	}
	return (race_property == 5 && !player);
}

AttackMessage* LvBu::monster_AttackOthers(){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}
	AttackMessage* msg = AttackMessage::createMessage();



	if (spiral_burst_light == spiral_burst_limit){
		spiral_burst_light = 0;
		this->monster_setPower(2, 1);
		msg->setEffect(0);
		msg->setSkillProperty(0);
		msg->setType(5);
		msg->setSkillEffectNo(4);
		return msg;
	}

	if (energy >= energy_limit){
		energy = 0;
		spiral_burst_light++;
		msg->setEffect(140 * level*1.1 *power / ((power + 10) * 5));
		msg->setSkillProperty(6);
		msg->setType(4);
		msg->setSkillEffectNo(1);

		return msg;
	}

	spiral_burst_light++;
	energy++;
	
	int temp = rand() % 100;
	
	if (temp <= 55){
		msg->setEffect(70 * level*1.1 *power / ((power + 10) * 5));
		msg->setSkillProperty(6);
		msg->setType(2);
		msg->setSkillEffectNo(1);
		return msg;
	}
	else if (temp <= 70){
		msg->setEffect(0);
		msg->setSkillProperty(0);
		msg->setType(3);
		msg->setSkillEffectNo(0);
		return msg;
	}
	else{
		msg->setEffect(normal_attack * level*1.1 *power / ((power + 10) * 5));
		msg->setSkillProperty(0);
		msg->setType(1);
		msg->setSkillEffectNo(1);
		return msg; 
	}

}
/*战女神米涅瓦*/
GodnessMinerva::GodnessMinerva(bool enemy, int level) :Monster(){
	Monster();
	name = "GodnessMinerva";
	spiral_burst_effect_png = "sb_GodnessMinerva";
	bisha_effect_png = "bisha_GodnessMinerva";
	this->level = 100;
	monster_type = 1;
	energy = 0;
	spiral_burst_light = 0;
	energy_limit = 2;
	spiral_burst_limit = 4;
	race_property = 5;
	hp_point = 50;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * enemy_enhance;
	}
	hp_total = hp_now;
	power_point = 60;
	power = (power_point * 2 + 5)*level / 10;
}

bool GodnessMinerva::monster_beAttackedBy(int number, int race_property, bool player){
	if (race_property == 6 && !player)
		hp_now = hp_now - number * property_enhance;
	else
		hp_now = hp_now - number;
	if (hp_now <= 0){
		hp_now = 0;
		this->alive = false;
	}
	return (race_property == 6 && !player);
}

AttackMessage* GodnessMinerva::monster_AttackOthers(AttackMessage* message){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}
	AttackMessage* msg = AttackMessage::createMessage();
	switch (message->getType()){
	case 1://普通攻击
		msg->setEffect(normal_attack * level*1.1 *power / ((power + 10) * 5));
		msg->setSkillProperty(0);
		msg->setSkillEffectNo(1);
		msg->setType(1);
		break;
	case 2://主技能
		msg->setEffect((40 * level*1.1 *power / ((power + 10) * 5)));
		msg->setSkillProperty(5);
		msg->setSkillEffectNo(1);
		msg->setType(2);
		break;
	case 3://副技能
		msg->setEffect(0.1f);
		msg->setSkillProperty(5);
		msg->setSkillEffectNo(6);
		msg->setType(3);
		break;
	case 4://必杀
		msg->setEffect((60 * level*1.1 *power / ((power + 10) * 5)));
		msg->setSkillProperty(5);
		msg->setSkillEffectNo(1);
		msg->setType(4);
		break;
		
	case 5://Sprial Burst
		msg->setEffect((100 * level*1.1 *power / ((power + 10) * 5)));
		msg->setSkillProperty(5);
		msg->setSkillEffectNo(1);
		msg->setType(5);
		break;
	
	}

	return msg;
}

/*纯白之盾瓦尔奇莉公主*/

PrincessShieldWaerqili::PrincessShieldWaerqili(bool enemy, int level):Monster(){
	name = "PrincessShieldWaerqili";
	spiral_burst_effect_png = "sb_PrincessShieldWaerqili";
	bisha_effect_png = "bisha_PrincessShieldWaerqili";
	this->level = 100;
	monster_type = 2;
	energy = 0;
	spiral_burst_light = 0;
	energy_limit = 3;
	spiral_burst_limit = 6;
	race_property = 5 ;
	hp_point = 70;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * enemy_enhance;
	}
	hp_total = hp_now;
	power_point = 40;
	power = (power_point * 2 + 5)*level / 10;
}

bool PrincessShieldWaerqili::monster_beAttackedBy(int number, int race_property, bool player){
	if (race_property == 6 && !player)
		hp_now = hp_now - number * property_enhance;
	else
		hp_now = hp_now - number;
	if (hp_now <= 0){
		hp_now = 0;
		this->alive = false;
	}
	return (race_property == 6 && !player);
}

AttackMessage* PrincessShieldWaerqili::monster_AttackOthers(AttackMessage* message){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}

	AttackMessage* msg = AttackMessage::createMessage();
	switch (message->getType()){
	case 1://普通攻击
		msg->setEffect((normal_attack * level*1.1 *power / ((power + 10) * 5)));
		msg->setSkillProperty(0);
		msg->setSkillEffectNo(1);
		msg->setType(1);
		break;
	case 2://主技能
		msg->setEffect(0.2f);
		msg->setSkillProperty(5);
		msg->setSkillEffectNo(6);
		msg->setType(2);
		break;
	case 3://副技能
		msg->setEffect(20 * level*1.1 *power / ((power + 10) * 5));
		msg->setSkillProperty(5);
		msg->setSkillEffectNo(1);
		msg->setType(3);
		break;
	case 4://必杀
		msg->setEffect(0.4f);
		msg->setSkillProperty(5);
		msg->setSkillEffectNo(6);
		msg->setType(4);
		break;

	case 5://Sprial Burst
		msg->setEffect(0);
		msg->setSkillProperty(5);
		msg->setSkillEffectNo(3);
		msg->setEffectiveTime(1);
		msg->setType(5);
		break;

	}
	return msg;
}

/*慈爱神维纳斯*/
GoddessOfLoveVenus::GoddessOfLoveVenus(bool enemy, int level) :Monster(){
	name = "GoddessOfLoveVenus";
	spiral_burst_effect_png = "sb_GoddessOfLoveVenus";
	bisha_effect_png = "bisha_GoddessOfLoveVenus";
	this->level = 100;
	monster_type = 2;
	energy = 0;
	spiral_burst_light = 0;
	energy_limit = 2;
	spiral_burst_limit = 5;
	race_property = 5;
	hp_point = 70;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * enemy_enhance;
	}
	hp_total = hp_now;
	power_point = 40;
	power = (power_point * 2 + 5)*level / 10;

}

bool GoddessOfLoveVenus::monster_beAttackedBy(int number, int race_property, bool player){
	if (race_property == 6 && !player)
		hp_now = hp_now - number * property_enhance;
	else
		hp_now = hp_now - number;
	if (hp_now <= 0){
		hp_now = 0;
		this->alive = false;
	}
	return  (race_property == 6 && !player);
}

AttackMessage* GoddessOfLoveVenus::monster_AttackOthers(AttackMessage* message){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}

	AttackMessage* msg = AttackMessage::createMessage();
	switch (message->getType()){
	case 1://普通攻击
		msg->setEffect((normal_attack * level*1.1 *power / ((power + 10) * 5)));
		msg->setSkillProperty(0);
		msg->setSkillEffectNo(1);
		msg->setType(1);
		break;
	case 2://主技能
		msg->setEffect(0.2f);
		msg->setSkillProperty(5);
		msg->setSkillEffectNo(6);
		msg->setType(2);
		break;
	case 3://副技能
		msg->setEffect(20 * level*1.1 *power / ((power + 10) * 5));
		msg->setSkillProperty(5);
		msg->setSkillEffectNo(1);
		msg->setType(3);
		break;
	case 4://必杀
		msg->setEffect(0.9f);
		msg->setSkillProperty(5);
		msg->setEffectiveTime(1);
		msg->setSkillEffectNo(3);
		msg->setType(4);
		break;

	case 5://Sprial Burst
		msg->setEffect(1.5f);
		msg->setSkillProperty(5);
		msg->setSkillEffectNo(4);
		msg->setEffectiveTime(1);
		msg->setType(5);
		break;

	}
	return msg;

}
/*大魔王撒旦*/

Archdemon::Archdemon(bool enemy, int level) :Monster(){
	name = "Archdemon";
	spiral_burst_effect_png = "sb_Archdemon";
	bisha_effect_png = "bisha_Archdemon";
	this->level = 100;
	monster_type = 1;
	energy = 0;
	spiral_burst_light = 0;
	energy_limit = 3;
	spiral_burst_limit = 6;
	race_property = 6;
	hp_point = 60;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * enemy_enhance;
	}
	hp_total = hp_now;
	power_point = 60;
	power = (power_point * 2 + 5)*level / 10;

}

bool Archdemon::monster_beAttackedBy(int number, int race_property, bool player){
	if (race_property == 5&& !player)
		hp_now = hp_now - number * property_enhance;
	else
		hp_now = hp_now - number;
	if (hp_now <= 0){
		hp_now = 0;
		this->alive = false;
	}
	return (race_property == 5 && !player);
}

AttackMessage* Archdemon::monster_AttackOthers(AttackMessage* message){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}

	AttackMessage* msg = AttackMessage::createMessage();
	switch (message->getType()){
	case 1://普通攻击
		msg->setEffect((normal_attack * level*1.1 *power / ((power + 10) * 5)));
		msg->setSkillProperty(0);
		msg->setSkillEffectNo(1);
		msg->setType(1);
		break;
	case 2://主技能
		msg->setEffect((60 * level*1.1 *power / ((power + 10) * 5)));
		msg->setSkillProperty(6);
		msg->setSkillEffectNo(1);
		msg->setType(2);
		break;
	case 3://副技能
		msg->setEffect(0);
		msg->setSkillProperty(6);
		msg->setSkillEffectNo(0);
		msg->setType(3);
		break;
	case 4://必杀
		msg->setEffect((100 * level*1.1 *power / ((power + 10) * 5)));
		msg->setSkillProperty(6);
		msg->setSkillEffectNo(1);
		msg->setType(4);
		break;

	case 5://Sprial Burst
		msg->setEffect((140 * level*1.1 *power / ((power + 10) * 5)));
		msg->setSkillProperty(6);
		msg->setSkillEffectNo(1);
		msg->setType(5);
		break;

	}
	return msg;

}
