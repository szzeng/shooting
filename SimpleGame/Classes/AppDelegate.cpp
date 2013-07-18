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
        searchPaths.push_back("hd");
        searchPaths.push_back("sd");
        pDirector->setContentScaleFactor(640.0f/designSize.height);
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

    // create a scene. it's an autorelease object

	
	/** 在cocos2d-x中使用中文	**/
	//利用CCDictionary来读取xml
	CCDictionary *strings = CCDictionary::createWithContentsOfFile("strings.xml");
	//读取Hello键中的值 objectForKey根据key，获取对应的string
	const char *hello = ((CCString*)strings->objectForKey("Hello"))->m_sString.c_str();
	//读取Info键中的值
	const char *info = ((CCString*)strings->objectForKey("Info"))->m_sString.c_str();
	

	GameMenuScene *gameMenuScene = GameMenuScene::create();
	gameMenuScene->getLayer()->getLabel()->setString(hello);

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
