/*
 * Monster.h
 *
 *  Created on: 2014-7-9
 *      Author: LarryShi
 */

#ifndef MONSTER_H_
#define MONSTER_H_
#include <string>
using namespace std;
class Monster {
private:
	string name;
	string description;
	string race;
	int level;
	int experence;
	int hp_total;
	int hp_now;
	int power;
	int speed;
	int dodge_rate;
	int critical_hit_rate;

public:
	Monster(string name);
	void setDescription(string description);
	void setCon(int con);
	string getName();
	int getHP();
};

#endif /* MONSTER_H_ */
