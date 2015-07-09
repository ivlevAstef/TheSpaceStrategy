#include "Scene.h"
#include "Models/Entity.h"
#include "Views/GameView.h"
#include "Views/InterfaceView/BuildButtonLayer.h"
#include "SIALogger.h"
#include "Common/GameTouchEvents.h"

SIASetModuleName(Object);

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
  SIAFatalAssert(m_pArea.get());

  m_pGameLayer = GameLayer::create();
  SIAFatalAssert(m_pGameLayer);

  m_pGridView = GridView::create(m_pArea->grid());
  SIAFatalAssert(m_pGridView);

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

static TouchPos touchPos(cocos2d::Vec2 pos, ViewPos winPos) {
  auto tPos = pos + winPos;
  return TouchPos(tPos.x, tPos.y);
}

void Scene::touchBegan(cocos2d::Vec2 pos) {
  GameTouchEvents::touchBegan(touchPos(pos, m_viewMath.windowPos()));

  ViewPos centerPos = m_viewMath.center(pos);

  SIAAssert(!m_pButtonLayer);

  m_pButtonLayer = BuildButtonLayer::create(centerPos + m_viewMath.windowPos());
  SIAFatalAssert(m_pButtonLayer);

  m_pGameLayer->addChild(m_pButtonLayer, 100);

  m_pButtonLayer->pick += BuildButtonLayer::DPick(this, [this, centerPos] (std::string pickId) {
    SIAInfo("Pick build with name:%s.", pickId);
    auto newBuild = Object::create(pickId, m_viewMath.convert(centerPos));
    SIACheckRet(!newBuild.get());
    addObject(newBuild);
  });

  m_pButtonLayer->close += BuildButtonLayer::DClose(this, [this] (BuildButtonLayer* layer) {
    SIAAssert(layer);
    SIAAssert(m_pButtonLayer == layer);
    m_pButtonLayer = nullptr;
    m_pGameLayer->removeChild(layer);
  }, true);
}

void Scene::touchMoved(cocos2d::Vec2 pos) {
  GameTouchEvents::touchMoved(touchPos(pos, m_viewMath.windowPos()));
}
void Scene::touchEnded(cocos2d::Vec2 pos) {
  GameTouchEvents::touchEnded(touchPos(pos, m_viewMath.windowPos()));
}

void Scene::move(cocos2d::Vec2 moveDt) {
  m_viewMath.moveWindow(moveDt);
}

bool Scene::addObject(ObjectPtr pObject) {
  SIACheckRetValue(!pObject.get(), false);

  SIAAssert(m_pArea.get());
  SIAAssert(m_pGameLayer);

  auto pEntity = pObject->entity();
  SIAAssert(pEntity.get());
  SIACheckRetValue(!m_pArea->addEntity(pEntity), false);

  auto pView = pObject->view();
  SIAAssert(pView);
  m_pGameLayer->addGameView(pView);

  m_pObjects.push_back(pObject);

  SIADebug("Added object on scene.");
  return true;
}

void Scene::eraseObject(ObjectPtr pObject) {
  SIACheckRet(!pObject.get());

  SIAAssert(m_pArea.get());
  SIAAssert(m_pGameLayer);

  auto pEntity = pObject->entity();
  SIAAssert(pEntity.get());
  m_pArea->removeEntity(pEntity);

  auto pView = pObject->view();
  SIAAssert(pView);
  m_pGameLayer->eraseGameView(pView);

  m_pObjects.erase(std::remove_if(m_pObjects.begin(), m_pObjects.end(), [&pObject] (ObjectPtr& pObj) {
    return pObject.get() == pObj.get();
  }), m_pObjects.end());

  SIADebug("Removed object from scene.");
}

void Scene::update(SceneInterfacePtr pScene) {
  SIAAssert(pScene.get() == this);
  SIAAssert(m_pArea.get());
  SIAAssert(m_pGameLayer);

  m_viewMath.setWindowSize(m_pGameLayer->getContentSize());

  m_pArea->update();
  m_pGameLayer->update(m_viewMath);

  for (ObjectPtr pObject : m_pObjects) {
    SIAAssert(pObject.get());
    pObject->update(pScene);
  }
}