#include "GameLayer.h"
#include "cocos2d.h"

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

  CC_SAFE_DELETE(view);
  return nullptr;
}

GameLayer::GameLayer() {
  init();
  scheduleUpdate();
}

void GameLayer::addGameView(GameView* child) {
  addChild(child, 1, gameViewTag);
}

void GameLayer::setBackground(std::string backgroundId) {
  removeChildByTag(backgroundTag, true);
  Sprite* background = Sprite::create("images/backgrounds/" + backgroundId + ".png");
  if (background) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    background->setPosition(visibleSize.width*0.5f, visibleSize.height*0.5f);
    addChild(background, -1, backgroundTag);
  }
}

void GameLayer::modificationBackground(cocos2d::Color3B color) {
  Node* back = getChildByTag(backgroundTag);
  if (back) {
    back->setColor(color);
  }
}

void GameLayer::update(float delta) {
  for (Node* child: _children) {
    if (gameViewTag == child->getTag()) {
      GameView* gView = static_cast<GameView*>(child);
      if (gView) {
        SIAUtils::Position pos = gView->cell();

        gView->setPosition(pos.x * 100, pos.y * 100);
      }
    }
  }
}