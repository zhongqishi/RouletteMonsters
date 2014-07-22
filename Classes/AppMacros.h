#ifndef APPMACROS_H
#define APPMACROS_H

#include "cocos2d.h"
USING_NS_CC;

#define BACKGROUND_LEVEL 0 
#define GAME_LEVEL 1
#define SPRITE_LEVEL 2

#define DESIGNED_WIDTH 1080
#define DESIGNED_HEIGHT 1920

#define MAIN_SCENE_LAYER_TOP_HEIGHT 1580
#define MAIN_SCENE_LAYER_BOTTOM_HEIGHT 180

#define SaveStringToXML UserDefault::getInstance()->setStringForKey
#define LoadStringFromXML UserDefault::getInstance()->getStringForKey
#define SaveBooleanToXML UserDefault::getInstance()->setBoolForKey
#define LoadBooleanFromXML UserDefault::getInstance()->getBoolForKey
#define FlushXML UserDefault::sharedUserDefault()->flush
#define SaveIntegerToXML UserDefault::getInstance()->setIntegerForKey
#define LoadIntegerFromXML UserDefault::getInstance()->getIntegerForKey



extern bool gIsFromTeamEditToMonsterBox ; 
extern int gMonsterBoxClickedMonster ; 
extern bool gIsFromMonsterBoxToTeamEdit ; 
extern int gCurrentSelectedTeam ; 
extern int gCurrentSelectTeamMember ; 

// extern int gTeamAMonsterCode [ 4 ];
// extern int gTeamBMonsterCode [ 4 ];
// extern int gTeamCMonsterCode [ 4 ];
// extern int gTeamDMonsterCode [ 4 ];
// extern int gTeamEMonsterCode [ 4 ];
extern int gTotalMonsterAmount ; 
extern int gTeamMonsterCode [ 5 ][ 4 ] ;



extern int MAIN_SCENE_OPENED_LAYER ;

enum MAIN_SCENE_LAYERS{
	HOMELAYER,
	QUESTLAYER,
	MONSTERLAYER,
	// FRIENDLAYER,
	// SHOPLAYER,
	// OPTIONLAYER,
	MONSTERBOXLAYER,
	TEAMEDITLAYER
}; 

enum ROULETTE_MONSTER_ORDER{
	RIGHT,
	UP,
	LEFT,
	DOWN
} ;

enum TEAM{
	A,
	B,
	C,
	D,
	E
};

enum TEAM_STATUS{
	SELECTED,
	UNSELECTED
};


#endif
