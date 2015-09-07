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

#include "SIAPoint2D.h"
#include <memory>

namespace Common
{
  typedef SIA::Point2D<int> CellPos;
  typedef SIA::Point2D<double> EntityPos;
  typedef SIA::Point2D<double> EntitySize;

  class ModelMath {
  public:
    static CellPos cell(EntityPos pos);

    static EntityPos center(CellPos pos);

    static double distance(EntityPos p1, EntityPos p2);
    static double distance2(EntityPos p1, EntityPos p2);
  };
};

#endif // _SIA_THE_SPACE_STRATEGY_MODEL_MATH_H__
