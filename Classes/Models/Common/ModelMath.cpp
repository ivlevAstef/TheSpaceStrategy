#include "ModelMath.h"

using namespace Common;

CellPos ModelMath::cell(EntityPos pos) {
  return CellPos((int)pos.x, (int)pos.y);
}

EntityPos ModelMath::center(CellPos pos) {
  return EntityPos((double)pos.x + 0.5, (double)pos.y + 0.5);
}

EntityPos ModelMath::buildPos(CellPos pos, PosIndex buildIndex) {
  static const EntityPos translated[ePosIndexOnlyBuildCount] = {
    EntityPos(0, 0.3),
    EntityPos(0.3, 0),
    EntityPos(0, -0.3),
    EntityPos(-0.3, 0)
  };

  auto entPos = center(pos);
  entPos.x += translated[buildIndex].x;
  entPos.y += translated[buildIndex].y;
  
  return entPos;
}

double ModelMath::distance(EntityPos p1, EntityPos p2) {
  return 0;
}