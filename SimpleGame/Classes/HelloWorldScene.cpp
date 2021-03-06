#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
unsigned int HelloWorld::m_uMode = 0;
#define TRANSITION_DURATION (1.2f)

HelloWorld::~HelloWorld()
{
    if (_targets)
    {
        _targets->release();
        _targets = NULL;
    }

    if (_projectiles)
    {
        _projectiles->release();
        _projectiles = NULL;
    }
    if (_booms)
    {
        _booms->release();
        _booms = NULL;
    }
    
//    CCLog("~HelloWorld");
    // cpp don't need to call super dealloc
    // virtual destructor will do this
}

HelloWorld::HelloWorld()
:_targets(NULL)
,_projectiles(NULL)
,_booms(NULL)
,_projectilesDestroyed(0)
{
}

CCScene* HelloWorld::scene(unsigned int mode)
{
    CCScene * scene = NULL;
    
    m_uMode = mode;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    CCSprite *player;
    
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) );

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////
        

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);
        
        // Place the menu item bottom-right conner.
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2,
                                    origin.y + pCloseItem->getContentSize().height/2));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // background 
        CCSprite* bg = CCSprite::create("Bg.png");
        bg->setScale(visibleSize.height/bg->getTextureRect().size.height);
        bg->setPosition(ccp(winSize.width/2, winSize.height/2));
        bg->setOpacity(130);
        this->addChild(bg, 0);

        /////////////////////////////
        // 2. add your codes below...
        switch ( m_uMode )
        {
            case 0 :
                player = CCSprite::create("PlayerSZ.png", CCRectMake(0, 0, 67, 100) );
                player->setPosition( ccp(origin.x + player->getContentSize().width/2,
                                         origin.y + visibleSize.height/2) );
                break;
            case 1 :
                player = CCSprite::create("PlayerSY.png", CCRectMake(0, 0, 117, 107) );
                player->setPosition( ccp(visibleSize.width/2,
                                         origin.y + visibleSize.height-player->getContentSize().width/2) );
                break;
            default:
                player = CCSprite::create("PlayerSZ.png", CCRectMake(0, 0, 67, 100) );
                player->setPosition( ccp(origin.x + player->getContentSize().width/2,
                                         origin.y + visibleSize.height/2) );
        }
        
        this->addChild(player);

        this->schedule( schedule_selector(HelloWorld::gameLogic), 0.5 );

        this->setTouchEnabled(true);

        _targets = new CCArray;
        _projectiles = new CCArray;
        _booms= new CCArray;

        // use updateGame instead of update, otherwise it will conflit with SelectorProtocol::update
        // see http://www.cocos2d-x.org/boards/6/topics/1478
        this->schedule( schedule_selector(HelloWorld::updateGame) );

        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav", true);

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

// cpp with cocos2d-x
void HelloWorld::addTarget()
{
    CCSprite *target;
//    CCAnimation* animation;
    CCDelayTime *delay;

    switch ( m_uMode )
    {
        case 0 :
            target = CCSprite::create("TargetSY.png", CCRectMake(0,0,43,65) ); 
            
//            animation = CCAnimation::create();
//            animation->addSpriteFrameWithFileName("TargetSY.png");
//            animation->addSpriteFrameWithFileName("TargetSY1.png");
//            animation->setDelayPerUnit(0.3f);
//            animation->setRestoreOriginalFrame(true);
//            target->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
//            CCActionInterval* seq = CCSequence::create( animate,
//                               CCFlipX::create(true),
//                               animate->copy()->autorelease(),
//                               CCFlipX::create(false),
//                               NULL);
            delay = CCDelayTime::create(0.3);
            target->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(delay, CCFlipX::create(true),delay->copy()->autorelease(), CCFlipX::create(false),NULL)));
            
            break;
        case 1 :
            target = CCSprite::create("TargetSZ.png", CCRectMake(0,0,46,65) );                
            target->setRotation(20);
            target->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(CCRotateBy::create(0.5,-40),CCRotateBy::create(0.5,40),NULL)));
            break;
        default:
            target = CCSprite::create("TargetSY.png", CCRectMake(0,0,43,65) );        
    }
    
    // Determine where to spawn the target along the Y axis
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    float minY = target->getContentSize().height/2;
    float maxY = winSize.height -  target->getContentSize().height/2;
    int rangeY = (int)(maxY - minY);
    // srand( TimGetTicks() );
    int actualY = ( rand() % rangeY ) + (int)minY;

    // Create the target slightly off-screen along the right edge,
    // and along a random position along the Y axis as calculated
    target->setPosition( 
        ccp(winSize.width + (target->getContentSize().width/2), 
            CCDirector::sharedDirector()->getVisibleOrigin().y + actualY) );
    this->addChild(target);

    // Determine speed of the target
    int minDuration = (int)2.0;
    int maxDuration = (int)4.0;
    int rangeDuration = maxDuration - minDuration;
    // srand( TimGetTicks() );
    int actualDuration = ( rand() % rangeDuration ) + minDuration;

    // Create the actions
    CCFiniteTimeAction* actionMove = CCMoveTo::create( (float)actualDuration,
                                            ccp(0 - target->getContentSize().width/2, actualY) );
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this, 
                                            callfuncN_selector(HelloWorld::spriteMoveFinished));
    target->runAction( CCSequence::create(actionMove, actionMoveDone, NULL) );

    // Add to targets array
    target->setTag(1);
    _targets->addObject(target);
}

