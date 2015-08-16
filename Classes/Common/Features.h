/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_FEATURES_H__
#define _SIA_THE_SPACE_STRATEGY_FEATURES_H__

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace Common
{
  class Feature {
  public:
    struct Point {
    float x;
    float y;
    };

    static const bool UndefinedBool;
    static const signed char UndefinedChar;
    static const unsigned char UndefinedUChar;
    static const int UndefinedInt;
    static const unsigned int UndefinedUInt;
    static const float UndefinedFloat;
    static const double UndefinedDouble;
    static const Point UndefinedPoint;

    enum FeatureType {
    eFT_Undefined,
    eFT_Bool,
    eFT_Char,
    eFT_UChar,
    eFT_Int32,
    eFT_UInt32,
    eFT_Float,
    eFT_Double,
    eFT_Point
    };

  public:
    Feature();

    operator FeatureType() const;
      
    operator bool() const;
    operator signed char() const;
    operator unsigned char() const;
    operator int() const;
    operator unsigned int() const;
    operator float() const;
    operator double() const;
    operator Point() const;

    Feature& operator=(bool value);
    Feature& operator=(signed char value);
    Feature& operator=(unsigned char value);
    Feature& operator=(int value);
    Feature& operator=(unsigned int value);
    Feature& operator=(float value);
    Feature& operator=(double value);
    Feature& operator=(Point value);

  private:
    union FeatureValue {
    void* undefined;
    bool b;
    signed char c;
    unsigned char uc;
    int i;
    unsigned int ui;
    float f;
    double d;
    Point p;
    };

    FeatureType m_type;
    FeatureValue m_value;
  };


  class Features;
  typedef std::shared_ptr<Features> FeaturesPtr;

  class Features {
  public:
    typedef size_t Cache;
  public:

    static FeaturesPtr create();

    bool is(std::string name) const;

    Feature& operator[](std::string name) const;///unsafe used only with 'is'

    Feature& operator[](std::string name);
    Feature& operator[](Cache cache) const;

    Cache cache(std::string name);

    void erase(std::string name);

  private:
    typedef std::shared_ptr<Feature> FeaturePtr;

    FeaturePtr& get(const std::string& name);

    std::unordered_map<std::string, FeaturePtr> m_features;
    std::vector<FeaturePtr> m_cache;
  };

};

#endif // _SIA_THE_SPACE_STRATEGY_FEATURES_H__
