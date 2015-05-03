#include "Entity.h"

using namespace Components::Data;

Entity* Entity::create() {
  return new Entity();
}