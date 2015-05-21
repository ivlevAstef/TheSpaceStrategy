#include "Build.h"
#include "Components/Data/Entity.h"
#include "Components/Data/Features.h"

using namespace Objects::Building;
using namespace Components::Data;

Build::Build() {
  addComponent(Features::create());
  auto features = getComponent<Features>();

  if (features) {
    addComponent(Entity::create(features));
  }
}

Build::~Build() {
}