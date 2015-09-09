#include "GameView.h"
#include "cocos2d.h"
#include "SIALogger.h"

SIASetModuleName(View);

USING_NS_CC;

using namespace Views;

bool GameView::init(std::string viewId, Models::EntityPtr pModel) {
  SIACheckRetValue(!Node::init(), false);

  m_pModel = pModel;

  m_energyRangeNode = nullptr;
  m_sprite = Sprite::create("images/gameviews/builds/" + viewId + ".png");
  SIACheckRetValue(!m_sprite, false);

  addChild(m_sprite);

  setContentSize(m_sprite->getContentSize());

  SIADebug("Game view init with id:%s.", viewId.c_str());

  return true;
}

void GameView::setEnergyState(bool connected) {
  if (connected) {
    m_sprite->setOpacity(255);
  } else {
    m_sprite->setOpacity(120);
  }
}

void GameView::setEnergyRange(Vec2 range, bool visible) {
  if (range.x > 0 && range.y > 0 && visible) {
    if (nullptr == m_energyRangeNode) {
      m_energyRangeNode = DrawNode::create();
      addChild(m_energyRangeNode, -1);
    }

    m_energyRangeNode->clear();
    m_energyRangeNode->drawSolidCircle(Vec2::ZERO, range.x, 0, 50, Color4F(50, 200, 50, 200));

  } else if (nullptr != m_energyRangeNode) {
    removeChild(m_energyRangeNode);
    m_energyRangeNode = nullptr;
  }
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