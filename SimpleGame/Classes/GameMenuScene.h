/******************************************************************************

  SZ 2013-2014,

 ******************************************************************************
  File Name     : GameMenuScene.h
  Version       : Initial Draft
  Author        : SZ ZENG
  Created       : 2013/7/18
  Last Modified :
  Description   : GameMenuScene.cpp header file
  Function List :
  History       :
  1.Date        : 2013/7/18
    Author      : SZ ZENG
    Modification: Created file

******************************************************************************/

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifndef __GAMEMENUSCENE_H__
#define __GAMEMENUSCENE_H__

#include "cocos2d.h"

class GameMenuLayer : public cocos2d::CCLayerColor
{
public:
    GameMenuLayer():_label(NULL) {};
    virtual ~GameMenuLayer();
    bool init();
    CREATE_FUNC(GameMenuLayer);

    void gameMenuDone();

    CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
};

class GameMenuScene : public cocos2d::CCScene
{
public:
    GameMenuScene():_layer(NULL) {};
    ~GameMenuScene();
    bool init();
    CREATE_FUNC(GameMenuScene);
  
    CC_SYNTHESIZE_READONLY(GameMenuLayer*, _layer, Layer);
};

#endif /* __GAMEMENUSCENE_H__ */
