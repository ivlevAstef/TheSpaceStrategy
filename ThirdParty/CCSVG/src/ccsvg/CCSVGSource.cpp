#include "MonkSVG/mkOpenVG_SVG.h"
#include "MonkVG/openvg.h"
#include "MonkVG/vgext.h"
#include "CCSVGSource.h"


USING_NS_CC;

class CCSVGSource::PrivateData {
public:
  bool _isOptimized;
  MonkSVG::OpenVG_SVGHandler::SmartPtr _svg;
};

void CCSVGSource::initialization() {
  _privateData = std::make_shared<CCSVGSource::PrivateData>();

  setTessellationIterations(3);

  _privateData->_isOptimized = false;
  _privateData->_svg = static_pointer_cast<MonkSVG::OpenVG_SVGHandler>(MonkSVG::OpenVG_SVGHandler::create());
}

void CCSVGSource::initializationWithData(Data* data) {
  MonkSVG::OpenVG_SVGHandler::SmartPtr& svg = _privateData->_svg;

  MonkSVG::SVG parser;
  parser.initialize(svg);
  parser.read((char *)data->getBytes());

  _contentRect = CCRectMake(svg->minX(), svg->minY(), svg->width(), svg->height());
  _contentSize = CCSizeMake(svg->width(), svg->height());
}

CCSVGSource::CCSVGSource(Data* data) {
  initialization();
  initializationWithData(data);

}
CCSVGSource::CCSVGSource(String* string) {
  initialization();

  Data data = CCFileUtils::sharedFileUtils()->getDataFromFile(string->getCString());
  initializationWithData(&data);
}

CCSVGSource::CCSVGSource(const CCSVGSource& copy) {
  _contentRect = copy._contentRect;
  _contentSize = copy._contentSize;
  _privateData = copy._privateData;
}

void CCSVGSource::setTessellationIterations(size_t numberOfTesselationIterations) {
  vgSeti(VG_TESSELLATION_ITERATIONS_MNK, numberOfTesselationIterations);
}

bool CCSVGSource::hasTransparentColors() const {
  if (_privateData->_svg.get()) {
    return _privateData->_svg->hasTransparentColors();
  }
  return false;
}


void CCSVGSource::draw() {
  optimize();
  _privateData->_svg->draw();
}

void CCSVGSource::optimize() {
  if (_privateData->_isOptimized) {

    VGfloat matrix[9];
    vgGetMatrix(matrix);

    vgLoadIdentity();
    _privateData->_svg->optimize();
    vgLoadMatrix(matrix);

    _privateData->_isOptimized = true;

  }
}

Clonable* CCSVGSource::clone() const {
  auto a = new (std::nothrow) CCSVGSource(*this);
  a->autorelease();
  return a;
}
