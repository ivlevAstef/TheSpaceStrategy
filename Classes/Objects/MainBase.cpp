#include "MainBase.h"
#include "Components/View/GameView.h"

using namespace Objects;
using namespace Components::View;

std::shared_ptr<MainBase> MainBase::create() {
  return std::make_shared<MainBase>();
}

MainBase::MainBase() {
  m_features.Int("MAX HP") = 100;
  m_features.Int("HP") = 100;

  auto view = GameView::create("MainBase");
  view->setCell(4, 4);
  addComponent(view);
}