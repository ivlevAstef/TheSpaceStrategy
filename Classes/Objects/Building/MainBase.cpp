#include "MainBase.h"
#include "Components/View/GameView.h"
#include "Components/Data/Entity.h"
#include "Components/Data/Modificator/EnergyGenerator.h"
#include "logger/SIAUtils_Logger.h"
#include "Common/FeatureNames.h"

using namespace Objects::Building;
using namespace Components::Data;
using namespace Components::View;
using namespace Common;

std::shared_ptr<MainBase> MainBase::create(size_t x, size_t y) {
  return std::make_shared<MainBase>(x, y);
}

MainBase::MainBase(size_t x, size_t y) {
  auto pView = GameView::create("MainBase");
  addComponent(pView);

  init();

  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);
  pEntity->setCellPos(x, y);

  auto pFeatures = getComponent<Features>();
  SIA_ASSERT(pFeatures != nullptr);
  auto features = *pFeatures;

  features[FeatureNames::ID] = Entity::MainBase;
  features[FeatureNames::maxHP] = 100;
  features[FeatureNames::HP] = 100;
  features[FeatureNames::physic] = true;

  addComponent(Modificator::EnergyGenerator::create(pFeatures, 25));
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