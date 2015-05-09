#include "BuildButtonLayer.h"
#include "BuildButtonView.h"
#include "logger/SIAUtils_Logger.h"

using namespace Components::InterfaceView;

BuildButtonLayer* BuildButtonLayer::create(cocos2d::Vec2 pos) {
  BuildButtonLayer* view = new (std::nothrow)BuildButtonLayer(pos);
  if (view) {
    view->autorelease();
    return view;
  }

  SIA_LOG_ERR("can't create button layer");
  CC_SAFE_DELETE(view);
  return nullptr;
}

BuildButtonLayer::BuildButtonLayer(cocos2d::Vec2 pos) {
  SIA_CHECK_RET(!init(), ERR);

  BuildButtonView* buttonMainBase = BuildButtonView::create("MainBase");
  this->addChild(buttonMainBase);


  this->setPosition(pos);
}