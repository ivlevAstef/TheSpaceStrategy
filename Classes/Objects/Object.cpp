#include "Object.h"

#include "Models/Entity_Factory.h"
#include "Views/GameView.h"

#include "logger/SIAUtils_Logger.h"

using namespace Common;
using namespace Views;
using namespace Models;
using namespace Objects;

Object::Object(std::string objName, double x, double y) {
  m_pEntity = Entity::Factory::createBuildByName(objName);
  m_pEntity->setPos(x, y);

  m_pView = GameView::create(objName);

  m_pView->select += GameView::DSelect(this, [] (GameView* view) {
    SIA_LOG_DBG("Select %d", view);
  });
}

void Object::update(SceneInterfacePtr pScene) {
  if (m_pEntity.get() && m_pView) {
    ViewPos pos = pScene->viewMath().convert(m_pEntity->pos());
    m_pView->setPosition(pos);
  }
}

Object::~Object() {
}