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
	string Name;
	string Description;
	int Level;
	int Exp;
	int HP;
	int Str;//力量，决定攻击力
	int Dex;//敏捷，决定闪避和暴击
	int Con;//体力，决定HP和防御
	int Recovery;
	int Attack;
	int Defense;
	int Avoid;
	int Critical;
public:
	Monster(string name);
	void setDescription(string description);
	void setCon(int con);
	string getName();
	int getHP();
};

#endif /* MONSTER_H_ */
