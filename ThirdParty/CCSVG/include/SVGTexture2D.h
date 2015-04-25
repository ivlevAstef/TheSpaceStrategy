#pragma once
#ifndef __COCOS_2D_SVG_TEXTURE_2D_H__
#define __COCOS_2D_SVG_TEXTURE_2D_H__

#include "SVGDefines.h"
#include "base/CCRef.h"
#include "base/CCData.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN

class CC_SVG_DLL SVGTexture2D: public Ref {
public:
  SVGTexture2D();
  SVGTexture2D(const SVGTexture2D& copy);

  bool initWithData(Data& data);
  bool initWithFile(const char* string);
  bool initWithFile(std::string& string);

  void setTessellationIterations(size_t numberOfTesselationIterations);

  inline void setContentRect(Rect rect) { _contentRect = rect; }
  inline void setContentSize(Size size) { _contentSize = size; }

  inline Rect contentRect() const { return _contentRect; }
  inline Size contentSize() const { return _contentSize; }

  bool hasTransparentColors() const;

  void draw();

private:
  Rect _contentRect;
  Size _contentSize;

  class PrivateData;
  friend class PrivateData;
  std::shared_ptr<PrivateData> _privateData;
};

NS_CC_END

#endif