/*
 * FadeRotateRy.h
 *
 *  Created on: 2014-7-7
 *      Author: LarryShi
 */
#include "cocos2d.h"


#ifndef _Skills_h_
#define _Skills_h_

class SkillsAnimation : public cocos2d::Sequence{

public:
	static void* setParameter(cocos2d::Size *size);

	static Sequence* create(float time, float scal);


private:
	static cocos2d::Size *size;
	const static bool is_size_set=false;

	static Sequence* createNormalAttack(float time);
	static Sequence* createAccumulatedAttack(float time);
	static Sequence* createSkillAttack(float time);
};


#endif /* _Skills_h_ */
