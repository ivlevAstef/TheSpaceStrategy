#include "GameLayer.h"
#include "cocos2d.h"
#include "SIALogger.h"

SIASetModuleName(View);

using namespace Views;
using namespace Common;
USING_NS_CC;

static const int backgroundTag = 100;
static const int gameViewTag = 101;

bool GameLayer::init(Models::AreaPtr pArea) {
  SIACheckRetValue(!Layer::init(), false);

  m_pAreaModel = pArea;

  m_background = nullptr;
  m_touchesCount = 0;

  m_area = Layer::create();
  SIAFatalAssert(m_area);
  addChild(m_area, 1);

  m_pAreaNode = DrawNode::create();
  if (m_pAreaNode && m_pAreaModel) {
    addChild(m_pAreaNode);
  } else {
    SIAError("Can't create area node");
  }

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

  dispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
#else
  auto touchesListener = EventListenerTouchAllAtOnce::create();
  SIACheckRet(!touchesListener);
  
  touchesListener->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
  
  dispatcher->addEventListenerWithSceneGraphPriority(touchesListener, this);
#endif
}

void GameLayer::onExit() {
  Layer::onExit();
}

void GameLayer::draw(const Common::ViewMath& viewMath) {
  SIAAssert(m_area);

  if (m_pAreaNode) {
    SIAAssert(m_pAreaModel);

    EntityPos entityPoints[4] = {
      ModelMath::center(CellPos(0, 0)) + EntityPos(-M_SQRT1_2, -M_SQRT1_2),
      ModelMath::center(CellPos(m_pAreaModel->width(), 0)) + EntityPos(M_SQRT1_2, -M_SQRT1_2),
      ModelMath::center(CellPos(m_pAreaModel->width(), m_pAreaModel->height())) + EntityPos(M_SQRT1_2, M_SQRT1_2),
      ModelMath::center(CellPos(0, m_pAreaModel->height())) + EntityPos(-M_SQRT1_2, M_SQRT1_2)
    };

    ViewPos points[4] = {
      viewMath.convert(entityPoints[0]),
      viewMath.convert(entityPoints[1]),
      viewMath.convert(entityPoints[2]),
      viewMath.convert(entityPoints[3])
    };

    m_pAreaNode->clear();
    m_pAreaNode->drawPoly(points, 4, true, Color4F(0.6f, 0.8f, 0.9f, 1.0f));

    m_pAreaNode->setPosition(viewMath.windowPos());
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
  
  if (0 == m_touchesCount) {
    this->touchBegan(m_area->convertTouchToNodeSpace(touch));
    m_touchesCount++;
    return true;
  }
  
  this->touchEnded(m_area->convertTouchToNodeSpace(touch));
  return false;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event) {
  if (1 == m_touchesCount) {
    SIAAssert(m_area);
    this->touchMoved(m_area->convertTouchToNodeSpace(touch));
  }
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event) {
  m_touchesCount--;
  SIAAssert(m_area);
  this->touchEnded(m_area->convertTouchToNodeSpace(touch));
}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event) {
  m_touchesCount--;
  SIAAssert(m_area);
  this->touchEnded(m_area->convertTouchToNodeSpace(touch));
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
void GameLayer::onMouseDown(cocos2d::Event* event) {
  EventMouse* eMouse = static_cast<EventMouse*>(event);
  if (eMouse) {
    m_previousCursorLocation = eMouse->getLocationInView();
  }

  if (MOUSE_BUTTON_MIDDLE == eMouse->getMouseButton()) {
    auto locationInView = eMouse->getLocationInView();
    locationInView.y = -locationInView.y;//Bug into cocos
    auto location = Director::getInstance()->convertToGL(locationInView);

    erase(m_area->convertToNodeSpace(location));
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

#else

static Vec2 getCenter(cocos2d::Vec2 p1, cocos2d::Vec2 p2) {
  return p1 + (p2 - p1) * 0.5f;
}

void GameLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* unused_event) {
  if (2 == touches.size()) {
    auto prevloc = getCenter(touches[0]->getPreviousLocation(), touches[1]->getPreviousLocation());
    auto loc = getCenter(touches[0]->getLocation(), touches[1]->getLocation());
    move(loc - prevloc);
  }
}

#endif