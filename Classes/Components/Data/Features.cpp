#include "Features.h"
#include "logger/SIAUtils_Logger.h"

using namespace Components::Data;

Features* Features::create() {
  COMPONENT_ALLOC(Features)();
  COMPONENT_INIT(Features);
}

Features::FeatureType Features::Type(std::string name) {
  return m_features[name].type;
}
bool& Features::Bool(std::string name) {
  return m_features[name].v.b;
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

Features::FeatureType Features::Type(Cache cache) const {
  SIA_ASSERT(cache);
  return m_cache[cache - 1]->type;
}
bool& Features::Bool(Cache cache) const {
  SIA_ASSERT(cache);
  return m_cache[cache - 1]->v.b;
}
__int32& Features::Int(Cache cache) const {
  SIA_ASSERT(cache);
  return m_cache[cache - 1]->v.i;
}
unsigned __int32& Features::uInt(Cache cache) const {
  SIA_ASSERT(cache);
  return m_cache[cache - 1]->v.ui;
}
float& Features::Float(Cache cache) const {
  SIA_ASSERT(cache);
  return m_cache[cache - 1]->v.f;
}

Features::Cache Features::cache(std::string name) {
  Feature& feature = m_features[name];
  if (0 == feature.cache) {
    m_cache.push_back(&feature);
    feature.cache = m_cache.size();
  }
  return feature.cache;
}