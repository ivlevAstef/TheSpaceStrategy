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