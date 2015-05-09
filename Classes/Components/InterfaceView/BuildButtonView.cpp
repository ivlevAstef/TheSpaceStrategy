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
  button = ui::Button::create("images/gameviews/" + m_viewId + ".png");
  SIA_ASSERT(button);

  button->addClickEventListener(ui::Widget::ccWidgetClickCallback([this] (Ref*) {
    SIA_LOG_DBG("click on button with id:%s", m_viewId.c_str());
    click(this);
  }));

  addChild(button);

  setContentSize(button->getContentSize());
}