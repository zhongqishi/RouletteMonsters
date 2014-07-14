/*
 * Monster.cpp
 *
 *  Created on: 2014-7-9
 *      Author: LarryShi
 */

#include "Monster.h"

Monster::Monster(string name){
	this->Name=name;
}

void Monster::setDescription(string description){
	this->Description=description;

}
void Monster::setCon(int con){
	this->Con=con;
	this->HP=con*20;
}
string Monster::getName(){
	return this->Name;
}
int Monster::getHP(){
	return this->HP;
}

