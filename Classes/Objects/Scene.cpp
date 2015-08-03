#include "Scene.h"
#include "Models/Entity.h"
#include "Views/GameView.h"
#include "Views/InterfaceView/BuildButtonLayer.h"
#include "SIALogger.h"
#include "Common/GameTouchEvents.h"

#include "Models/Commands/AddEntity.h"
#include "Models/Commands/EraseEntity.h"

SIASetModuleName(Object);

using namespace Objects;
using namespace Views;
using namespace Models;
using namespace Commands;
using namespace Common;

ScenePtr Scene::create(size_t width, size_t height) {
  return std::make_shared<Scene>(width, height);
}

Scene::Scene(size_t width, size_t height) {
  m_pButtonLayer = nullptr;

  m_modelController.setArea(std::make_shared<Area>(width, height));
  m_modelController.start();

  m_pGameLayer = GameLayer::create(m_modelController.area());
  SIAFatalAssert(m_pGameLayer);

  m_pGameLayer->setBackground("background");
  m_pGameLayer->modificationBackground(cocos2d::Color3B(150, 150, 200));

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

  SIAAssert(!m_pButtonLayer);

  m_pButtonLayer = BuildButtonLayer::create(pos + m_viewMath.windowPos());
  SIAFatalAssert(m_pButtonLayer);

  m_pGameLayer->addChild(m_pButtonLayer, 100);

  m_pButtonLayer->pick += BuildButtonLayer::DPick(this, [this, pos] (std::string pickId) {
    SIAInfo("Pick build with name:%s.", pickId.c_str());
    auto newBuild = Object::create(pickId, m_viewMath.convert(pos));
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

void Scene::addObject(ObjectPtr pObject) {
  SIACheckRet(!pObject.get());
  SIAAssert(m_pGameLayer);

  auto pEntity = pObject->entity();
  SIAAssert(pEntity);

  m_modelController.addCommand(std::make_shared<Commands::AddEntity>(pEntity), 
    [pObject, this] () {
      auto pView = pObject->view();
      SIAAssert(pView);
      m_pGameLayer->addGameView(pView);

      m_pObjects.push_back(pObject);

      SIADebug("Added object on scene.");
    }, nullptr);
}

void Scene::eraseObject(ObjectPtr pObject) {
  SIACheckRet(!pObject);
  SIAAssert(m_pGameLayer);

  auto pEntity = pObject->entity();
  SIAAssert(pEntity);

  m_modelController.addCommand(std::make_shared<Commands::EraseEntity>(pEntity),
    [pObject, this] () {
    auto pView = pObject->view();
    SIAAssert(pView);
    m_pGameLayer->eraseGameView(pView);

    m_pObjects.erase(std::remove_if(m_pObjects.begin(), m_pObjects.end(), [&pObject] (ObjectPtr& pObj) {
      return pObject.get() == pObj.get();
    }), m_pObjects.end());

    SIADebug("Removed object from scene.");
  }, nullptr);
}

void Scene::draw(SceneInterfacePtr pScene, double dt) {
  m_modelController.callCommandsCallback();

  SIAAssert(pScene.get() == this);
  SIAAssert(m_pGameLayer);

  m_viewMath.setWindowSize(m_pGameLayer->getContentSize());

  m_pGameLayer->draw(m_viewMath);

  for (ObjectPtr pObject : m_pObjects) {
    SIAAssert(pObject.get());
    pObject->draw(pScene);
  }
}