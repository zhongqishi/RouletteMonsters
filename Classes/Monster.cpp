/*
 * Monster.cpp
 *
 *  Created on: 2014-7-9
 *      Author: LarryShi
 */


#include "Monster.h"
#include <cstdlib>
/*
Monster
*/
int normal_attack = 20;
Monster::Monster(){
	this->alive = true;
}
void Monster::monster_setDescription(string description){

}
void Monster::monster_setLevel(int level){

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


float Monster::monster_AttackOthers(){
	return 1.1f;
}

float Monster::monster_AttackOthers(int number){
	return 1.1f;
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
	
	this->level = 100;
	race_property = 1;
	hp_point = 25;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * 2;
	}
	hp_total = hp_now;
	power_point = 25;
	power = (power_point * 2 + 5)*level / 10;


}

int SlimeFire::beAttackedBy(int number, int race_property, bool player){
	if (race_property == 2&&!player)
		hp_now = hp_now - number * 2;
	else
		hp_now = hp_now - number;
	return hp_now;
}

float SlimeFire::monster_AttackOthers(){
	if (buffed)
		buff_time--;
	if (buff_time <= 0){
		buffed = false;
		power = power / times_power;
	}
	return normal_attack*level*1.1 *power / ((power + 10) / 5);
}

/* 史莱姆 水*/

SlimeWater::SlimeWater(bool enemy, int level) :Monster(){
	
	name = "SlimeWater";

	this->level = 100;
	race_property =2;
	hp_point = 25;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * 2;
	}
	hp_total = hp_now;
	power_point = 25;
	power = (power_point * 2 + 5)*level / 10;


}

int SlimeWater::beAttackedBy(int number, int race_property, bool player){
	if (race_property == 3 && !player)
		hp_now = hp_now - number * 2;
	else
		hp_now = hp_now - number;
	return hp_now;
}

float SlimeWater::monster_AttackOthers(){
	if (buffed)
		buff_time--;
	if (buff_time <= 0){
		buffed = false;
		power = power / times_power;
	}
	return normal_attack*level*1.1 *power / ((power + 10) / 5);
}

/*黑龙宝宝*/
BlackDragonBaby::BlackDragonBaby(bool enemy, int level) :Monster(){
	name = "BlackDragonBaby";

	this->level = 100;
	race_property = 6;
	hp_point = 30;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * 2;
	}
	hp_total = hp_now;
	power_point = 30;
	power = (power_point * 2 + 5)*level / 10;
}

int BlackDragonBaby::beAttackedBy(int number, int race_property, bool player){
	if (race_property == 5 && !player)
		hp_now = hp_now - number * 2;
	else
		hp_now = hp_now - number;
	return hp_now;
}

float BlackDragonBaby::monster_AttackOthers(){
	if (buffed)
		buff_time--;
	if (buff_time <= 0){
		buffed = false;
		power = power / times_power;
	}
	return normal_attack*level*1.1 *power / ((power + 10) / 5);
}

/*吕布*/

LvBu::LvBu(bool enemy, int level) :Monster(){
	name = "LvBu";
	energy = 0;
	spiral_burst_light = 0;
	energy_limit = 3;
	spiral_burst_limit = 5;
	this->level = 100;
	race_property = 6;
	hp_point = 60;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * 2;
	}
	hp_total = hp_now;
	power_point = 70;
	power = (power_point * 2 + 5)*level / 10;
}

int LvBu::beAttackedBy(int number, int race_property, bool player){
	if (race_property == 5 && !player)
		hp_now = hp_now - number * 2;
	else
		hp_now = hp_now - number;
	return hp_now;
}

float LvBu::monster_AttackOthers(){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}

	if (spiral_burst_light == spiral_burst_limit){
		spiral_burst_light = 0;
		this->monster_setPower(2, 1);
		return 0;
	}

	if (energy >= energy_limit){
		energy = 0;
		spiral_burst_light++;
		return 140 * level*1.1 *power / ((power + 10) / 5);
	}

	spiral_burst_light++;
	energy++;
	
	int temp = rand() % 100;
	
	if (temp <= 55){
		return 70 * level*1.1 *power / ((power + 10) / 5);
	}
	else if (temp <= 70){
		return 0;
	}
	else{
		return normal_attack * level*1.1 *power / ((power + 10) / 5);
	}

}
/*战女神米涅瓦*/
GodnessMinerva::GodnessMinerva(bool enemy, int level) :Monster(){
	Monster();
	name = "GodnessMinerva";
	this->level = 100;

	energy = 0;
	spiral_burst_light = 0;
	energy_limit = 2;
	spiral_burst_limit = 4;
	race_property = 5;
	hp_point = 50;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * 2;
	}
	hp_total = hp_now;
	power_point = 60;
	power = (power_point * 2 + 5)*level / 10;
}

