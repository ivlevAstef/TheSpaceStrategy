#include "Features.h"
#include "logger/SIAUtils_Logger.h"

using namespace Components::Data;

Features* Features::create() {
  COMPONENT_ALLOC(Features)();
  COMPONENT_INIT(Features);
}

Features::FeaturePtr& Features::get(const std::string& name) {
  FeaturePtr& feature = m_features[name];
  if (nullptr == feature.get()) {
    feature.reset(new Feature());
  }
  return feature;
}

Features::FeatureType Features::Type(std::string name) {
  return get(name)->type;
}
bool& Features::Bool(std::string name) {
  return get(name)->v.b;
}
__int32& Features::Int(std::string name) {
  return get(name)->v.i;
}
unsigned __int32& Features::uInt(std::string name) {
  return get(name)->v.ui;
}
float& Features::Float(std::string name) {
  return get(name)->v.f;
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

void Features::erase(std::string name) {
  FeaturePtr& feature = m_features[name];
  if (nullptr != feature.get()) {
    feature->type = eFT_Undefined;
    feature->v.undefined = nullptr;
  }
  m_features.erase(name);
}

Features::Cache Features::cache(std::string name) {
  std::shared_ptr<Feature> feature = get(name);
  if (0 == feature->cache) {
    m_cache.push_back(feature);
    feature->cache = m_cache.size();
  }
  return feature->cache;
}