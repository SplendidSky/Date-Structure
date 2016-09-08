#ifndef __GAME_PAGE_H__
#define __GAME_PAGE_H__

#include "cocos2d.h"
#include "losePage.h"
#include "winPage.h"

using namespace cocos2d;

class MainGame : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	// initialize game
	virtual bool init();
	void addMap();
	// add player
	void addPlayer();//TODO
	// add enemies
	void addEnemy();//TODO
	// add beans
	void addBean();//TODO
	// go to losePage
	void goToLosePage(cocos2d::Ref *pSender);
	// go to winPage
	void goToWinPage(cocos2d::Ref *pSender);
	// update to new position of enemies
	void addKeyboardListener();
	void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode code, Event* event);
	void update(float f) override;// TODO
	bool collide(Sprite *s1, Sprite *s2);
	bool collide(Sprite *s1, TMXObjectGroup *w);
	enum MOVE {UP, DOWN, LEFT, RIGHT, NO_DIRECTION};

	// a selector callback
	void menuCloseCallback(cocos2d::Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainGame);
private:
	int p_x;
	int p_y;
	int wid;
	int hei;
	std::vector<Sprite*> beans;
	Vec2 origin;
	Size visibleSize;
	MOVE move = MOVE::RIGHT;
	TMXTiledMap *map;
	TMXObjectGroup *wall;
	cocos2d::Sprite *player;
};

#endif // __GAME_PAGE_H__
