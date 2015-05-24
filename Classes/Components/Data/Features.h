/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_DATA_FEATURES_H__
#define _COMPONENTS_DATA_FEATURES_H__

#include "../Component.h"
#include <unordered_map>
#include <vector>
#include <memory>

namespace Components
{
  namespace Data
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
      static const __int32 UndefinedInt;
      static const unsigned __int32 UndefinedUInt;
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
      operator __int32() const;
      operator unsigned __int32() const;
      operator float() const;
      operator double() const;
      operator Point() const;

      Feature& operator=(bool value);
      Feature& operator=(signed char value);
      Feature& operator=(unsigned char value);
      Feature& operator=(__int32 value);
      Feature& operator=(unsigned __int32 value);
      Feature& operator=(float value);
      Feature& operator=(double value);
      Feature& operator=(Point value);

    private:
      union FeatureValue {
        void* undefined;
        bool b;
        signed char c;
        unsigned char uc;
        __int32 i;
        unsigned __int32 ui;
        float f;
        double d;
        Point p;
      };

      FeatureType m_type;
      FeatureValue m_value;
    };

    class Features: public ComponentRef {
    public:
      typedef size_t Cache;
    public:
      DEFINE_COMPONENT(Features);

      static Features* create();

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
};

#endif // _COMPONENTS_DATA_FEATURES_H__
