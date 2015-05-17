#include "GetterMineral.h"
#include "Components/View/GameView.h"
#include "Components/Data/Entity.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/FeatureNames.h"

using namespace Objects::Building;
using namespace Components::Data;
using namespace Components::View;
using namespace Common;

std::shared_ptr<GetterMineral> GetterMineral::create(int x, int y) {
  return std::make_shared<GetterMineral>(x, y);
}

GetterMineral::GetterMineral(int x, int y) {
  auto pView = GameView::create("GetterMineral");
  addComponent(pView);

  init();

  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);
  pEntity->setCell(x, y);

  pEntity->features().Int(FeatureNames::ID) = Entity::GetterMineral;
  pEntity->features().Int(FeatureNames::maxHP) = 50;
  pEntity->features().Int(FeatureNames::HP) = 50;
  pEntity->features().Bool(FeatureNames::generator) = false;
  pEntity->features().Bool(FeatureNames::physic) = true;
}

void GetterMineral::update() {
  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);

  auto pView = getComponent<GameView>();
  SIA_ASSERT(pView != nullptr);

  pView->setPosition(pEntity->pos().x, pEntity->pos().y);
}

void GetterMineral::init() {
  auto pView = getComponent<GameView>();
  SIA_ASSERT(pView != nullptr);

  pView->select += GameView::DSelect(this, [] (GameView* view) {
    SIA_LOG_DBG("Select %d", view);
  });
}