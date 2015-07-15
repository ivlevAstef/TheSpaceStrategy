//
//File: SIAPoint2D.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:21 16/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_POINT2D_H__
#define _SIA_POINT2D_H__

namespace SIA
{
  template<typename Type>
  struct Point2D
  { 
  public:
    Point2D(Type x = 0, Type y = 0) :
      x(x), y(y)
    {

    }

    bool operator==(Point2D<Type> p2) {
      return x == p2.x && y == p2.y;
    }

  public:
    Type x;
    Type y;
  };


  typedef Point2D<int> Point2DInt;
  typedef Point2D<int> Position;
  typedef Point2D<float> RPosition;
  typedef Point2D<size_t> Size;
  typedef Point2D<double> Vector;
};

#endif // _SIA_POINT2D_H__
