#ifndef __Attack_Message_H__
#define __Attack_Message_H__

class AttackMessage
{
public:
	static AttackMessage*  createMessage();
	

	void setType(int type);
	void setSkillEffectNo(int num);
	void setSkillProperty(int num);
	void setNumAttackMonster(int num);
	void setNumAssistMonster(int num);
	void setEffect(float effect);
	void setEffectiveTime(int time);
	int getType();
	int getNumAttackMonster();
	int getNumAssistMonster();
	int getSkillEffectNo();
	int getSkillProperty();
	float getEffect();
	int getEffectiveTime();
private:
	AttackMessage();
	static  AttackMessage*  message;
	int type;//1:attack,2:main,3:sub,4:必杀，5:Spiral Burst
	int num_attack_monster;
	int num_assist_monster;
	int skill_property;//0:Nothing, 1.攻击，2 回复，3减伤，4，增加攻击，5，给敌人按比例伤害，6给自己按比例恢复
	int skill_effect_no;//
	float effect;
	int effectiveTime;
	
	AttackMessage(AttackMessage const&);              // Don't Implement
	void operator=(AttackMessage const&); // Don't implement
};

#endif // __Attack_Message_H__
