#include "BuildButtonLayer.h"
#include "BuildButtonView.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/GameTouchEvents.h"

using namespace Common;
using namespace Views;
USING_NS_CC;

bool BuildButtonLayer::init(Vec2 pos) {
  SIA_CHECK_ZERO(!Node::init(), ERR);

  BuildButtonView* buttonMainBase = BuildButtonView::create("MainBase");
  buttonMainBase->setPosition(-50, 0);
  this->addChild(buttonMainBase);


  BuildButtonView* buttonPylon = BuildButtonView::create("Pylon");
  buttonPylon->setPosition(50, 0);
  this->addChild(buttonPylon);

  BuildButtonView* buttonGetterMineral = BuildButtonView::create("MinerMinerals");
  buttonGetterMineral->setPosition(0, -50);
  this->addChild(buttonGetterMineral);

  this->setPosition(pos);


  GameTouchEvents::touchMoved += GameTouchEvents::DTouchMoved(this, [this] (TouchPos touchPos) {
    Vec2 pos = getPosition();
    pos = Vec2(touchPos.x - pos.x, touchPos.y - pos.y);

    for (Node* child : getChildren()) {
      BuildButtonView* button = static_cast<BuildButtonView*>(child);
      SIA_ASSERT(child);

      if (button->containsPoint(pos)) {
        button->select();
      } else {
        button->normal();
      }
    }
  });

  GameTouchEvents::touchEnded += GameTouchEvents::DTouchEnded(this, [this] (TouchPos) {
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