void HelloWorld::spriteMoveFinished(CCNode* sender)
{
//    CCSprite *sprite = (CCSprite *)sender;
    CCSprite* sprite = dynamic_cast<CCSprite*>(sender);

    if (sprite->getTag() == 1)  // target
    {
        _targets->removeObject(sprite);
        
        GameLoseScene *GameLoseScene = GameLoseScene::create();
        GameLoseScene->getLayer()->getLabel()->setString("You Lose :[");
        CCDirector::sharedDirector()->replaceScene(GameLoseScene);
        return;

    }
    else if (sprite->getTag() == 2) // projectile
    {
        _projectiles->removeObject(sprite);
    }
    else
    {
        _booms->removeObject(sprite);
    }
    
    this->removeChild(sprite, true);
}

void HelloWorld::gameLogic(float dt)
{
    this->addTarget();
}

// cpp with cocos2d-x
void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    // Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocation();
    
//    CCLog("++++++++after  x:%f, y:%f", location.x, location.y);

    // Set up initial location of projectile
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSprite *projectile = CCSprite::create("Projectile.png", CCRectMake(0, 0, 20, 20));

    switch ( m_uMode )    
    {
        case 0 :
            projectile->setPosition( ccp(origin.x+20, origin.y+winSize.height/2) );        
            break;
        case 1 :
            projectile->setPosition( ccp(winSize.width/2, origin.y+winSize.height-55));
            break;
        default:
            projectile->setPosition( ccp(origin.x+20, origin.y+winSize.height/2) );        
    }

    // Determinie offset of location to projectile
    float offX = location.x - projectile->getPosition().x;
    float offY = location.y - projectile->getPosition().y;
    
    projectile->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(CCScaleTo::create(0.2, 0.7),CCScaleTo::create(0.2,1),NULL)));
    // Ok to add now - we've double checked position
    this->addChild(projectile);
    
    float realX, ratio, realY, offRealX, offRealY;
    CCPoint realDest;
    if (offX <= 0)   // Bail out if we are shooting down or backwards
    {
        // Determine where we wish to shoot the projectile to
        realX = projectile->getPosition().x;
        ratio = offY / offX;
        realY = projectile->getPosition().y - (realX * ratio);
        realDest = ccp(0, realY);
        
        // Determine the length of how far we're shooting
        offRealX = projectile->getPosition().x;
        offRealY = realY - projectile->getPosition().y;
    }
    else
    {
        // Determine where we wish to shoot the projectile to
        realX = origin.x+winSize.width + (projectile->getContentSize().width/2);
        ratio = offY / offX;
        realY = ((realX-projectile->getPosition().x) * ratio) + projectile->getPosition().y;
        realDest = ccp(realX, realY);
        
        // Determine the length of how far we're shooting
        offRealX = realX - projectile->getPosition().x;
        offRealY = realY - projectile->getPosition().y;
    }
    
    float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));
    float velocity = 120/1; // 480pixels/1sec
    float realMoveDuration = length/velocity;

    // Move projectile to actual endpoint
    projectile->runAction( CCSequence::create(
        CCMoveTo::create(realMoveDuration, realDest),
        CCCallFuncN::create(this, 
                            callfuncN_selector(HelloWorld::spriteMoveFinished)), 
        NULL) );

    // Add to projectiles array
    projectile->setTag(2);
    _projectiles->addObject(projectile);

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pew-pew-lei.wav");
}

