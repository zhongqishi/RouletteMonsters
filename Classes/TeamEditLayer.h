#ifndef TEAM_EDIT_SCENE_H
#define TEAM_EDIT_SCENE_H

#include "cocos2d.h"

USING_NS_CC;

class TeamEditLayer : public cocos2d::Layer
{
public:
	
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    Vec2 touchStartLocation , touchMovedLocation ; 

    Vec2 rouletteRoundCenter ;

    CREATE_FUNC(TeamEditLayer);

    virtual bool backButtonOnTouchBegan(Touch* touch, Event  *event) ;  
	virtual void backButtonOnTouchMoved(Touch* touch, Event  *event) ;  
	virtual void backButtonOnTouchEnded(Touch* touch, Event  *event) ; 

    virtual bool rouletteRoundOnTouchBegan(Touch* touch, Event  *event) ;  
	virtual void rouletteRoundOnTouchMoved(Touch* touch, Event  *event) ;  
	virtual void rouletteRoundOnTouchEnded(Touch* touch, Event  *event) ;  

	virtual bool teamInfoOnTouchBegan(Touch* touch, Event  *event) ;  
	virtual void teamInfoOnTouchMoved(Touch* touch, Event  *event) ;  
	virtual void teamInfoOnTouchEnded(Touch* touch, Event  *event) ;

	virtual bool teamMemberOnTouchBegan(Touch* touch, Event  *event) ;  
	virtual void teamMemberOnTouchMoved(Touch* touch, Event  *event) ;  
	virtual void teamMemberOnTouchEnded(Touch* touch, Event  *event) ;

	Rect backButtonRect ;

	int currentActiveTeam  ; 

	float team_info_label_height,team_info_label_width, team_info_label_x, team_info_label_y ; 

	Rect teamARect, teamBRect, teamCRect, teamDRect, teamERect ;
	Rect teamMemberUpRect, teamMemberDownRect, teamMemberLeftRect, teamMemberRightRect ;


	Texture2D *team_edit_layer_team_a_active_texture,
		*team_edit_layer_team_a_inactive_texture,
		*team_edit_layer_team_b_active_texture,
		*team_edit_layer_team_b_inactive_texture,
		*team_edit_layer_team_c_active_texture,
		*team_edit_layer_team_c_inactive_texture,
		*team_edit_layer_team_d_active_texture,
		*team_edit_layer_team_d_inactive_texture,
		*team_edit_layer_team_e_active_texture,
		*team_edit_layer_team_e_inactive_texture ;

	Texture2D *teamLabelTexture [ 5 ] [ 2 ] ; 

	Texture2D *monsterTexture[35][4];

	// Texture2D *monsterTextureUp [35] ;
	// Texture2D *monsterTextureDown [35] ;
	// Texture2D *monsterTextureLeft [35] ;
	// Texture2D *monsterTextureRight [35] ;

};



#endif
