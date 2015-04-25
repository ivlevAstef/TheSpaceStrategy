#pragma once
#ifndef __COCOS_2D_SVG_SPRITE_H__
#define __COCOS_2D_SVG_SPRITE_H__

#include "SVGDefines.h"
#include "2d/CCNode.h"
#include "base/CCProtocols.h"
#include "renderer/CCCustomCommand.h"
#include "SVGTexture2D.h"

NS_CC_BEGIN

class CC_SVG_DLL SVGSprite: public Node, public BlendProtocol {
public:
  static SVGSprite* createWithFile(const char* file);
  static SVGSprite* createWithFile(std::string& file);
  static SVGSprite* createWithTexture(SVGTexture2D* texture);

  virtual void setBlendFunc(const BlendFunc& blendFunc) override;
  virtual const BlendFunc& getBlendFunc() const override;

CC_CONSTRUCTOR_ACCESS:

  SVGSprite();
  virtual ~SVGSprite();
  bool initWithFile(std::string& file);
  bool initWithTexture(SVGTexture2D* texture);

protected:
  virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;

  void onDraw(const Mat4& transform, bool transformUpdated);

protected:
  BlendFunc     _blendFunc;
  SVGTexture2D* _texture;

  CustomCommand _customCommand;
};

NS_CC_END

#endif