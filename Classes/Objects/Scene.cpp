#include "Scene.h"
#include "Models/Entity.h"
#include "Views/GameView.h"
#include "Views/InterfaceView/BuildButtonLayer.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/GameTouchEvents.h"

using namespace Objects;
using namespace Views;
using namespace Models;
using namespace Common;

ScenePtr Scene::create(size_t width, size_t height) {
  return std::make_shared<Scene>(width, height);
}

Scene::Scene(size_t width, size_t height) {
  m_pButtonLayer = nullptr;

  m_pArea = std::make_shared<Area>(width, height);
  SIA_ASSERT(m_pArea);

  m_pGameLayer = GameLayer::create();
  SIA_ASSERT(m_pGameLayer);

  m_pGridView = GridView::create(width, height);
  SIA_ASSERT(m_pGridView);

  m_pGameLayer->setBackground("background");
  m_pGameLayer->modificationBackground(cocos2d::Color3B(150, 150, 200));
  m_pGameLayer->setGridView(m_pGridView);

  using std::placeholders::_1;
  m_pGameLayer->touchBegan += GameLayer::DTouchBegan(this, std::bind(&Scene::touchBegan, this, _1));
  m_pGameLayer->touchMoved += GameLayer::DTouchMoved(this, std::bind(&Scene::touchMoved, this, _1));
  m_pGameLayer->touchEnded += GameLayer::DTouchEnded(this, std::bind(&Scene::touchEnded, this, _1));
  m_pGameLayer->move += GameLayer::DMove(this, std::bind(&Scene::move, this, _1));
}

Scene::~Scene() {
}

void Scene::touchBegan(cocos2d::Touch* touch) {
  cocos2d::Vec2 pos = m_pGameLayer->convertTouchToNodeSpace(touch);
  GameTouchEvents::touchBegan(TouchPos(pos.x, pos.y));

  ViewPos centerPos = m_viewMath.center(pos);

  /*if (!m_circularMath.activeZone(data.x, data.y)) {
    return;
  }*/

  SIA_ASSERT(nullptr == m_pButtonLayer);

  m_pButtonLayer = BuildButtonLayer::create(centerPos); 
  SIA_ASSERT(m_pButtonLayer);

  m_pGameLayer->addChild(m_pButtonLayer, 100);

   m_pButtonLayer->pick += BuildButtonLayer::DPick(this, [this, centerPos] (std::string pickId) {
    SIA_LOG_INFO("PICK pickID");
    auto newBuild = Object::create(pickId, centerPos.x, centerPos.y);
    SIA_CHECK_RET(nullptr == newBuild.get(), WRN);
    addObject(newBuild);
  });

  m_pButtonLayer->close += BuildButtonLayer::DClose(this, [this] (BuildButtonLayer* layer) {
    SIA_ASSERT(layer);
    m_pButtonLayer = nullptr;
    m_pGameLayer->removeChild(layer);
  }, true);
}

void Scene::touchMoved(cocos2d::Touch* touch) {
  cocos2d::Vec2 pos = m_pGameLayer->convertTouchToNodeSpace(touch);
  GameTouchEvents::touchMoved(TouchPos(pos.x, pos.y));
}
void Scene::touchEnded(cocos2d::Touch* touch) {
  cocos2d::Vec2 pos = m_pGameLayer->convertTouchToNodeSpace(touch);
  GameTouchEvents::touchEnded(TouchPos(pos.x, pos.y));
}

void Scene::move(cocos2d::Vec2 moveDt) {
  m_viewMath.moveWindow(moveDt);
}

bool Scene::addObject(ObjectPtr pObject) {
  SIA_CHECK_ZERO(pObject.get() == nullptr, WRN);

  auto pEntity = pObject->entity();
  if (m_pArea.get() && pEntity.get()) {
    SIA_CHECK_ZERO(!m_pArea->addEntity(pEntity), DBG);
  }

  m_pObjects.push_back(pObject);
  auto pView = pObject->view();
  if (m_pGameLayer && pView) {
    m_pGameLayer->addGameView(pView);
  }

  SIA_LOG_DBG("Added object on scene.");
  return true;
}

void Scene::eraseObject(ObjectPtr pObject) {
  SIA_CHECK_RET(pObject.get() == nullptr, WRN);

  auto pEntity = pObject->entity();
  if (m_pArea.get() && pEntity.get()) {
    m_pArea->removeEntity(pEntity);
  }

  auto pView = pObject->view();
  if (m_pGameLayer && pView) {
    m_pGameLayer->eraseGameView(pView);
  }

  m_pObjects.erase(std::remove_if(m_pObjects.begin(), m_pObjects.end(), [&pObject] (ObjectPtr& pObj) {
    return pObject.get() == pObj.get();
  }), m_pObjects.end());

  SIA_LOG_DBG("Removed object from scene.");
}

void Scene::update(SceneInterfacePtr pScene) {
  SIA_ASSERT(pScene.get() == this);

  m_pArea->update();
  m_pGameLayer->update(m_viewMath);

  for (ObjectPtr pObject : m_pObjects) {
    pObject->update(pScene);
  }
}