#include "GameView.h"
#include "cocos2d.h"

USING_NS_CC;

using namespace Components::View;

GameView* GameView::create(std::string viewId) {
  GameView* view = new (std::nothrow)GameView(viewId);
  if (view) {
    view->autorelease();
    return view;
  }

  CC_SAFE_DELETE(view);
  return nullptr;
}

GameView::GameView(std::string viewId) {
  init();
  sprite = Sprite::create("images/gameviews/" + viewId + ".png");
  this->addChild(sprite);
}
