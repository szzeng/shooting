/******************************************************************************

  SZ 2013-2014,

 ******************************************************************************
  File Name     : GameMenuScene.cpp
  Version       : Initial Draft
  Author        : SZ ZENG
  Created       : 2013/7/18
  Last Modified :
  Description   : GAME Menu
  Function List :
              GameMenuLayer.gameMenuDone
              GameMenuLayer.init
              GameMenuLayer.~GameMenuLayer
              GameMenuScene.init
              GameMenuScene.~GameMenuScene
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

#include "GameMenuScene.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

bool GameMenuScene::init()
{
	if( CCScene::init() )
	{
		this->_layer = GameMenuLayer::create();
		this->_layer->retain();
		this->addChild(_layer);
		
		return true;
	}
	else
	{
		return false;
	}
}

GameMenuScene::~GameMenuScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}


bool GameMenuLayer::init()
{
	if ( CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		this->_label = CCLabelTTF::create("","Artial", 32);
		_label->retain();
		_label->setColor( ccc3(0, 0, 0) );
		_label->setPosition( ccp(winSize.width/2, winSize.height/2) );
		this->addChild(_label);
		
		this->runAction( CCSequence::create(
                                CCDelayTime::create(3),
                                CCCallFunc::create(this, 
                                callfunc_selector(GameMenuLayer::gameMenuDone)),
                                NULL));
		
		return true;
	}
	else
	{
		return false;
	}
}

void GameMenuLayer::gameMenuDone()
{
	CCDirector::sharedDirector()->replaceScene( HelloWorld::scene() );
}

GameMenuLayer::~GameMenuLayer()
{
	if (_label)
	{
		_label->release();
		_label = NULL;
	}
}
