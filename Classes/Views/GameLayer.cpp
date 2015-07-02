#include "GameLayer.h"
#include "cocos2d.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/GridMath.h"

using namespace Views;
using namespace Common;
USING_NS_CC;

static const int backgroundTag = 100;
static const int gameViewTag = 101;
static const int gridViewTag = 102;

bool GameLayer::init() {
  SIA_CHECK_ZERO(!Layer::init(), ERR);
  
  m_background = nullptr;
  m_gridView = nullptr;

  m_area = Layer::create();
  addChild(m_area, 1);

  return true;
}

void GameLayer::addGameView(GameView* child) {
  SIA_ASSERT(m_area);
  SIA_CHECK_RET(child == nullptr, ERR);

  SIA_LOG_DBG("Add game view");
  m_area->addChild(child, 1, gameViewTag);
}

void GameLayer::eraseGameView(GameView* child) {
  SIA_ASSERT(m_area);
  SIA_CHECK_RET(child == nullptr, ERR);

  SIA_LOG_DBG("Erase game view");
  m_area->removeChild(child);
}

void GameLayer::setGridView(GridView* gridView) {
  m_gridView = gridView;
  SIA_CHECK_RET(gridView == nullptr, DBG);

  gridView->setPosition(0, 0);

  addChild(gridView, 0, gridViewTag);
  SIA_LOG_DBG("set gridView");

}

void GameLayer::setBackground(std::string backgroundId) {
  removeChildByTag(backgroundTag, true);
  m_background = Sprite::create("images/backgrounds/" + backgroundId + ".png");

  SIA_CHECK_RET(m_background == nullptr, ERR);

  Size size = getContentSize();
  m_background->setPosition(size.width*0.5f, size.height*0.5f);
  addChild(m_background, -1, backgroundTag);
  SIA_LOG_DBG("set background %s", backgroundId.c_str());
}

void GameLayer::modificationBackground(cocos2d::Color3B color) {
  Node* back = getChildByTag(backgroundTag);
  SIA_CHECK_RET(back == nullptr, WRN);

  back->setColor(color);
}

void GameLayer::onEnter() {
  Layer::onEnter();

  // Register Touch Event
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  auto listener = EventListenerTouchOneByOne::create();

  listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
  listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
  listener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
  listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

  dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
  auto mouseListener = EventListenerMouse::create();

  mouseListener->onMouseDown = CC_CALLBACK_1(GameLayer::onMouseDown, this);
  mouseListener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMoved, this);
  mouseListener->onMouseUp = CC_CALLBACK_1(GameLayer::onMouseUp, this);

  dispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
#endif
}

void GameLayer::onExit() {
  Layer::onExit();
}

void GameLayer::update(const Common::ViewMath& viewMath) {
  if (m_gridView) {
    m_gridView->update(viewMath);
  }

  m_area->setPosition(viewMath.windowPos());

  Size size = getContentSize();
  Vec2 backPos = viewMath.windowPos() * 0.1f;
  backPos.x += size.width * 0.5f;
  backPos.y += size.height * 0.5f;
  
  m_background->setPosition(backPos);
}

bool GameLayer::onTouchBegan(Touch* touch, Event* unused_event) {
  this->touchBegan(touch);
  return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event) {
  this->touchMoved(touch);
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event) {
  this->touchEnded(touch);
}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event) {
  this->touchEnded(touch);
}

void GameLayer::onMouseDown(cocos2d::Event* event) {
  EventMouse* eMouse = static_cast<EventMouse*>(event);
  if (eMouse) {
    m_previousCursorLocation = eMouse->getLocationInView();
  }
}

void GameLayer::onMouseMoved(cocos2d::Event* event) {
  EventMouse* eMouse = static_cast<EventMouse*>(event);
  if (eMouse) {
    auto location = eMouse->getLocationInView();
    if (MOUSE_BUTTON_RIGHT == eMouse->getMouseButton()) {
      move(location - m_previousCursorLocation);
    }
    m_previousCursorLocation = location;
  }
}

void GameLayer::onMouseUp(cocos2d::Event* event) {

}