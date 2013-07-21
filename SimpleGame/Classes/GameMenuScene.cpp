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
static float alignmentItemPadding = 50;
static float menuItemPaddingCenter = 110;

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/
#define TRANSITION_DURATION (1.2f)

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
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        CCLog("GameMenuLayer:testDealloc %f, %f",winSize.width, winSize.height);
        
        this->_label = TTFFontShadowAndStroke("", 16);
        _label->retain();

        CCLog("GameMenuLayer:origin %f, %f", origin.x, origin.y);
        _label->setPosition( ccp(origin.x + _label->getFontSize()*2 , origin.y + visibleSize.height - _label->getFontSize()) );
//        _label->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(_label, 1);

        CCSprite* bg1 = CCSprite::create("menu1.png");
        bg1->setScale(winSize.width/bg1->getTextureRect().size.width);
        bg1->setPosition(ccp(winSize.width/2, winSize.height/2));
        addChild(bg1, 0);

        // Label Item (CCLabelTTF)
        CCLabelTTF* label1 = TTFFontShadowAndStroke("Shooting", 32);
        CCLabelTTF* label2 = TTFFontShadowAndStroke("Option", 32);        
        CCLabelTTF* label3 = TTFFontShadowAndStroke("Quit", 32);

        CCMenuItemLabel* item1 = CCMenuItemLabel::create( label1, this, menu_selector(GameMenuLayer::onStart) );
        CCMenuItemLabel* item2 = CCMenuItemLabel::create( label2, this, menu_selector(GameMenuLayer::onOption) );
        CCMenuItemLabel* item3 = CCMenuItemLabel::create( label3, this, menu_selector(GameMenuLayer::onQuit) );

        CCMenu* menu = CCMenu::create( item1, item2, item3, NULL );
        menu->alignItemsHorizontallyWithPadding(alignmentItemPadding);
        menu->setColor( ccc3(255, 255, 255) );
        menu->setPosition(ccp(winSize.width/2, origin.y + label1->getFontSize()));

        addChild(menu, 1);

        return true;
    }
    else
    {
        return false;
    }
}

void GameMenuLayer::onStart(CCObject* pSender)
{
    CCScene* scene = HelloWorld::scene() ;
    CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, scene);
//    scene->release();      //???why error?
    CCDirector::sharedDirector()->setDepthTest(false);
    if (pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
    //    this->runAction( CCSequence::create(
    //                            CCDelayTime::create(3),
    //                            CCCallFunc::create(this,
    //                            callfunc_selector(GameMenuLayer::gameMenuDone)),
    //                            NULL));
    //    CCScene* scene = new SceneTestScene();
    //    CCLayer* pLayer = new SceneTestLayer2();
    //    scene->addChild( pLayer, 0 );
    //    CCDirector::sharedDirector()->pushScene(scene);
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


void GameMenuLayer::onQuit(CCObject* pSender)
{
    // "quit" menu item clicked
    CCDirector::sharedDirector()->end();

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
//    CCDirector::sharedDirector()->replaceScene( HelloWorld::scene() );
}

CCLabelTTF* GameMenuLayer::TTFFontShadowAndStroke(const char *value, int fontSize)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    ccColor3B tintColorWhite = { 255, 255, 255 };
    ccColor3B strokeColor = { 0, 0, 0 };
    ccColor3B strokeShadowColor = { 0, 0, 0 };

    CCSize shadowOffset(12.0, 12.0);

    ccFontDefinition TextDef;
    TextDef.m_fontSize = fontSize;
    TextDef.m_fontName = std::string("fonts/Marker Felt.ttf");

    TextDef.m_shadow.m_shadowEnabled = false;
    TextDef.m_shadow.m_shadowOffset  = shadowOffset;
    TextDef.m_shadow.m_shadowOpacity = 1.0;
    TextDef.m_shadow.m_shadowBlur    = 1.0;
    TextDef.m_stroke.m_strokeEnabled = true;
    TextDef.m_stroke.m_strokeColor   = strokeColor;
    TextDef.m_stroke.m_strokeSize    = 1.5;
    TextDef.m_fontFillColor   = tintColorWhite;
    
   return CCLabelTTF::createWithFontDefinition(value, TextDef);

}

GameMenuLayer::~GameMenuLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}
