#include "Features.h"
#include "logger/SIAUtils_Logger.h"

using namespace Components;

Features::FeatureType Features::Type(std::string name) {
  return m_features[name].type;
}
__int32& Features::Int(std::string name) {
  return m_features[name].v.i;
}
unsigned __int32& Features::uInt(std::string name) {
  return m_features[name].v.ui;
}
float& Features::Float(std::string name) {
  return m_features[name].v.f;
}

Features::FeatureType Features::Type(size_t cache) {
  SIA_ASSERT(cache == 0);
  return m_cache[cache - 1]->type;
}
__int32& Features::Int(size_t cache) {
  SIA_ASSERT(cache == 0);
  return m_cache[cache - 1]->v.i;
}
unsigned __int32& Features::uInt(size_t cache) {
  SIA_ASSERT(cache == 0);
  return m_cache[cache - 1]->v.ui;
}
float& Features::Float(size_t cache) {
  SIA_ASSERT(cache == 0);
  return m_cache[cache - 1]->v.f;
}

size_t Features::Cache(std::string name) {
  Feature& feature = m_features[name];
  if (0 == feature.cache) {
    m_cache.push_back(&feature);
    feature.cache =  m_cache.size();
  }
  return feature.cache;
}