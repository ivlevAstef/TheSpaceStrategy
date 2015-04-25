#include "SVGTexture2D.h"
#include "MonkSVG/mkOpenVG_SVG.h"
#include "MonkVG/openvg.h"
#include "MonkVG/vgext.h"
#include "platform/CCFileUtils.h"


USING_NS_CC;

class SVGTexture2D::PrivateData {
public:
  bool _isOptimized;
  MonkSVG::OpenVG_SVGHandler::SmartPtr _svg;
};

SVGTexture2D::SVGTexture2D() {
  _privateData = std::make_shared<SVGTexture2D::PrivateData>();

  setTessellationIterations(3);

  _privateData->_isOptimized = false;
  _privateData->_svg = std::static_pointer_cast<MonkSVG::OpenVG_SVGHandler>(MonkSVG::OpenVG_SVGHandler::create());
}


bool SVGTexture2D::initWithData(Data& data) {
  MonkSVG::OpenVG_SVGHandler::SmartPtr& svg = _privateData->_svg;

  MonkSVG::SVG parser;
  parser.initialize(svg);
  if (!parser.read((char *)data.getBytes())) {
    return false;
  }

  _contentRect = Rect(svg->minX(), svg->minY(), svg->width(), svg->height());
  _contentSize = Size(svg->width(), svg->height());

  return true;
}

bool SVGTexture2D::initWithFile(std::string& string) {
  Data data = FileUtils::getInstance()->getDataFromFile(string);
  return initWithData(data);
}

bool SVGTexture2D::initWithFile(const char* string) {
  return initWithFile(std::string(string));
}

SVGTexture2D::SVGTexture2D(const SVGTexture2D& copy) {
  _contentRect = copy._contentRect;
  _contentSize = copy._contentSize;
  _privateData = copy._privateData;
}

void SVGTexture2D::setTessellationIterations(size_t numberOfTesselationIterations) {
  vgSeti(VG_TESSELLATION_ITERATIONS_MNK, numberOfTesselationIterations);
}

bool SVGTexture2D::hasTransparentColors() const {
  if (_privateData->_svg.get()) {
    return _privateData->_svg->hasTransparentColors();
  }
  return false;
}


void SVGTexture2D::draw() {
  _privateData->_svg->draw();
}