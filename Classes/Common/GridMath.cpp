#include "GridMath.h"
#include "logger/SIAUtils_Logger.h"
#include <cmath>

using namespace Common;
USING_NS_CC;

#ifdef USE_6_MODEL
#define SQRT3 1.732050807568877
#endif

const double GridMath::GridCellSize = 100;

SIAUtils::Position GridMath::cellPos(cocos2d::Vec2 pos) {
#if defined(USE_4_MODEL) || defined(USE_8_MODEL)
  return SIAUtils::Position(pos.x / GridCellSize,
                            pos.y / GridCellSize);
#elif defined(USE_6_MODEL)
  double x = (pos.x + pos.y*SQRT3) / (SQRT3 * GridCellSize);
  double y = (pos.y*SQRT3 - pos.x) / (SQRT3 * GridCellSize);

  int xZero = x;
  int yZero = y;
  double xN = x - (double)xZero;
  double yN = y - (double)yZero;

  bool xSmall = xN < 0.5;
  bool ySmall = yN < 0.5;

  if (!(xSmall ^ ySmall)) {///(x > 0.5 y > 0.5) or ( x < 0.5 y < 0.5)
    return SIAUtils::Position(xZero + !xSmall, yZero + !ySmall);
  }

  ///x > 0.5 y < 0.5
  if (!xSmall && ySmall) {
    size_t xT = (1 + yN < 2.0 * xN) ? 1 : 0;
    size_t yT = (xN < 2.0 * yN) ? 1 : 0;
    if (0 == xT && 1 == yT) {
      xT = yT = (xN < 1.0 - yN) ? 0 : 1;
    }

    return SIAUtils::Position(xZero + xT, yZero + yT);
  } else { ///y > 0.5 x < 0.5
    size_t xT = (yN < 2.0 * xN) ? 1 : 0;
    size_t yT = (1 + xN < 2.0 * yN) ? 1 : 0;
    if (0 == yT && 1 == xT) {
      xT = yT = (yN < 1.0 - xN) ? 0 : 1;
    }

    return SIAUtils::Position(xZero + xT, yZero + yT);
  }
#else
#error Defined Model Type
#endif
}


cocos2d::Vec2 GridMath::center(size_t x, size_t y) {
#if defined(USE_4_MODEL) || defined(USE_8_MODEL)
  return Vec2(x * GridCellSize + GridCellSize*0.5, 
              y * GridCellSize + GridCellSize*0.5);
#elif defined(USE_6_MODEL)
  return Vec2(GridCellSize*SQRT3*0.5 * ((int)x - (int)y),
              GridCellSize*0.5 * (x + y));
#else
#error Defined Model Type
#endif
}

cocos2d::Vec2 GridMath::build(size_t x, size_t y, size_t index) {
  SIA_ASSERT(index < MaxCellBuilds);
#if defined(USE_4_MODEL) || defined(USE_8_MODEL)
  static const Vec2 translated[MaxCellBuilds] = {
    Vec2(0, GridCellSize*0.3f),
    Vec2(GridCellSize*0.3f, 0),
    Vec2(0, GridCellSize*-0.3f),
    Vec2(GridCellSize*-0.3f, 0)
  };

  return center(x, y) + translated[index];
#elif defined(USE_6_MODEL)
#define SQRT5 2.23606797749979
  static const Vec2 translated[MaxCellBuilds] = {
    Vec2(0, GridCellSize / 4.0),
    Vec2(GridCellSize*SQRT5 / 8.0, -GridCellSize / 8.0),
    Vec2(-GridCellSize*SQRT5 / 8.0, -GridCellSize / 8.0),
    
  };

  return center(x, y) + translated[index];
#else
#error Defined Model Type
#endif
}


std::vector<cocos2d::Vec2> GridMath::cellView(size_t x, size_t y, cocos2d::Vec2 translate) {
  double cellHalfSize = GridCellSize * 0.5;
#ifdef USE_4_MODEL
  static const size_t viewCount = 4;
  static const Vec2 cellPos[viewCount] = {
    Vec2(-cellHalfSize,-cellHalfSize),
    Vec2( cellHalfSize,-cellHalfSize),
    Vec2( cellHalfSize, cellHalfSize),
    Vec2(-cellHalfSize, cellHalfSize)
  };
#elif defined(USE_8_MODEL)
#define SQRT2 1.414213562373095
  static const size_t viewCount = 8;
  double octaEdge = GridCellSize / (SQRT2 + 1.0);
  double octaB = GridCellSize / (SQRT2 + 2.0);

  static const Vec2 cellPos[viewCount] = {
    Vec2(-cellHalfSize, octaB - cellHalfSize),
    Vec2(-cellHalfSize, octaB + octaEdge - cellHalfSize),
    Vec2(octaB - cellHalfSize, cellHalfSize),
    Vec2(octaB + octaEdge - cellHalfSize, cellHalfSize),
    Vec2(cellHalfSize, octaB + octaEdge - cellHalfSize),
    Vec2(cellHalfSize, octaB - cellHalfSize),
    Vec2(octaB + octaEdge - cellHalfSize, -cellHalfSize),
    Vec2(octaB - cellHalfSize, -cellHalfSize)
  };

#elif defined(USE_6_MODEL)
  static const size_t viewCount = 6;
  static const Vec2 cellPos[viewCount] = {
    Vec2(-cellHalfSize / SQRT3, -cellHalfSize),
    Vec2(-GridCellSize / SQRT3, 0),
    Vec2(-cellHalfSize / SQRT3, cellHalfSize),
    Vec2(cellHalfSize / SQRT3, cellHalfSize),
    Vec2(GridCellSize / SQRT3, 0),
    Vec2(cellHalfSize / SQRT3, -cellHalfSize),
    
  };
#else
#error Defined Model Type
#endif

  std::vector<cocos2d::Vec2> res;
  res.resize(viewCount);
  Vec2 center = GridMath::center(x, y);
  for (size_t i = 0; i < viewCount; i++) {
    res[i] = center + cellPos[i] + translate;
  }

  return res;
}

const std::vector<SIAUtils::Position>& GridMath::neighborhood() {
#if defined(USE_4_MODEL) || defined(USE_8_MODEL)
  static const std::vector<SIAUtils::Position> res = {
    SIAUtils::Position(-1, 0),
    SIAUtils::Position(1 , 0),
    SIAUtils::Position(0 , 1),
    SIAUtils::Position(0 ,-1)
  };
  return res;
#elif defined(USE_6_MODEL)
  static const std::vector<SIAUtils::Position> res = {
    SIAUtils::Position(-1, 0),
    SIAUtils::Position(1 , 0),
    SIAUtils::Position(0 , 1),
    SIAUtils::Position(0 ,-1),
    SIAUtils::Position(-1,-1),
    SIAUtils::Position(1 , 1)
  };
  return res;
#else
#error Defined Model Type
#endif
}
std::vector<SIAUtils::Position> GridMath::neighborhood(size_t x, size_t y) {
  const std::vector<SIAUtils::Position>& neighborhood = GridMath::neighborhood();
  std::vector<SIAUtils::Position> res;
  res.resize(neighborhood.size());
  for (size_t i = 0; i < neighborhood.size(); i++) {
    res[i].x = x + neighborhood[i].x;
    res[i].y = y + neighborhood[i].y;
  }
  return res;
}