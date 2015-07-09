#include "BuildButtonView.h"
#include "cocos2d.h"
#include "SIALogger.h"
#include "ui/UIButton.h"

SIASetModuleName(View);

USING_NS_CC;

using namespace Views;

bool BuildButtonView::init(std::string viewId) {
  SIACheckRetValue(!Node::init(), false);

  m_viewId = viewId;

  m_normal = Sprite::create("images/gameviews/builds/" + m_viewId + ".png");
  SIACheckRetValue(!m_normal, false);

  m_select = Sprite::create("images/gameviews/builds/" + m_viewId + ".png");
  SIACheckRetValue(!m_select, false);

  m_disable = Sprite::create("images/gameviews/builds/" + m_viewId + ".png");
  SIACheckRetValue(!m_disable, false);

  m_select->setScale(0.8f);
  m_disable->setColor(Color3B(100,100,100));

  
  addChild(m_normal);
  addChild(m_select);
  addChild(m_disable);

  normal();

  setContentSize(m_normal->getContentSize());

  SIAInfo("Build Button view init with id:%s.", m_viewId.c_str());
  return true;
}

bool BuildButtonView::containsPoint(const cocos2d::Vec2& point) const {
  Rect frame;
  frame.origin = getPosition();
  frame.size = getContentSize();
  frame.origin -= Vec2(frame.size.width*0.5, frame.size.height * 0.5);
  return frame.containsPoint(point);

}


bool BuildButtonView::isSelect() {
  SIAAssert(m_select);
  return m_select->isVisible();
}

void BuildButtonView::normal() {
  SIAAssert(m_normal); SIAAssert(m_select); SIAAssert(m_disable);

  m_normal->setVisible(true);
  m_select->setVisible(false);
  m_disable->setVisible(false);
}

void BuildButtonView::select() {
  SIAAssert(m_normal); SIAAssert(m_select); SIAAssert(m_disable);

  m_normal->setVisible(false);
  m_select->setVisible(true);
  m_disable->setVisible(false);
}

void BuildButtonView::disable() {
  SIAAssert(m_normal); SIAAssert(m_select); SIAAssert(m_disable);

  m_normal->setVisible(false);
  m_select->setVisible(false);
  m_disable->setVisible(true);
}