void HelloWorld::updateGame(float dt)
{
    CCArray *projectilesToDelete = new CCArray;
    CCObject* it = NULL;
    CCObject* jt = NULL;

    // for (it = _projectiles->begin(); it != _projectiles->end(); it++)
    CCARRAY_FOREACH(_projectiles, it)
    {
        CCSprite *projectile = dynamic_cast<CCSprite*>(it);
       
        if ( projectile->getTag() != 3 ) // not booms
        {
            CCRect projectileRect = CCRectMake(
                projectile->getPosition().x - (projectile->getContentSize().width/2),
                projectile->getPosition().y - (projectile->getContentSize().height/2),
                projectile->getContentSize().width,
                projectile->getContentSize().height);
            
            CCArray* targetsToDelete =new CCArray;
            
            // for (jt = _targets->begin(); jt != _targets->end(); jt++)
            CCARRAY_FOREACH(_targets, jt)
            {
                CCSprite *target = dynamic_cast<CCSprite*>(jt);
                CCRect targetRect = CCRectMake(
                    target->getPosition().x - (target->getContentSize().width/2),
                    target->getPosition().y - (target->getContentSize().height/2),
                    target->getContentSize().width,
                    target->getContentSize().height);
            
                // if (CCRect::CCRectIntersectsRect(projectileRect, targetRect))
                if (projectileRect.intersectsRect(targetRect))
                {
                    targetsToDelete->addObject(target);
                   target->setVisible(false);
                    
                    CCSprite *boomAnimation = CCSprite::create("Projectile.png", CCRectMake(0, 0, 20, 20));
                    boomAnimation->setPosition(ccp(target->getPosition().x, target->getPosition().y));
                    boomAnimation->runAction( CCSequence::create(
                        CCScaleTo::create(0.5, 0.5),CCScaleTo::create(0.5,2),
                        CCScaleTo::create(0.5, 0.5),CCScaleTo::create(0.5,2),
                        CCCallFuncN::create(this, 
                                            callfuncN_selector(HelloWorld::spriteMoveFinished)), 
                        NULL) );
                    // Add to projectiles array
                    boomAnimation->setTag(3);
                    _booms->addObject(boomAnimation);
                    this->addChild(boomAnimation);
                }
            }
            
            // for (jt = targetsToDelete->begin(); jt != targetsToDelete->end(); jt++)
            CCARRAY_FOREACH(targetsToDelete, jt)
            {
                CCSprite *target = dynamic_cast<CCSprite*>(jt);
                _targets->removeObject(target);
                this->removeChild(target, true);
            
                _projectilesDestroyed++;
                if (_projectilesDestroyed >= 25)
                {
                    GameWinScene *GameWinScene = GameWinScene::create();
                    GameWinScene->getLayer()->getLabel()->setString("You Win!");
                        CCScene* pScene = CCTransitionFade::create(TRANSITION_DURATION, GameWinScene);
                    //    scene->release();      //???why error?
                        CCDirector::sharedDirector()->setDepthTest(false);
                        if (pScene)
                        {
                            this->unschedule( schedule_selector(HelloWorld::updateGame) );
                            CCDirector::sharedDirector()->replaceScene(pScene);
                        }
                        return;
                }
            }
            
            if (targetsToDelete->count() > 0)
            {
                projectilesToDelete->addObject(projectile);
            }
            targetsToDelete->release();

        }
    }

    // for (it = projectilesToDelete->begin(); it != projectilesToDelete->end(); it++)
    CCARRAY_FOREACH(projectilesToDelete, it)
    {
        CCSprite* projectile = dynamic_cast<CCSprite*>(it);
        _projectiles->removeObject(projectile);
        this->removeChild(projectile, true);
    }
    projectilesToDelete->release();
}

void HelloWorld::registerWithTouchDispatcher()
{
    // CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}
