#include "ModelMath.h"
#include "SIALogger.h"
SIASetModuleName(Model);

using namespace Common;

static const EntityPos buildTr[ModelMath::ePosIndexCount] = {
  EntityPos(0, 0.3),
  EntityPos(0.3, 0),
  EntityPos(0, -0.3),
  EntityPos(-0.3, 0),
  EntityPos(0, 0)
};

CellPos ModelMath::cell(EntityPos pos) {
  return CellPos((int)pos.x, (int)pos.y);
}

EntityPos ModelMath::center(CellPos pos) {
  return EntityPos((double)pos.x + 0.5, (double)pos.y + 0.5);
}

EntityPos ModelMath::buildPos(CellPos pos, PosIndex buildIndex) {
  SIAAssert(0 <= buildIndex && buildIndex <= ePosIndexCount);
  auto entPos = center(pos);
  entPos.x += buildTr[buildIndex].x;
  entPos.y += buildTr[buildIndex].y;
  
  return entPos;
}

ModelMath::PosIndex ModelMath::buildPos(EntityPos pos) {
  auto centerPos = center(cell(pos));
  auto tr = pos - centerPos;
 
  for (size_t i = 0; i < ePosIndexCount; i++) {
    if (abs(tr.x - buildTr[i].x) < 1.0e-3 && abs(tr.y - buildTr[i].y) < 1.0e-3) {
      return static_cast<PosIndex>(i);
    }
  }
  return eUndefined;
}

double ModelMath::distance(EntityPos p1, EntityPos p2) {
  SIAAssertMsg(false, "Distance function not implemented.");
  return 0;
}