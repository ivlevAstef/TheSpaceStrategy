#include "MainBase.h"
#include "Components/View/GameView.h"
#include "Components/Data/Entity.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/FeatureNames.h"

using namespace Objects::Building;
using namespace Components::Data;
using namespace Components::View;
using namespace Common;

std::shared_ptr<MainBase> MainBase::create(int x, int y) {
  return std::make_shared<MainBase>(x, y);
}

MainBase::MainBase(int x, int y) {
  auto pView = GameView::create("MainBase");
  addComponent(pView);

  init();

  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);
  pEntity->setCell(x, y);

  pEntity->features()[FeatureNames::ID] = Entity::MainBase;
  pEntity->features()[FeatureNames::maxHP] = 100;
  pEntity->features()[FeatureNames::HP] = 100;
  pEntity->features()[FeatureNames::generator] = true;
  pEntity->features()[FeatureNames::generatedEnergy] = 25;
  pEntity->features()[FeatureNames::physic] = true;
}

void MainBase::update() {
  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);

  auto pView = getComponent<GameView>();
  SIA_ASSERT(pView != nullptr);

  pView->setPosition(pEntity->pos().x, pEntity->pos().y);
}

void MainBase::init() {
  auto pView = getComponent<GameView>();
  SIA_ASSERT(pView != nullptr);

  pView->select += GameView::DSelect(this, [] (GameView* view) {
    SIA_LOG_DBG("Select %d", view);
  });
}