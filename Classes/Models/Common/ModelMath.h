//
//File: ModelMath.h
//Description: Class with Math function for Model.
//Author: Ivlev Alexander. Stef
//Created: 27/06/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_MODEL_MATH_H__
#define _SIA_THE_SPACE_STRATEGY_MODEL_MATH_H__

#include "math/SIAUtils_Point2D.h"
#include <memory>

namespace Common
{
  typedef SIAUtils::Point2D<int> CellPos;
  typedef SIAUtils::Point2D<double> EntityPos;

  class ModelMath {
  public:
    enum PosIndex {
      ePosIndexBegin = 0,
      eTop = 0,
      eBottom = 1,
      eLeft = 2,
      eRight = 3,
      ePosIndexOnlyBuildCount = 4,
      eCenter = 4,
      ePosIndexCount = 5
    };

  public:
    static CellPos cell(EntityPos pos);

    static EntityPos center(CellPos pos);
    static EntityPos buildPos(CellPos pos, PosIndex buildIndex);

    static double distance(EntityPos p1, EntityPos p2);
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_MODEL_MATH_H__
