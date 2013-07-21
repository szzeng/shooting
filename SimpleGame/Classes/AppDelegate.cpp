#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameMenuScene.h"

USING_NS_CC;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCSize designSize = CCSizeMake(480, 320);
    std::vector<std::string> searchPaths;

    if (screenSize.height > 320)
    {
        CCSize resourceSize = CCSizeMake(960, 640);
        searchPaths.push_back("hd");
        searchPaths.push_back("sd");
        pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
    }
    else
    {
        searchPaths.push_back("sd");
        pDirector->setContentScaleFactor(320.0f/designSize.height);
    }
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    
    CCDictionary *strings = CCDictionary::createWithContentsOfFile("strings.xml");
    //?����?Hello?��?D��??�� objectForKey?��?Ykey��???��???��|��?string
    const char *version = ((CCString*)strings->objectForKey("Version"))->m_sString.c_str();
    //?����?Info?��?D��??��
    const char *info = ((CCString*)strings->objectForKey("Info"))->m_sString.c_str();
    
    // create a scene. it's an autorelease object
    GameMenuScene *gameMenuScene = GameMenuScene::create();
    gameMenuScene->getLayer()->getLabel()->setString(version);

    // run
    pDirector->runWithScene(gameMenuScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
