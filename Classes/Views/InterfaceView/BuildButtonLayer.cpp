#include "BuildButtonLayer.h"
#include "BuildButtonView.h"
#include "SIALogger.h"
#include "Common/GameTouchEvents.h"

SIASetModuleName(View);

using namespace Common;
using namespace Views;
USING_NS_CC;

const float BuildButtonLayer::circleRadius = 60;
const float BuildButtonLayer::buttonCircleRadius = 40;

bool BuildButtonLayer::init(Vec2 pos) {
  SIACheckRetValue(!Node::init(), false);

  m_pCircleBack = DrawNode::create();

  if (m_pCircleBack) {
    m_pCircleBack->drawSolidCircle(Vec2::ZERO, buttonCircleRadius, 0, 30, Color4F(0.5f, 0.0f, 0.5f, 0.2f));
    m_pCircleBack->drawSolidCircle(Vec2::ZERO, circleRadius, 0, 50, Color4F(0.5f, 0.5f, 1.0f, 0.5f));
    addChild(m_pCircleBack);
  } else {
    SIAError("Can't create circle back.");
  }

  m_pButtonsNode = Node::create();

  if (m_pButtonsNode) {
    addChild(m_pButtonsNode);

    BuildButtonView* buttonMainBase = BuildButtonView::create("MainBase");
    if (buttonMainBase) {
      buttonMainBase->setPosition(buttonPosition(90));
      m_pButtonsNode->addChild(buttonMainBase);
    } else {
      SIAError("Can't create button main base.");
    }

    BuildButtonView* buttonPylon = BuildButtonView::create("Pylon");
    if (buttonPylon) {
      buttonPylon->setPosition(buttonPosition(-30));
      m_pButtonsNode->addChild(buttonPylon);
    } else {
      SIAError("Can't create button pylon.");
    }

    BuildButtonView* buttonMinerMineral = BuildButtonView::create("MinerMinerals");
    if (buttonMinerMineral) {
      buttonMinerMineral->setPosition(buttonPosition(210));
      m_pButtonsNode->addChild(buttonMinerMineral);
    } else {
      SIAError("Can't create button miner mineral.");
    }

    GameTouchEvents::touchMoved += GameTouchEvents::DTouchMoved(this, [this] (TouchPos touchPos) {
      Vec2 pos = getPosition();
      pos = Vec2(touchPos.x - pos.x, touchPos.y - pos.y);

      for (Node* child : m_pButtonsNode->getChildren()) {
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
      for (Node* child : m_pButtonsNode->getChildren()) {
        BuildButtonView* button = static_cast<BuildButtonView*>(child);
        SIAFatalAssert(button);

        if (button->isSelect()) {
          pick(button->viewId());
        }
      }

      close(this);
    });
  } else {
    SIAError("Can't create button node.");
  }

  this->setPosition(pos);
  SIADebug("Init Build button layer in pos:{%f,%f}.", pos.x, pos.y);

  return true;
}

cocos2d::Vec2 BuildButtonLayer::buttonPosition(float angleDegrees) {
  return Vec2::forAngle(angleDegrees * M_PI / 180.0f) * buttonCircleRadius;
}

BuildButtonLayer::~BuildButtonLayer() {
  GameTouchEvents::touchMoved.clean(this);
  GameTouchEvents::touchEnded.clean(this);
}