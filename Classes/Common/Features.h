/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMMON_FEATURES_H__
#define _COMMON_FEATURES_H__

#include <unordered_map>
#include <vector>

namespace Common
{
  class Features {
  public:
    typedef size_t Cache;

    enum FeatureType {
      eFT_Undefined,
      eFT_Bool,
      eFT_Int,
      eFT_UInt,
      eFT_Float
    };

  public:

    FeatureType Type(std::string name);
    bool& Bool(std::string name);
    __int32& Int(std::string name);
    unsigned __int32& uInt(std::string name);
    float& Float(std::string name);

    FeatureType Type(Cache cache) const;
    bool& Bool(Cache cache) const;
    __int32& Int(Cache cache) const;
    unsigned __int32& uInt(Cache cache) const;
    float& Float(Cache cache) const;

    Cache cache(std::string name);

  private:
    union FeatureValue {
      void* undefined;
      bool b;
      __int32 i;
      unsigned __int32 ui;
      float f;
    };

    struct Feature {
      FeatureType type;
      FeatureValue v;
      Cache cache;

      Feature() : type(eFT_Undefined), cache(0) {
        v.undefined = nullptr;
      }
    };
    
    std::unordered_map<std::string, Feature> m_features;
    std::vector<Feature*> m_cache;
  };

};

#endif // _COMMON_FEATURES_H__
