#include "GameView.h"
#include "cocos2d.h"
#include "SIALogger.h"

SIASetModuleName(View);

USING_NS_CC;

using namespace Views;

bool GameView::init(std::string viewId) {
  SIACheckRetValue(!Node::init(), false);

  sprite = Sprite::create("images/gameviews/builds/" + viewId + ".png");
  SIACheckRetValue(!sprite, false);

  addChild(sprite);

  setContentSize(sprite->getContentSize());

  SIADebug("Game view init with id:%s.", viewId.c_str());

  return true;
}

bool GameView::hasPoint(const Vec2& pos) {
  const Vec2 selfPos = getPosition();
  const Size selfSize = getContentSize();
  const Rect rect = Rect(selfPos.x - selfSize.width * 0.5, 
                          selfPos.y - selfSize.height * 0.5, 
                          selfSize.width, selfSize.height);

  return rect.origin.x < pos.x && pos.x < rect.origin.x + rect.size.width &&
         rect.origin.y < pos.y && pos.y < rect.origin.y + rect.size.height;
}

bool GameView::hasPointWithSelect(const cocos2d::Vec2& pos) {
  if (hasPoint(pos)) {
    select(this);
    return true;
  }
  return false;
}