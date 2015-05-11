#include "BuildButtonView.h"
#include "cocos2d.h"
#include "logger/SIAUtils_Logger.h"
#include "ui/UIButton.h"

USING_NS_CC;

using namespace Components::InterfaceView;

BuildButtonView* BuildButtonView::create(std::string viewId) {
  BuildButtonView* view = new (std::nothrow)BuildButtonView(viewId);
  if (view) {
    view->autorelease();
    return view;
  }

  SIA_LOG_ERR("can't create button view");
  CC_SAFE_DELETE(view);
  return nullptr;
}

BuildButtonView::BuildButtonView(std::string viewId) {
  SIA_CHECK_RET(!init(), ERR);

  m_viewId = viewId;

  SIA_LOG_FUNC("%s", m_viewId.c_str());

  m_normal = Sprite::create("images/gameviews/" + m_viewId + ".png");
  SIA_ASSERT(m_normal);

  m_select = Sprite::create("images/gameviews/" + m_viewId + ".png");
  SIA_ASSERT(m_select);

  m_disable = Sprite::create("images/gameviews/" + m_viewId + ".png");
  SIA_ASSERT(m_disable);


  m_select->setScale(0.8);
  m_disable->setColor(Color3B(100,100,100));

  
  addChild(m_normal);
  addChild(m_select);
  addChild(m_disable);

  normal();

  setContentSize(m_normal->getContentSize());
}

bool BuildButtonView::containsPoint(const cocos2d::Vec2& point) const {
  Rect frame;
  frame.origin = getPosition();
  frame.size = getContentSize();
  frame.origin -= Vec2(frame.size.width*0.5, frame.size.height * 0.5);
  return frame.containsPoint(point);

}


bool BuildButtonView::isSelect() {
  return m_select->isVisible();
}

void BuildButtonView::normal() {
  m_normal->setVisible(true);
  m_select->setVisible(false);
  m_disable->setVisible(false);
}

void BuildButtonView::select() {
  m_normal->setVisible(false);
  m_select->setVisible(true);
  m_disable->setVisible(false);
}

void BuildButtonView::disable() {
  m_normal->setVisible(false);
  m_select->setVisible(false);
  m_disable->setVisible(true);
}