#include "winPage.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
USING_NS_CC;

Scene* Win::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Win::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Win::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	visibleHeight = visibleSize.height;
	visibleWidth = visibleSize.width;

	auto label = Label::createWithTTF("  o  gr  tul  tio  !", "fonts/Marker Felt.ttf", 60);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2 + 30,
		origin.y + visibleSize.height / 2 + 60));
	label->setColor(ccc3(255, 255, 0));
	// add the label as a child to this layer
	this->addChild(label, 0);
	
	//吃豆人
	man = Sprite::create("sprite/player2.png");
	man->setPosition(Vec2(visibleSize.width / 2 + origin.x - 145, visibleSize.height / 2 + origin.y + 70));
	man->setScale(0.2);
	this->addChild(man, 1);
	/*auto mAnimation1 = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "sprite/player%d.png", i);
		mAnimation1->addSpriteFrameWithFile(nameSize);
	}
	mAnimation1->setDelayPerUnit(0.1f);
	mAnimation1->setLoops(-1);
	auto mAnimate1 = Animate::create(mAnimation1);
	man->runAction(mAnimate1);*/

	//红色怪物
	red = Sprite::create("sprite/player1.png");
	red->setPosition(Vec2(visibleSize.width / 2 + origin.x - 65, visibleSize.height / 2 + 55));
	red->setScale(0.1);
	this->addChild(red, 1);
	auto mAnimation = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "sprite/red%d.png", i);
		mAnimation->addSpriteFrameWithFile(nameSize);
	}
	mAnimation->setDelayPerUnit(0.05f);
	mAnimation->setLoops(-1);
	auto mAnimate = Animate::create(mAnimation);
	red->runAction(mAnimate);

	//蓝色怪物
	blue = Sprite::create("sprite/player1.png");
	blue->setPosition(Vec2(visibleSize.width / 2 + origin.x+ 14, visibleSize.height / 2 + 55));
	blue->setScale(0.1);
	this->addChild(blue, 1);
	auto mAnimation2 = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "sprite/blue%d.png", i);
		mAnimation2->addSpriteFrameWithFile(nameSize);
	}
	mAnimation2->setDelayPerUnit(0.05f);
	mAnimation2->setLoops(-1);
	auto mAnimate2 = Animate::create(mAnimation2);
	blue->runAction(mAnimate2);

	//橘黄色怪物
	orange = Sprite::create("sprite/player1.png");
	orange->setPosition(Vec2(visibleSize.width / 2 + origin.x + 103, visibleSize.height / 2 + 55));
	orange->setScale(0.1);
	this->addChild(orange, 1);
	auto mAnimation3 = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "sprite/orange%d.png", i);
		mAnimation3->addSpriteFrameWithFile(nameSize);
	}
	mAnimation3->setDelayPerUnit(0.05f);
	mAnimation3->setLoops(-1);
	auto mAnimate3 = Animate::create(mAnimation3);
	orange->runAction(mAnimate3);

	//紫色怪物
	pink = Sprite::create("sprite/player1.png");
	pink->setPosition(Vec2(visibleSize.width / 2 + origin.x + 190, visibleSize.height / 2 + 55));
	pink->setScale(0.1);
	this->addChild(pink, 1);
	auto mAnimation4 = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "sprite/pink%d.png", i);
		mAnimation4->addSpriteFrameWithFile(nameSize);
	}
	mAnimation4->setDelayPerUnit(0.05f);
	mAnimation4->setLoops(-1);
	auto mAnimate4 = Animate::create(mAnimation4);
	pink->runAction(mAnimate4);

	RestartButton = Button::create();
	RestartButton->setTitleText("Play again");
	RestartButton->setTitleFontSize(25);
	RestartButton->setPosition(Size(visibleWidth / 2, visibleHeight / 3));
	RestartButton->setTitleFontName("Marker Felt");
	//RestartButton->addClickEventListener(CC_CALLBACK_0(StartPage::start_function, this));
	this->addChild(RestartButton, 2);

	return true;
}
