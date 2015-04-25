//
//  glBatch.cpp
//  MonkVG-iOS
//
//  Created by Micah Pearlman on 6/27/11.
//  Copyright 2011 Zero Vision. All rights reserved.
//

#include "glBatch.h"
#include "glContext.h"

namespace MonkVG {
  
  OpenGLBatch::OpenGLBatch()
  :	IBatch()
  ,	_vertexCount(0)
  {}
  OpenGLBatch::~OpenGLBatch() {
  }
  
  void OpenGLBatch::addPathVertexData( GLfloat* fillVerts, size_t fillVertCnt, GLfloat* strokeVerts, size_t strokeVertCnt, VGbitfield paintModes ) {
    
    // get the current transform
    Matrix33& transform = *IContext::instance().getActiveMatrix();
    
    if ( paintModes & VG_FILL_PATH) {
      vertex_t vert;

      // get the paint color
      IPaint* paint = IContext::instance().getFillPaint();
      const VGfloat* fc = paint->getPaintColor();
      
      vert.color =	( uint32_t(fc[3] * 255.0f) << 24 )	// a
            |	( uint32_t(fc[2] * 255.0f) << 16 )	// b
            |	( uint32_t(fc[1] * 255.0f) << 8 )	// g
            |	( uint32_t(fc[0] * 255.0f) << 0 );	// r
      
      // get vertices and transform them
      VGfloat v[2];
      for ( int i = 0; i < fillVertCnt * 2; i+=2 ) {
        v[0] = fillVerts[i];
        v[1] = fillVerts[i + 1];
        affineTransform( vert.v, transform, v );
        _vertices.push_back( vert );
      }
    }
    
    if ( paintModes & VG_STROKE_PATH) {
      vertex_t vert, startVertex, lastVertex;
      
      // get the paint color
      IPaint* paint = IContext::instance().getStrokePaint();
      const VGfloat* fc = paint->getPaintColor();
      
      vert.color =	( uint32_t(fc[3] * 255.0f) << 24 )	// a
      |	( uint32_t(fc[2] * 255.0f) << 16 )	// b
      |	( uint32_t(fc[1] * 255.0f) << 8 )	// g
      |	( uint32_t(fc[0] * 255.0f) << 0 );	// r
      
      // get vertices and transform them
      VGfloat v[2];
      int vertcnt = 0;
      for ( int i = 0; i < strokeVertCnt * 2; i+=2, vertcnt++ ) {
        v[0] = strokeVerts[i];
        v[1] = strokeVerts[i + 1];
        affineTransform( vert.v, transform, v );
        
        // for stroke we need to convert from a strip to triangle
        switch ( vertcnt ) {
          case 0:
            _vertices.push_back( vert );
            break;
          case 1:
            startVertex = vert;
            _vertices.push_back( vert );
            break;
          case 2:
            lastVertex = vert;
            _vertices.push_back( vert );						
            break;
            
          default:
            _vertices.push_back( startVertex );
            _vertices.push_back( lastVertex );
            _vertices.push_back( vert );
            startVertex = lastVertex;
            lastVertex = vert;
            break;
        }
      }
    }
    

    
  }
  
  void OpenGLBatch::finalize() {

    _vertexCount = _vertices.size();
    _vertices.clear();
    
  }
    
  void OpenGLBatch::dump( void **vertices, size_t *size ) {
        
      *size = _vertices.size() * sizeof( vertex_t );
      *vertices = std::malloc( *size );
        
      std::memcpy( *vertices, &_vertices[0], *size );
        
  }
  
  void OpenGLBatch::draw() {
    // get the native OpenGL context
    OpenGLContext& glContext = (MonkVG::OpenGLContext&)IContext::instance();
    glContext.beginRender();

    glContext.vertexPointer(2, GL_FLOAT, sizeof(vertex_t), (GLvoid*)(&_vertices[0].v));
    glContext.colorPointer(4, GL_UNSIGNED_BYTE, sizeof(vertex_t), (GLvoid*)(&_vertices[0].color));
    glContext.drawArrays(GL_TRIANGLES, 0, _vertexCount);
    
    glContext.endRender();

  }
    
}