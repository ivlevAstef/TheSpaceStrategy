#include "BuildButtonLayer.h"
#include "BuildButtonView.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/GameTouchEvents.h"

using namespace Common;
using namespace Components::InterfaceView;
USING_NS_CC;

BuildButtonLayer* BuildButtonLayer::create(Vec2 pos) {
  BuildButtonLayer* view = new (std::nothrow)BuildButtonLayer(pos);
  if (view) {
    view->autorelease();
    return view;
  }

  SIA_LOG_ERR("can't create button layer");
  CC_SAFE_DELETE(view);
  return nullptr;
}



BuildButtonLayer::BuildButtonLayer(Vec2 pos) {
  SIA_CHECK_RET(!init(), ERR);

  BuildButtonView* buttonMainBase = BuildButtonView::create("MainBase");
  buttonMainBase->setPosition(-50, 0);
  this->addChild(buttonMainBase);


  BuildButtonView* buttonPylon = BuildButtonView::create("Pylon");
  buttonPylon->setPosition(50, 0);
  this->addChild(buttonPylon);

  this->setPosition(pos);


  GameTouchEvents::touchMoved += GameTouchEvents::DTouchMoved(this, [this] (GameTouchData data) {
    for (Node* child : getChildren()) {
      BuildButtonView* button = static_cast<BuildButtonView*>(child);
      SIA_ASSERT(child);
      
      Vec2 pos = data.worldPos - getPosition();

      if (button->containsPoint(pos)) {
        button->select();
      } else {
        button->normal();
      }
    }
  });

  GameTouchEvents::touchEnded += GameTouchEvents::DTouchEnded(this, [this] (GameTouchData data) {
    for (Node* child : getChildren()) {
      BuildButtonView* button = static_cast<BuildButtonView*>(child);
      SIA_ASSERT(child);

      if (button->isSelect()) {
        pick(button->viewId());
      }
    }

    close(this);
  });
}

BuildButtonLayer::~BuildButtonLayer() {
  GameTouchEvents::touchMoved.clean(this);
  GameTouchEvents::touchEnded.clean(this);
}