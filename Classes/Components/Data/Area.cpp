#include "Area.h"

using namespace Components::Data;

Area* Area::create() {
  return new Area();
}

void Area::addEntity(Entity* pEntity) {

}
void Area::removeEntity(Entity* pEntity) {

}

bool Area::convert(const int x, const int y, float& toX, float& toY) {
  return true;
}