#include "Build.h"
#include "Components/Data/Entity.h"

using namespace Objects::Building;

Build::Build() {
  addComponent(Components::Data::Entity::create());
}

Build::~Build() {
  auto pEntity = getComponent<Components::Data::Entity>();
  if (pEntity) {
    eraseComponent(pEntity);
    Components::Data::Entity::free(pEntity);
  }
}