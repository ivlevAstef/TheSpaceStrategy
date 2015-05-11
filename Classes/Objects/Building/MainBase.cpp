#include "MainBase.h"
#include "Components/View/GameView.h"
#include "Components/Data/Entity.h"
#include "logger/SIAUtils_Logger.h"

using namespace Objects::Building;
using namespace Components::Data;
using namespace Components::View;

std::shared_ptr<MainBase> MainBase::create(int x, int y) {
  return std::make_shared<MainBase>(x, y);
}

MainBase::MainBase(int x, int y) {
  m_features.Int("MAX HP") = 100;
  m_features.Int("HP") = 100;

  auto pView = GameView::create("MainBase");
  addComponent(pView);

  init();

  auto pEntity = getComponent<Entity>();
  SIA_ASSERT(pEntity != nullptr);
  pEntity->setCell(x, y);
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