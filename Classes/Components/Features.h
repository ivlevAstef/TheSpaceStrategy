/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _COMPONENTS_FEATURES_H__
#define _COMPONENTS_FEATURES_H__

#include <unordered_map>
#include <vector>

namespace Components
{
  class Features {
  public:
    enum FeatureType {
      eFT_Undefined,
      eFT_Int,
      eFT_UInt,
      eFT_Float
    };

  public:
    FeatureType Type(std::string name);
    __int32& Int(std::string name);
    unsigned __int32& uInt(std::string name);
    float& Float(std::string name);

    FeatureType Type(size_t cache);
    __int32& Int(size_t cache);
    unsigned __int32& uInt(size_t cache);
    float& Float(size_t cache);

    size_t Cache(std::string name);

  private:
    union FeatureValue {
      void* undefined;
      __int32 i;
      unsigned __int32 ui;
      float f;
    };

    struct Feature {
      FeatureType type;
      FeatureValue v;
      size_t cache;

      Feature() : type(eFT_Undefined), cache(0) {
        v.undefined = nullptr;
      }
    };
    
    std::unordered_map<std::string, Feature> m_features;
    std::vector<Feature*> m_cache;
  };

};

#endif // _COMPONENTS_FEATURES_H__
