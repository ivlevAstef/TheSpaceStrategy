#include "BuildButtonLayer.h"
#include "BuildButtonView.h"
#include "SIALogger.h"
#include "Common/GameTouchEvents.h"

SIASetModuleName(View);

using namespace Common;
using namespace Views;
USING_NS_CC;

bool BuildButtonLayer::init(Vec2 pos) {
  SIACheckRetValue(!Node::init(), false);

  BuildButtonView* buttonMainBase = BuildButtonView::create("MainBase");
  if (buttonMainBase) {
    buttonMainBase->setPosition(-50, 0);
    this->addChild(buttonMainBase);
  } else {
    SIAError("Can't create button main base.");
  }

  BuildButtonView* buttonPylon = BuildButtonView::create("Pylon");
  if (buttonPylon) {
    buttonPylon->setPosition(50, 0);
    this->addChild(buttonPylon);
  } else {
    SIAError("Can't create button pylon.");
  }

  BuildButtonView* buttonMinerMineral = BuildButtonView::create("MinerMinerals");
  if (buttonMinerMineral) {
    buttonMinerMineral->setPosition(0, -50);
    this->addChild(buttonMinerMineral);
  } else {
    SIAError("Can't create button miner mineral.");
  }

  this->setPosition(pos);

  GameTouchEvents::touchMoved += GameTouchEvents::DTouchMoved(this, [this] (TouchPos touchPos) {
    Vec2 pos = getPosition();
    pos = Vec2(touchPos.x - pos.x, touchPos.y - pos.y);

    for (Node* child : getChildren()) {
      BuildButtonView* button = static_cast<BuildButtonView*>(child);
      SIAFatalAssert(button);

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
      SIAFatalAssert(button);

      if (button->isSelect()) {
        pick(button->viewId());
      }
    }

    close(this);
  });

  SIADebug("Init Build button layer in pos:{%f,%f}.", pos.x, pos.y);

  return true;
}

BuildButtonLayer::~BuildButtonLayer() {
  GameTouchEvents::touchMoved.clean(this);
  GameTouchEvents::touchEnded.clean(this);
}