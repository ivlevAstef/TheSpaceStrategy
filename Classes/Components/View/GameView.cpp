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
}
