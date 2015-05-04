#include "GameView.h"
#include "cocos2d.h"
#include "logger/SIAUtils_Logger.h"

USING_NS_CC;

using namespace Components::View;

GameView* GameView::create(std::string viewId) {
  GameView* view = new (std::nothrow)GameView(viewId);
  if (view) {
    view->autorelease();
    return view;
  }

  SIA_LOG_ERR("can't create gameView");
  CC_SAFE_DELETE(view);
  return nullptr;
}

GameView::GameView(std::string viewId) {
  SIA_CHECK_RET(!init(), ERR);

  SIA_LOG_FUNC("%s", viewId.c_str());
  sprite = Sprite::create("images/gameviews/" + viewId + ".png");

  SIA_CHECK_RET(sprite == nullptr, ERR);
  addChild(sprite);

  setContentSize(sprite->getContentSize());
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