#include "Features.h"
#include "logger/SIAUtils_Logger.h"
#include <cfloat>

using namespace Components::Data;

const bool Feature::UndefinedBool = false;
const signed char Feature::UndefinedChar = SCHAR_MAX;
const unsigned char Feature::UndefinedUChar = UCHAR_MAX;
const __int32 Feature::UndefinedInt = INT32_MAX;
const unsigned __int32 Feature::UndefinedUInt = UINT32_MAX;
const float Feature::UndefinedFloat = FLT_MAX;
const double Feature::UndefinedDouble = DBL_MAX;

#define GET_VALUE(TYPE, UNDEFINED) \
switch (m_type) { \
  case eFT_Bool: return (TYPE)m_value.b; \
  case eFT_Char: return (TYPE)m_value.c; \
  case eFT_UChar: return (TYPE)m_value.uc; \
  case eFT_Int32: return (TYPE)m_value.i; \
  case eFT_UInt32: return (TYPE)m_value.ui; \
  case eFT_Float: return (TYPE)m_value.f; \
  case eFT_Double: return (TYPE)m_value.d; \
  default: return (TYPE)UNDEFINED; \
}

#define SET_VALUE(TYPE, POSTFIX) \
  m_type = TYPE; \
  m_value.POSTFIX = value; \
  return *this;

Feature::Feature() {
  m_type = eFT_Undefined;
  m_value.undefined = nullptr;
}

Feature::operator FeatureType() const {
  return m_type;
}

Feature::operator bool() const {
  switch (m_type) {
    case eFT_Bool: return m_value.b;
    case eFT_Char: return m_value.c != 0;
    case eFT_UChar: return m_value.uc != 0;
    case eFT_Int32: return m_value.i != 0;
    case eFT_UInt32: return m_value.ui != 0;
    case eFT_Float: return m_value.f != 0;
    case eFT_Double: return m_value.d != 0;
    default: return UndefinedBool;
  }
}
Feature::operator signed char() const {
  GET_VALUE(signed char, UndefinedChar);
}
Feature::operator unsigned char() const {
  GET_VALUE(unsigned char, UndefinedUChar);
}
Feature::operator __int32() const {
  GET_VALUE(__int32, UndefinedInt);
}
Feature::operator unsigned __int32() const {
  GET_VALUE(unsigned __int32, UndefinedUInt);
}
Feature::operator float() const {
  GET_VALUE(float, UndefinedFloat);
}
Feature::operator double() const {
  GET_VALUE(double, UndefinedDouble);
}

Feature& Feature::operator=(bool value) {
  SET_VALUE(eFT_Bool, b);
}
Feature& Feature::operator=(signed char value) {
  SET_VALUE(eFT_Char, c);
}
Feature& Feature::operator=(unsigned char value) {
  SET_VALUE(eFT_UChar, uc);
}
Feature& Feature::operator=(__int32 value) {
  SET_VALUE(eFT_Int32, i);
}
Feature& Feature::operator=(unsigned __int32 value) {
  SET_VALUE(eFT_UInt32, ui);
}
Feature& Feature::operator=(float value) {
  SET_VALUE(eFT_Float, f);
}
Feature& Feature::operator=(double value) {
  SET_VALUE(eFT_Double, d);
}

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


Feature& Features::operator[](std::string name) {
  return *get(name);
}
Feature& Features::operator[](Cache cache) const {
  SIA_ASSERT(cache);
  return *m_cache[cache - 1];
}

void Features::erase(std::string name) {
  FeaturePtr& feature = m_features[name];
  if (nullptr != feature.get()) {
    (*feature) = Feature();
  }
  m_features.erase(name);
}

Features::Cache Features::cache(std::string name) {
  std::shared_ptr<Feature> feature = get(name);

  for (size_t i = 0; i < m_cache.size(); i++) {
    if (m_cache[i].get() == feature.get()) {
      return i + 1;
    }
  }

  m_cache.push_back(feature);
  return m_cache.size();
}