/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
 Copyright (c) 2010      Ray Wenderlich
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "GameMenuScene.h"

using namespace cocos2d;

bool GameOverScene::init()
{
    if( CCScene::init() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

GameOverScene::~GameOverScene()
{
}


bool GameOverLayer::init()
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
                                callfunc_selector(GameOverLayer::gameOverDone)),
                                NULL));
        
        return true;
    }
    else
    {
        return false;
    }
}

void GameOverLayer::gameOverDone()
{

    // create a scene. it's an autorelease object
    GameMenuScene *gameMenuScene = GameMenuScene::create();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();

    CCDirector::sharedDirector()->replaceScene(gameMenuScene);
}

GameOverLayer::~GameOverLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}

bool GameWinScene::init()
{
    if( CCScene::init() )
    {
        this->_layer = GameWinLayer::create();
        this->_layer->retain();
        this->addChild(_layer);
        
        return true;
    }
    else
    {
        return false;
    }
}

GameWinScene::~GameWinScene()
{
    if (_layer)
    {
        _layer->release();
        _layer = NULL;
    }
}


bool GameWinLayer::init()
{
    if ( CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
    {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        this->_label = CCLabelTTF::create("","Artial", 32);
        _label->retain();
        _label->setColor( ccc3(0, 0, 0) );
        _label->setPosition( ccp(winSize.width*3/4, winSize.height*3/4) );
        this->addChild(_label);
        

        // Determine the random ending
        int min= (int)2.0;
        int max = (int)6.0;
        int range = max - min;
        // srand( TimGetTicks() );
        int actual = (int)( rand() % range ) + min;
        
        char str[20] = {0};
        sprintf(str, "WinBG%d.png", actual);
        
//        CCLog("GameWinLayer++%s",str);
        CCSprite* bg = CCSprite::create(str);
        bg->setScale(visibleSize.height/bg->getTextureRect().size.height);
        bg->setPosition(ccp(origin.x + (bg->getTextureRect().size.width*visibleSize.height)/
            (2*bg->getTextureRect().size.height),
            winSize.height/2));
//        bg->setOpacity(50);
        this->addChild(bg, 0);


        // fixed BG
        CCSprite* bg1 = CCSprite::create("WinBG1.png");
        bg1->setPosition( ccp(winSize.width - bg1->getTextureRect().size.width/2 , origin.y + bg1->getTextureRect().size.height/2) );
//        bg->setOpacity(50);
        this->addChild(bg1, 0);

        this->runAction( CCSequence::create(
                                CCDelayTime::create(6),
                                CCCallFunc::create(this, 
                                callfunc_selector(GameWinLayer::gameOverDone)),
                                NULL));
        
        return true;
    }
    else
    {
        return false;
    }
}

void GameWinLayer::gameOverDone()
{
    GameOverLayer::gameOverDone();
}

GameWinLayer::~GameWinLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}

bool GameLoseScene::init()
{
    if( CCScene::init() )
    {
        this->_layer = GameLoseLayer::create();
        this->_layer->retain();
        this->addChild(_layer);
        
        return true;
    }
    else
    {
        return false;
    }
}

GameLoseScene::~GameLoseScene()
{
    if (_layer)
    {
        _layer->release();
        _layer = NULL;
    }
}


bool GameLoseLayer::init()
{
    if ( CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
    {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite* bg = CCSprite::create("Lose.png");
//        bg->setScale(winSize.width/bg->getTextureRect().size.width);
        bg->setPosition(ccp(winSize.width/4, winSize.height/2));
        this->addChild(bg, 0);
        
//        CCLog("GameLoseLayer");
        this->_label = CCLabelTTF::create("","Artial", 32);
        _label->retain();
        _label->setColor( ccc3(0, 0, 0) );
        _label->setPosition( ccp(winSize.width*3/5 , winSize.height/2) );
        this->addChild(_label, 1);
        
        this->runAction( CCSequence::create(
                                CCDelayTime::create(3),
                                CCCallFunc::create(this, 
                                callfunc_selector(GameLoseLayer::gameOverDone)),
                                NULL));
        
        return true;
    }
    else
    {
        return false;
    }
}

void GameLoseLayer::gameOverDone()
{
    GameOverLayer::gameOverDone();
}

GameLoseLayer::~GameLoseLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}

