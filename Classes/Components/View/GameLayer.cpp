#include "GameLayer.h"
#include "cocos2d.h"
#include "logger/SIAUtils_Logger.h"

using namespace Components::View;
USING_NS_CC;

static const int backgroundTag = 100;
static const int gameViewTag = 101;
static const int gridViewTag = 102;

GameLayer* GameLayer::create() {
  COMPONENT_ALLOC(GameLayer)();
  COMPONENT_INIT(GameLayer);
}

GameLayer::GameLayer() {
  SIA_CHECK_RET(!init(), ERR);
  
  m_background = nullptr;

  m_area = AreaLayer::create();
  addChild(m_area, 1);
}

void GameLayer::setGridView(size_t width, size_t height, size_t cellSize) {
  SIA_ASSERT(m_area);

  Size size = Director::getInstance()->getWinSize();
  m_grid = GridView::create(width, height, cellSize);
  m_grid->setContentSize(size);

  m_area->addChild(m_grid);

  m_area->setContentSize(Size(width*cellSize, height*cellSize));
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

static double normalizeNumber(double n, double size, double step) {
  if (n < -step + size) {
    n += step * ((int)(-n / step));
  }
  if (n > size) {
    n -= step * (1 + (int)(n / step));
  }
  return n;
}

static Vec2 normalizeVec(Vec2 vec, Size size, Size step) {
  vec.x = normalizeNumber(vec.x, size.width, step.width);
  vec.y = normalizeNumber(vec.y, size.height, step.height);
  return vec;
}

bool GameLayer::createData(cocos2d::Touch* touch, Common::GameTouchData& data) {
  Vec2 pos = convertTouchToNodeSpace(touch);

  size_t x = 0;
  size_t y = 0;
  if (m_grid->convert(touch, x, y)) {
    Vec2 center = convertToNodeSpace(m_grid->getCenter(x, y));

    pos = normalizeVec(pos, getContentSize(), m_area->getContentSize());
    center = normalizeVec(center, getContentSize(), m_area->getContentSize());
    data = {pos, center, x, y};
    return true;
  }
  return false;
}

//TODO:create utils
void GameLayer::move(cocos2d::Vec2 move) {
  SIA_LOG_INFO("Move on (%f,%f)", move.x, move.y);
  cocos2d::Vec2 newPos = m_area->getPosition() + move;

  newPos = normalizeVec(newPos, getContentSize(), m_area->getContentSize());

  m_area->setPosition(newPos);
  m_grid->setPosition(-newPos);

  ///TODO: create normal cycling background
  Vec2 backPos = m_background->getPosition();
  backPos += move * 0.1f;
  //backPos.x = normalizeNumber(backPos.x, 0, m_background->getContentSize().width);
  //backPos.y = normalizeNumber(backPos.y, 0, m_background->getContentSize().height);
  m_background->setPosition(backPos);
}

bool GameLayer::onTouchBegan(Touch* touch, Event* unused_event) {
  Common::GameTouchData data;
  if (createData(touch, data)) {
    Common::GameTouchEvents::touchBegan(data);
    return true;
  }
  return false;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event) {
  Common::GameTouchData data;
  if (createData(touch, data)) {
    Common::GameTouchEvents::touchMoved(data);
  }
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event) {
  Common::GameTouchData data;
  if (createData(touch, data)) {
    Common::GameTouchEvents::touchEnded(data);
  }
}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event) {
  Common::GameTouchData data;
  if (createData(touch, data)) {
    Common::GameTouchEvents::touchEnded(data);
  }
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

/////////////////////////////////////////////////////////////////////
static inline float getPair(float coordinate, float size) {
  return coordinate < size*0.5 ? coordinate + size : coordinate - size;
}

GameLayer::AreaLayer* GameLayer::AreaLayer::create() {
  AreaLayer* area = new (std::nothrow)AreaLayer();
  if (area) {
    area->autorelease();
    return area;
  }

  SIA_LOG_ERR("can't create areaLayer");
  CC_SAFE_DELETE(area);
  return nullptr;
}


void GameLayer::AreaLayer::visitGameView(Node* node, Renderer* renderer, const Mat4 &transform, uint32_t flags) {
  SIA_ASSERT(node);

  Vec2 pos = node->getPosition();
  Vec2 pairPos = Vec2(getPair(pos.x, getContentSize().width), getPair(pos.y, getContentSize().height));

  node->visit(renderer, transform, flags);

  node->setPosition(pairPos.x, pos.y);
  node->visit(renderer, transform, flags);

  node->setPosition(pos.x, pairPos.y);
  node->visit(renderer, transform, flags);

  node->setPosition(pairPos.x, pairPos.y);
  node->visit(renderer, transform, flags);

  node->setPosition(pos);
}

void GameLayer::AreaLayer::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags) {
  if (!_visible) {
    return;
  }

  uint32_t flags = processParentFlags(parentTransform, parentFlags);

  _director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
  _director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

  if (!_children.empty()) {
    sortAllChildren();

    for (int i = 0; i < _children.size(); i++) {
      auto node = _children.at(i);
      if (node) {
        if (node->getTag() == gameViewTag) {
          visitGameView(node, renderer, _modelViewTransform, flags);
        } else {
          node->visit(renderer, _modelViewTransform, flags);
        }
      }
    }
  }

  _director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}