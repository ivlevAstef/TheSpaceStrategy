#include "GameLayer.h"
#include "cocos2d.h"
#include "logger/SIAUtils_Logger.h"

using namespace Components::View;
USING_NS_CC;

static const int backgroundTag = 100;
static const int gameViewTag = 101;

GameLayer* GameLayer::create() {
  GameLayer* view = new (std::nothrow)GameLayer();
  if (view) {
    view->autorelease();
    return view;
  }

  SIA_LOG_ERR("can't create gameLayer");
  CC_SAFE_DELETE(view);
  return nullptr;
}

GameLayer::GameLayer() {
  SIA_CHECK_RET(!init(), ERR);
}

void GameLayer::addGameView(GameView* child) {
  SIA_CHECK_RET(child == nullptr, ERR);
  SIA_LOG_DBG("Add game view");
  addChild(child, 1, gameViewTag);
}

void GameLayer::setBackground(std::string backgroundId) {
  removeChildByTag(backgroundTag, true);
  Sprite* background = Sprite::create("images/backgrounds/" + backgroundId + ".png");

  SIA_CHECK_RET(background == nullptr, ERR);

  Size visibleSize = Director::getInstance()->getVisibleSize();
  background->setPosition(visibleSize.width*0.5f, visibleSize.height*0.5f);
  addChild(background, -1, backgroundTag);
  SIA_LOG_DBG("set background %s", backgroundId.c_str());
}

void GameLayer::modificationBackground(cocos2d::Color3B color) {
  Node* back = getChildByTag(backgroundTag);
  SIA_CHECK_RET(back == nullptr, WRN);

  back->setColor(color);
}

void GameLayer::onEnter() {
  Layer::onEnter();

  // Register Touch Event
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  auto listener = EventListenerTouchOneByOne::create();

  listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
  listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
  listener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
  listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

  dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void GameLayer::onExit() {
  Layer::onExit();
}

bool GameLayer::onTouchBegan(Touch* touch, Event* unused_event) {
  Vec2 pos = convertTouchToNodeSpace(touch);

  for (auto pChild : getChildren()) {
    if (pChild && pChild->getTag() == gameViewTag) {
      GameView* pView = static_cast<GameView*>(pChild);
      if (pView) {
        if (pView->hasPointWithSelect(pos)) {
          ///TODO: save select object
          return true;
        }
      } else {
        SIA_LOG_WRN("incorrect data to gamelayer");
      }

    }
  }

  return false;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event) {

}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event) {

}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event) {
}