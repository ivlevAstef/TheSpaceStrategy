#pragma once
#ifndef __COCOS_2D_CCSVG_SOURCE_H__
#define __COCOS_2D_CCSVG_SOURCE_H__

#include "cocos2d.h"

NS_CC_BEGIN

class CCSVGSource: public Ref, public Clonable {
public:
  CCSVGSource(Data* data);
  CCSVGSource(String* string);
  CCSVGSource(const CCSVGSource& copy);

  void setTessellationIterations(size_t numberOfTesselationIterations);

  inline void setContentRect(CCRect rect) { _contentRect = rect; }
  inline void setContentSize(CCSize size) { _contentSize = size; }

  inline CCRect contentRect() const { return _contentRect; }
  inline CCSize contentSize() const { return _contentSize; }

  bool hasTransparentColors() const;

  void draw();
  void optimize();

  virtual Clonable* clone() const override;

private:
  CCRect _contentRect;
  CCSize _contentSize;

  class PrivateData;
  friend class PrivateData;
  std::shared_ptr<PrivateData> _privateData;

  void initialization();
  void initializationWithData(Data* data);
};

NS_CC_END

#endif