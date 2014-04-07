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
// LayerIgnoreAnchorPointPos
#define kLayerIgnoreAnchorPoint  1000

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
        
        CCDictionary *strings = CCDictionary::createWithContentsOfFile("strings.xml");
        const char *version = ((CCString*)strings->objectForKey("Version"))->m_sString.c_str();
//        const char *info = ((CCString*)strings->objectForKey("Info"))->m_sString.c_str();
       _layer->getLabel()->setString(version);
       
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
//        CCLog("GameMenuLayer:testDealloc %f, %f",winSize.width, winSize.height);
        
        this->_label = TTFFontShadowAndStroke("", 16);
        _label->retain();

//        CCLog("GameMenuLayer:origin %f, %f", origin.x, origin.y);
		CCLog("GameMenuLayer:getContentSize %f, %f", _label->getContentSize().width, _label->getContentSize().height);
		_label->setAnchorPoint(ccp(0, 0));
		_label->setPosition( ccp(origin.x + _label->getFontSize() , origin.y + visibleSize.height - _label->getFontSize()*3/2) );
//        _label->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(_label, 1);

        this->setTouchEnabled(true);

        CCSprite* bg = CCSprite::create("Menu1.png");
        bg->setScale(visibleSize.width/bg->getTextureRect().size.width);
        bg->setPosition(ccp(winSize.width/2, winSize.height/2));
        addChild(bg, 0);

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
//        schedule( schedule_selector(GameMenuLayer::testDealloc) );

                //
        // Configure shader to mimic glAlphaTest
//        //
//        CCGLProgram *alphaTestShader = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest);
//        GLint alphaValueLocation = glGetUniformLocation(alphaTestShader->getProgram(), kCCUniformAlphaTestValue);
//
//        // set alpha test value
//        // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
//        if (getShaderProgram())
//        {
//            getShaderProgram()->setUniformLocationWith1f(alphaValueLocation, 0.0f);
//        }
//        
//            CCNode* node = CCNode::create();
//        // camera uses the center of the image as the pivoting point
//        node->setContentSize( CCSizeMake(200,200) );
//        node->setAnchorPoint( ccp(0.5f, 0.5f));
//        node->setPosition( ccp(winSize.width*3/4, winSize.height*3/4));
//
//        addChild(node, 10);
//
//        CCSprite* sprite = CCSprite::create("Projectile.png", CCRectMake(85*0, 121*1, 40, 40));
//        sprite->setPosition(ccp( winSize.width*3/4, winSize.height*3/4) );
//        sprite->setVertexZ( 10 + 40 );
//        sprite->setShaderProgram(alphaTestShader);
//        node->addChild(sprite, 10);
//            
//
//        node->runAction( CCOrbitCamera::create(10, 1, 0, 0, 360, 0, 0) );
    

        return true;
    }
    else
    {
        return false;
    }
}

void GameMenuLayer::onStart(CCObject* pSender)
{
    CCScene* scene = HelloWorld::scene(m_uMode) ;
    CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, scene);
//    scene->release();      //???why error?
    CCDirector::sharedDirector()->setDepthTest(false);
    if (pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void GameMenuLayer::onOption(CCObject* pSender)
{
    CCNode* pLayer = this->getChildByTag(kLayerIgnoreAnchorPoint);
    if(pLayer != NULL)
    {
        this->removeChild(pLayer);
    }

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor *l = CCLayerColor::create(ccc4(0, 0, 0, 0x70), s.width/10, s.width/30);
    CCSize lsize = l->getContentSize();
    CCLog("++++++++getContentSize  x:%f, y:%f", lsize.width, lsize.height/2);
    l->setAnchorPoint(ccp(0.5f, 0.5f));
    l->ignoreAnchorPointForPosition(false);
    l->setPosition(ccp( s.width/2, s.height/2));

// add BG    
    CCSprite* bg = CCSprite::create("MenuBg.png");
    bg->setScale(lsize.height/bg->getTextureRect().size.height);
    bg->setPosition(ccp(lsize.width-bg->getTextureRect().size.width/20, lsize.height/2));
    l->addChild(bg, 10);


// add Menu    
    CCLabelTTF* label = TTFFontShadowAndStroke("SZ ZENG 2013 MOD", 16);
    CCLabelTTF* label1 = TTFFontShadowAndStroke("SZ shoots SY ", 48);
    CCLabelTTF* label2 = TTFFontShadowAndStroke("SY shoots SZ ", 48);

    CCMenuItemToggle *item = CCMenuItemToggle::createWithTarget(this, 
                                                                menu_selector(GameMenuLayer::optionCallback),
                                                                CCMenuItemLabel::create(label1),
                                                                CCMenuItemLabel::create(label2),
                                                                NULL );
    CCMenu* menu = CCMenu::create(item, NULL);
    menu->setContentSize(CCSizeMake(0.0, 0.0));  //WHY?!
    menu->setPosition(ccp(lsize.width/2, lsize.height*0.5));
    menu->setScale(0.1);

    l->addChild(label);
    l->addChild(menu);

    label->setPosition(ccp(lsize.width/2, lsize.height*0.9));
    label->setScale(0.1);

    this->addChild(l, 1, kLayerIgnoreAnchorPoint);

    CCScaleBy *scale = CCScaleBy::create(0.1, 10);
    CCScaleBy* back = (CCScaleBy*)scale->reverse();
    CCSequence *seq = CCSequence::create(scale, NULL);
    
    l->runAction(CCRepeat::create(seq, 1));
}

void GameMenuLayer::optionCallback(CCObject* pSender)
{
    if(m_uMode == 0)
    {
        m_uMode = 1; //SY shoot SZ
    }
    else
    {
        m_uMode = 0; //SZ shoot SY
    }
    CCLog("Game mode : %d ", m_uMode);
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

void GameMenuLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    // Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocation();
    CCLog("++++++++after  x:%f, y:%f", location.x, location.y); 
    
    CCNode* pLayer = this->getChildByTag(kLayerIgnoreAnchorPoint);
    if(pLayer == NULL)
    	return;

    CCScaleBy *scale = CCScaleBy::create(0.1, 200);
    CCScaleBy* back = (CCScaleBy*)scale->reverse();
    CCSequence *seq = CCSequence::create(back, NULL);

    pLayer->runAction(CCRepeat::create(seq, 1));
//    this->removeChild(pLayer);

    
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

    ccColor3B tintColorWhite = { 255, 255, 255 };
    ccColor3B strokeColor = { 0, 0, 0 };
    ccColor3B strokeShadowColor = { 0, 0, 0 };

    CCSize shadowOffset(12.0, 12.0);

    ccFontDefinition TextDef;
    TextDef.m_fontSize = fontSize;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    TextDef.m_fontName = std::string("fonts/tahoma.ttf");
#else
    TextDef.m_fontName = std::string("fonts/Felt.ttf");
#endif

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
