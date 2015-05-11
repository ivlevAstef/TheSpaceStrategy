#include "GameLayer.h"
#include "cocos2d.h"
#include "logger/SIAUtils_Logger.h"

using namespace Components::View;
USING_NS_CC;

static const int backgroundTag = 100;
static const int gameViewTag = 101;
static const int gridViewTag = 102;

GameLayer* GameLayer::create() {
  GameLayer* view = new (std::nothrow)GameLayer();
  if (view) {
    view->autorelease();
    return view;
  }

  SIA_LOG_ERR("can't create gameLayer");
  CC_SAFE_DELETE(view);
  return nullptr;
}

GameLayer::GameLayer() {
  SIA_CHECK_RET(!init(), ERR);
  
  m_background = nullptr;

  m_area = Layer::create();
  addChild(m_area, 1);
}

void GameLayer::setGridView(size_t width, size_t height, size_t cellSize) {
  SIA_ASSERT(m_area);

  Size size = getContentSize();
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
}
void GameLayer::onExit() {
  Layer::onExit();
}

bool GameLayer::createData(cocos2d::Touch* touch, Common::GameTouchData& data) {
  Vec2 pos = convertTouchToNodeSpace(touch);

  size_t x = 0;
  size_t y = 0;
  if (m_grid->convert(touch, x, y)) {
    Vec2 center = convertToNodeSpace(m_grid->getCenter(x, y));

    data = {pos, center, x, y};
    return true;
  }
  return false;
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