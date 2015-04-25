#include "SVGSprite.h"
#include "SVGTexture2D.h"
#include "renderer/CCRenderer.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgramState.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "2d/CCDrawingPrimitives.h"

#include "MonkVG/openvg.h"
#include "MonkVG/vgu.h"
#include "MonkSVG/mkSVG.h"
#include "MonkSVG/mkOpenVG_SVG.h"

USING_NS_CC;



SVGSprite::SVGSprite() {
  _texture = nullptr;
  init();
}

SVGSprite::~SVGSprite() {
  if (_texture) {
    _texture->release();
    _texture = nullptr;
  }
}

SVGSprite* SVGSprite::createWithFile(const char* file) {
  return createWithFile(std::string(file));
}

SVGSprite* SVGSprite::createWithFile(std::string& file) {
  SVGSprite* sprite = new (std::nothrow) SVGSprite();
  if (sprite && sprite->initWithFile(file)) {
    sprite->autorelease();
    return sprite;
  }
  CC_SAFE_DELETE(sprite);
  return nullptr;
}

SVGSprite* SVGSprite::createWithTexture(SVGTexture2D* texture) {
  SVGSprite* sprite = new (std::nothrow) SVGSprite();
  if (sprite && sprite->initWithTexture(texture)) {
    sprite->autorelease();
    return sprite;
  }
  CC_SAFE_DELETE(sprite);
  return nullptr;
}


bool SVGSprite::initWithFile(std::string& file) {
  SVGTexture2D* texture = new (std::nothrow) SVGTexture2D();
  if (texture && texture->initWithFile(file)) {
    texture->autorelease();
    return initWithTexture(texture);
  }
  CC_SAFE_DELETE(texture);
  return false;
}

bool SVGSprite::initWithTexture(SVGTexture2D* texture) {
  if (!texture) {
    return false;
  }

  _texture = texture;
  _texture->retain();


  _blendFunc = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
  _contentSize = _texture->contentSize();

  Rect rect = _texture->contentRect();
  _anchorPoint = Vec2(-rect.origin.x / rect.size.width, -rect.origin.y / rect.size.height);

  setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_U_COLOR));
}

void SVGSprite::setBlendFunc(const BlendFunc& blendFunc) {
  _blendFunc = blendFunc;
}

const BlendFunc& SVGSprite::getBlendFunc() const {
  return _blendFunc;
}


void SVGSprite::draw(Renderer* renderer, const Mat4& transform, uint32_t flags) {
  if (!_texture) {
    return;
  }

  _customCommand.init(_globalZOrder, transform, flags);
  _customCommand.func = CC_CALLBACK_0(SVGSprite::onDraw, this, transform, flags);

  renderer->addCommand(&_customCommand);
}

struct VEC_COLOR {
  Vec2 vertices;
  Color4B colors;
};

void SVGSprite::onDraw(const Mat4& transform, bool transformUpdated) {

  getGLProgram()->use();
  getGLProgram()->setUniformsForBuiltins(transform);

  GLfloat color[4] = {1, 1, 1, 1};

  getGLProgram()->setUniformLocationWith4fv(getGLProgram()->getUniformLocation("u_color"), (GLfloat*)color, 1);


  bool doBlend = _texture->hasTransparentColors();
  bool doBlendFunc = (_blendFunc.src != CC_BLEND_SRC || _blendFunc.dst != CC_BLEND_DST);

  GL::blendFunc(_blendFunc.src, _blendFunc.dst);

  /*float textureSize = 200;

  VEC_COLOR data[4];

  data[0].vertices = Vec2(0, 0);
  data[1].vertices = Vec2(textureSize, 0);
  data[2].vertices = Vec2(0, textureSize);
  data[3].vertices = Vec2(textureSize, textureSize);

  data[0].colors = Color4B(255, 255, 255, 255);
  data[1].colors = Color4B(255, 255, 255, 255);
  data[2].colors = Color4B(255, 255, 255, 255);
  data[3].colors = Color4B(255, 255, 255, 255);


  GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
  glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(VEC_COLOR), (GLvoid*)(&data[0].vertices));
  glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VEC_COLOR), (GLvoid*)(&data[0].colors));

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);*/

  _texture->draw();
}