int GodnessMinerva::beAttackedBy(int number, int race_property,bool player){
	if (race_property == 6 && !player)
		hp_now = hp_now - number * 2;
	else
		hp_now = hp_now - number;
	return hp_now;
}

float GodnessMinerva::monster_AttackOthers(int number){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}
	switch (number){
	case 1:return (int)(normal_attack * level*1.1 *power / ((power + 10) / 5)); break;//普通攻击
	case 2:return (int)(40 * level*1.1 *power / ((power + 10) / 5))+0.5f; break;//主技能
	case 3:return -0.1f; break;//副技能
	case 4:return (int)(60 * level*1.1 *power / ((power + 10) / 5)) + 0.5f; break;//必杀
	case 5:return (int)(100 * level*1.1 *power / ((power + 10) / 5)) + 0.5f;//Sprial Burst
	}
}

/*纯白之盾瓦尔奇莉公主*/

PrincessShieldWaerqili::PrincessShieldWaerqili(bool enemy, int level) :Monster(){
	name = "PrincessShieldWaerqili";
	this->level = 100;

	energy = 0;
	spiral_burst_light = 0;
	energy_limit = 3;
	spiral_burst_limit = 6;
	race_property = 5 ;
	hp_point = 70;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * 2;
	}
	hp_total = hp_now;
	power_point = 40;
	power = (power_point * 2 + 5)*level / 10;
}
int PrincessShieldWaerqili::beAttackedBy(int number, int race_property, bool player){
	if (race_property == 6 && !player)
		hp_now = hp_now - number * 2;
	else
		hp_now = hp_now - number;
	return hp_now;
}

float PrincessShieldWaerqili::monster_AttackOthers(int number){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}
	switch (number){
		case 1:return (int)(normal_attack * level*1.1 *power / ((power + 10) / 5)); break;//普通攻击
		case 2:return -0.2f; break;//主技能;
		case 3:return (int)(20 * level*1.1 *power / ((power + 10) / 5))+0.5f; break;//副技能
		case 4:return -0.4f; break;//必杀
		case 5:return -0.0015f; break;//Sprial Burst  
	}
}

/*慈爱神维纳斯*/
GoddessOfLoveVenus::GoddessOfLoveVenus(bool enemy, int level) :Monster(){
	name = "GoddessOfLoveVenus";
	this->level = 100;

	energy = 0;
	spiral_burst_light = 0;
	energy_limit = 2;
	spiral_burst_limit = 5;
	race_property = 5;
	hp_point = 70;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * 2;
	}
	hp_total = hp_now;
	power_point = 40;
	power = (power_point * 2 + 5)*level / 10;

}

int GoddessOfLoveVenus::beAttackedBy(int number, int race_property, bool player){
	if (race_property == 6 && !player)
		hp_now = hp_now - number * 2;
	else
		hp_now = hp_now - number;
	return hp_now;
}

float GoddessOfLoveVenus::monster_AttackOthers(int number){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}
	switch (number){
		case 1:return (int)(normal_attack * level*1.1 *power / ((power + 10) / 5)); break;//普通攻击
		case 2:return -0.2f; break;//主技能;
		case 3:return (int)(20 * level*1.1 *power / ((power + 10) / 5))+0.5f; break; break;//副技能
		case 4:return -0.00101f; break;//必杀
		case 5:return -0.00255f; break;//Sprial Burst  
	}
}
/*大魔王撒旦*/

Archdemon::Archdemon(bool enemy, int level) :Monster(){
	name = "Archdemon";
	this->level = 100;

	energy = 0;
	spiral_burst_light = 0;
	energy_limit = 3;
	spiral_burst_limit = 6;
	race_property = 6;
	hp_point = 60;
	hp_now = (hp_point * 2 + level)*level / 10 + 1000;
	if (enemy){
		hp_now = hp_now * 2;
	}
	hp_total = hp_now;
	power_point = 60;
	power = (power_point * 2 + 5)*level / 10;

}

int Archdemon::beAttackedBy(int number, int race_property, bool player){
	if (race_property == 5&& !player)
		hp_now = hp_now - number * 2;
	else
		hp_now = hp_now - number;
	return hp_now;
}

float Archdemon::monster_AttackOthers(int number){
	if (buffed)
		buff_time--;
	if (buff_time < 0){
		buffed = false;
		power = power / times_power;
	}
	switch (number){
		case 1:return (int)(normal_attack * level*1.1 *power / ((power + 10) / 5)); break;//普通攻击
		case 2:return (int)(60 * level*1.1 *power / ((power + 10) / 5)) + 0.6f; break;//主技能;
		case 3:return 0; break; //副技能
		case 4:return (int)(100 * level*1.1 *power / ((power + 10) / 5)) + 0.6f; break;//必杀
		case 5:return (int)(140 * level*1.1 *power / ((power + 10) / 5)) + 0.6f; break;//Sprial Burst  
	}
}
