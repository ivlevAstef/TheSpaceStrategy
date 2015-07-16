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
  struct Point2D {
  public:
    Point2D() : x(0), y(0) {

    }
    Point2D(Type xx, Type yy) {
      set(xx, yy);
    }
    Point2D(const Type* array) {
      set(array);
    }

    Point2D(const Point2D<Type>& copy) {
      set(copy);
    }

    void negative() {
      x = -x;
      y = -y;
    }

    void scale(Type scalar) {
      x *= scalar;
      y *= scalar;
    }
    void scale(const Point2D<Type>& scale) {
      x *= scale.x;
      y *= scale.y;
    }

    void set(Type xx, Type yy) {
      x = xx;
      y = yy;
    }
    void set(const Type* array) {
      x = array[0];
      y = array[1];
    }
    void set(const Point2D<Type>& v) {
      x = v.x;
      y = v.y;
    }

    inline const Point2D<Type> operator+(const Point2D<Type>& v) const {
      return Point<Type>(x + v.x, y + v.y);
    }
    inline Point2D<Type>& operator+=(const Point2D<Type>& v) {
      x += v.x;
      y += v.y;
      return *this;
    }

    inline const Point2D<Type> operator-(const Point2D<Type>& v) const {
      return Point2D<Type>(x - v.x, y - v.y);
    }
    inline Point2D<Type>& operator-=(const Point2D<Type>& v) {
      x -= v.x;
      y -= v.y;
      return *this;
    }

    inline const Point2D<Type> operator-() const {
      return Point<Type>(-x, -y);
    }

    inline const Point2D<Type> operator*(Type s) const {
      return Point<Type>(x * s, y * s);
    }
    inline Point2D<Type>& operator*=(Type s) {
      x *= s;
      y *= s;
      return *this;
    }

    inline const Point2D<Type> operator/(Type s) const {
      return Point<Type>(x / s, y / s);
    }

    inline bool operator<(const Point2D<Type>& v) const {
      return x < v.x && y < v.y;
    }
    inline bool operator>(const Point2D<Type>& v) const {
      return x > v.x && y > v.y;
    }
    inline bool operator==(const Point2D<Type>& v) const {
      return x == v.x && y == v.y;
    }
    inline bool operator!=(const Point2D<Type>& v) const {
      return !(*this == v);
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
