#include "GameLayer.h"
#include "cocos2d.h"
#include "SIALogger.h"

SIASetModuleName(View);

using namespace Views;
using namespace Common;
USING_NS_CC;

static const int backgroundTag = 100;
static const int gameViewTag = 101;
static const int gridViewTag = 102;

bool GameLayer::init() {
  SIACheckRetValue(!Layer::init(), false);

  m_background = nullptr;
  m_gridView = nullptr;

  m_area = Layer::create();
  SIAFatalAssert(m_area);
  addChild(m_area, 1);

  return true;
}

void GameLayer::addGameView(GameView* child) {
  SIACheckRet(!child);
  SIAAssert(m_area);

  SIADebug("Add game view.");
  m_area->addChild(child, 1, gameViewTag);
}

void GameLayer::eraseGameView(GameView* child) {
  SIACheckRet(!child);
  SIAAssert(m_area);

  SIADebug("Erase game view.");
  m_area->removeChild(child);
}

void GameLayer::setGridView(GridView* gridView) {
  m_gridView = gridView;
  SIACheckRet(!gridView);

  gridView->setPosition(0, 0);

  addChild(gridView, 0, gridViewTag);
  SIADebug("Set gridView.");

}

void GameLayer::setBackground(std::string backgroundId) {
  removeChildByTag(backgroundTag, true);
  m_background = Sprite::create("images/backgrounds/" + backgroundId + ".png");

  SIACheckRet(!m_background);

  Size size = getContentSize();
  m_background->setPosition(size.width*0.5f, size.height*0.5f);
  addChild(m_background, -1, backgroundTag);
  SIADebug("set background with id:%s.", backgroundId.c_str());
}

void GameLayer::modificationBackground(cocos2d::Color3B color) {
  Node* back = getChildByTag(backgroundTag);
  SIACheckRet(!back);

  back->setColor(color);
}

void GameLayer::onEnter() {
  Layer::onEnter();

  // Register Touch Event
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  auto listener = EventListenerTouchOneByOne::create();
  SIACheckRet(!dispatcher);
  SIACheckRet(!listener);

  listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
  listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
  listener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
  listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

  dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
  auto mouseListener = EventListenerMouse::create();
  SIACheckRet(!mouseListener);

  mouseListener->onMouseDown = CC_CALLBACK_1(GameLayer::onMouseDown, this);
  mouseListener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMoved, this);
  mouseListener->onMouseUp = CC_CALLBACK_1(GameLayer::onMouseUp, this);

  dispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
#endif
}

void GameLayer::onExit() {
  Layer::onExit();
}

void GameLayer::draw(const Common::ViewMath& viewMath) {
  SIAAssert(m_area);

  if (m_gridView) {
    m_gridView->draw(viewMath);
  }

  m_area->setPosition(viewMath.windowPos());

  Size size = getContentSize();
  Vec2 backPos = viewMath.windowPos() * 0.1f;
  backPos.x += size.width * 0.5f;
  backPos.y += size.height * 0.5f;

  if (m_background) {
    m_background->setPosition(backPos);
  }
}

bool GameLayer::onTouchBegan(Touch* touch, Event* unused_event) {
  SIAAssert(m_area);
  this->touchBegan(m_area->convertTouchToNodeSpace(touch));
  return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event) {
  SIAAssert(m_area);
  this->touchMoved(m_area->convertTouchToNodeSpace(touch));
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event) {
  SIAAssert(m_area);
  this->touchEnded(m_area->convertTouchToNodeSpace(touch));
}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event) {
  SIAAssert(m_area);
  this->touchEnded(m_area->convertTouchToNodeSpace(touch));
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