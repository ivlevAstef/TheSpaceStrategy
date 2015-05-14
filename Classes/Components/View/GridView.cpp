#include "GridView.h"
#include "logger/SIAUtils_Logger.h"

using namespace Components::View;
USING_NS_CC;

GridView* GridView::create(size_t width, size_t height, size_t cellSize) {
  GridView* view = new (std::nothrow)GridView(width, height, cellSize);
  if (view) {
    view->autorelease();
    return view;
  }

  SIA_LOG_ERR("can't create gridView");
  CC_SAFE_DELETE(view);
  return nullptr;
}

GridView::GridView(size_t width, size_t height, size_t cellSize) {
  SIA_CHECK_RET(!init(), ERR);

  m_width = width;
  m_height = height;
  m_cellSize = cellSize;

  double octaEdge = m_cellSize / (sqrt(2) + 1.0);
  double octaB = m_cellSize / (sqrt(2) + 2.0);

  m_vertices.push_back(Vec2(0, octaB));
  m_vertices.push_back(Vec2(0, octaB + octaEdge));
  m_vertices.push_back(Vec2(octaB, m_cellSize));
  m_vertices.push_back(Vec2(octaB + octaEdge, m_cellSize));
  m_vertices.push_back(Vec2(m_cellSize, octaB + octaEdge));
  m_vertices.push_back(Vec2(m_cellSize, octaB));
  m_vertices.push_back(Vec2(octaB + octaEdge, 0));
  m_vertices.push_back(Vec2(octaB, 0));
}

static void moveVertices(std::vector<Vec2>& vertices, int mx, int my) {
  for (size_t i = 0; i < vertices.size(); i++) {
    vertices[i].x += mx;
    vertices[i].y += my;
  }
}

static void cleanVertices(std::vector<Vec2>& vertices, const std::vector<Vec2>& cleanData) {
  SIA_ASSERT(vertices.size() == cleanData.size());

  for (size_t i = 0; i < vertices.size(); i++) {
    vertices[i] = cleanData[i];
  }
}

//TODO:create utils
static double normalizeNumber(double n, double step) {
  if (n < 0) {
    n += step * (1 + (int)(-n / step));
  }
  if (n > step) {
    n -= step * ((int)(n / step));
  }
  return n;
}

void GridView::draw(Renderer* renderer, const Mat4& transform, uint32_t flags) {
  if ((flags & FLAGS_TRANSFORM_DIRTY) == flags) {
    clear();

    Vec2 pos = getPosition();

    int xBegin = normalizeNumber(-pos.x, m_cellSize);
    int yBegin = normalizeNumber(-pos.y, m_cellSize);

    int cellWidth = m_cellSize;
    int cellHeight = m_cellSize;


    int width = getContentSize().width / m_cellSize;
    int height = getContentSize().height / m_cellSize;


    std::vector<Vec2> vertices;
    vertices.resize(m_vertices.size());

    for (int yI = -1; yI < height + 1; yI++) {
      cleanVertices(vertices, m_vertices);
      moveVertices(vertices, xBegin - cellWidth, yBegin + yI*cellHeight);

      for (int xI = -1; xI < width + 1; xI++) {
        drawPoly(&vertices[0], vertices.size(), true, Color4F(0.1f, 0.05f, 0.3f, 1.0f));

        moveVertices(vertices, cellWidth, 0);
      }
    }
  }  

  DrawNode::draw(renderer, transform, flags);
}

cocos2d::Vec2 GridView::normalizePosition(cocos2d::Vec2 pos) {
  pos.x = normalizeNumber(pos.x, m_width * m_cellSize);
  pos.y = normalizeNumber(pos.y, m_height * m_cellSize);
  return pos;
}

bool GridView::convert(cocos2d::Touch* touch, size_t& resX, size_t& resY) {
  SIA_ASSERT(touch);
  Vec2 pos = convertTouchToNodeSpace(touch) + getPosition();
  pos = normalizePosition(pos);

  int x = pos.x / m_cellSize;
  int y = pos.y / m_cellSize;

  resX = (size_t)x;
  resY = (size_t)y;
  return true;
}

cocos2d::Vec2 GridView::getCenter(size_t x, size_t y) {
  Vec2 center = Vec2((x * m_cellSize) + m_cellSize / 2, (y * m_cellSize) + m_cellSize / 2);
  center = center - getPosition();
  center = normalizePosition(center + getContentSize()) - getContentSize();

  return convertToWorldSpace(center);
}