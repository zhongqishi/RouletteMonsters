#include "AttackMessage.h"

bool hasCreated=false;
AttackMessage* AttackMessage::message = nullptr;
AttackMessage* AttackMessage::createMessage(){
	if (hasCreated)
		return message;
	else
	{
		message = new AttackMessage();
		hasCreated = true;
		return message;
	}
}
void AttackMessage::setType(int type){
	this->type = type;
}

void AttackMessage::setSkillEffectNo(int num){
	this->skill_effect_no = num;
}

void AttackMessage::setSkillProperty(int num){
	skill_property = num;
}

void AttackMessage::setNumAttackMonster(int num){
	this->num_attack_monster = num;
}
void AttackMessage::setNumAssistMonster(int num){
	this->num_assist_monster = num;
}
void AttackMessage::setEffect(float effect){
	this->effect = effect;
}
int AttackMessage::getType(){
	return type;
}
int AttackMessage::getSkillEffectNo(){
	return skill_effect_no;
}
int AttackMessage::getSkillProperty(){
	return skill_property;
}
int AttackMessage::getNumAttackMonster(){
	return num_attack_monster;
}
int AttackMessage::getNumAssistMonster(){
	return num_assist_monster;
}
float AttackMessage::getEffect(){
	return effect;
}

AttackMessage::AttackMessage(){

}

void AttackMessage::setEffectiveTime(int time){
	effectiveTime = time;
}

int AttackMessage::getEffectiveTime(){
	return effectiveTime;
}

AttackMessage::AttackMessage(AttackMessage const&){
	// Don't Implement
}

void AttackMessage::operator=(AttackMessage const&){
	// Don't im
}