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
        this->_label = CCLabelTTF::create("","Artial", 16);
        _label->retain();
        _label->setColor( ccc3(0, 0, 0) );
//        CCLog("GameMenuLayer:testDealloc %f, %f", _label->getDimensions().width, _label->getDimensions().height);
        _label->setPosition( ccp(_label->getFontSize()*2, _label->getFontSize()*2) );
        this->addChild(_label);

        
        CCMenuItemFont* item1 = CCMenuItemFont::create( "Shooting", this, menu_selector(GameMenuLayer::onStart) );
        CCMenuItemFont* item2 = CCMenuItemFont::create( "Option", this, menu_selector(GameMenuLayer::onOption) );
        CCMenuItemFont* item3 = CCMenuItemFont::create( "About", this, menu_selector(GameMenuLayer::onAbout) );

        CCMenu* menu = CCMenu::create( item1, item2, item3, NULL );
        menu->alignItemsVertically();
        menu->setColor( ccc3(0, 0, 0) );

        addChild( menu );
                
        return true;
    }
    else
    {
        return false;
    }
}

void GameMenuLayer::onStart(CCObject* pSender)
{
    
    this->runAction( CCSequence::create(
                            CCDelayTime::create(3),
                            CCCallFunc::create(this, 
                            callfunc_selector(GameMenuLayer::gameMenuDone)),
                            NULL));
//    CCScene* scene = new SceneTestScene();
//    CCLayer* pLayer = new SceneTestLayer2();
//    scene->addChild( pLayer, 0 );
//    CCDirector::sharedDirector()->pushScene( scene );
//    scene->release();
//    pLayer->release();
}

void GameMenuLayer::onOption(CCObject* pSender)
{
//    CCScene* scene = new SceneTestScene();
//    CCLayer* pLayer = new SceneTestLayer2();
//    scene->addChild( pLayer, 0 );
//
//    CCDirector::sharedDirector()->pushScene( CCTransitionSlideInT::create(1, scene) );
//    scene->release();
//    pLayer->release();
}


void GameMenuLayer::onAbout(CCObject* pSender)
{
    //getCocosApp()->exit();
    //CCDirector::sharedDirector()->popScene();

    //// HA HA... no more terminate on sdk v3.0
    //// http://developer.apple.com/iphone/library/qa/qa2008/qa1561.html
    //if( [[UIApplication sharedApplication] respondsToSelector:@selector(terminate)] )
    //    [[UIApplication sharedApplication] performSelector:@selector(terminate)];
}

void GameMenuLayer::testDealloc(float dt)
{
//    CCLog("GameMenuLayer:testDealloc");
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
