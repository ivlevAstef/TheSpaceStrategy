/*
 *  glContext.cpp
 *  MonkVG-OpenGL
 *
 *  Created by Micah Pearlman on 8/6/10.
 *  Copyright 2010 MP Engineering. All rights reserved.
 *
 */

#include "glContext.h"
#include "glPath.h"
#include "glPaint.h"
#include "glBatch.h"
#include "glImage.h"
#include "glFont.h"
#include "mkCommon.h"


namespace MonkVG {
  
  GLuint OpenGLContext::VERTEX_ATTRIB_POSITION = 0;
  GLuint OpenGLContext::VERTEX_ATTRIB_COLOR = 1;
  GLuint OpenGLContext::VERTEX_ATTRIB_TEXCOORDS = 2;

  //// singleton implementation ////
  static OpenGLContext g_context;
  IContext& IContext::instance()
  {
    return g_context;
  }

  
  OpenGLContext::OpenGLContext()
    :	IContext()
  {
  }
  
  void OpenGLContext::checkGLError() {
    
    int err = glGetError();
    
    
    const char* RVAL = "GL_UNKNOWN_ERROR";
    
    switch( err )
    {
      case GL_NO_ERROR:
        RVAL =  "GL_NO_ERROR";
        break;
      case GL_INVALID_ENUM:
        RVAL =  "GL_INVALID_ENUM";
        break;
      case GL_INVALID_VALUE:
        RVAL =  "GL_INVALID_VALUE";
        break;
      case GL_INVALID_OPERATION:
        RVAL = "GL_INVALID_OPERATION";
        break;
      case GL_STACK_OVERFLOW:
        RVAL =  "GL_STACK_OVERFLOW";
        break;
      case GL_STACK_UNDERFLOW:
        RVAL =  "GL_STACK_UNDERFLOW";
        break;
      case GL_OUT_OF_MEMORY:
        RVAL =  "GL_OUT_OF_MEMORY";
        break;
      default:
        break;
    }
    
    if( err != GL_NO_ERROR ) {
      printf("GL_ERROR: %s\n", RVAL );
      MK_ASSERT(0);
    }
  }	
  
  void OpenGLContext::beginRender() {
    
  }
  void OpenGLContext::endRender() {
  }

  
  /// factories
  
  IPath* OpenGLContext::createPath( VGint pathFormat, VGPathDatatype datatype, VGfloat scale, VGfloat bias, VGint segmentCapacityHint, VGint coordCapacityHint, VGbitfield capabilities ) {
  
    OpenGLPath *path = new OpenGLPath(pathFormat, datatype, scale, bias, segmentCapacityHint, coordCapacityHint, capabilities  &= VG_PATH_CAPABILITY_ALL);
    if( path == 0 )
      setError( VG_OUT_OF_MEMORY_ERROR );
  
    return (IPath*)path;
  }
  
  void OpenGLContext::destroyPath( IPath* path ) {
    delete (OpenGLPath*)path;
  }
  
  void OpenGLContext::destroyPaint( IPaint* paint ) {
    delete (OpenGLPaint*)paint;
  }
  
  IPaint* OpenGLContext::createPaint() {
    OpenGLPaint *paint = new OpenGLPaint();
    if( paint == 0 )
      setError( VG_OUT_OF_MEMORY_ERROR );
    return (IPaint*)paint;
  }
  
  IBatch* OpenGLContext::createBatch() {
    OpenGLBatch *batch = new OpenGLBatch();
    if( batch == 0 )
      setError( VG_OUT_OF_MEMORY_ERROR );
    return (IBatch*)batch;
  }
  
  void OpenGLContext::destroyBatch( IBatch* batch ) {
    if ( batch ) {
      delete batch;
    }
  }
  
  IImage* OpenGLContext::createImage( VGImageFormat format,
                     VGint width, VGint height,
                     VGbitfield allowedQuality) {
    return new OpenGLImage( format, width, height, allowedQuality );
  }
  void OpenGLContext::destroyImage( IImage* image ) {
    if ( image ) {
      delete image;
    }
  }
  
  IFont* OpenGLContext::createFont() {
    return new OpenGLFont();
  }
  void OpenGLContext::destroyFont( IFont* font ) {
    if ( font ) {
      delete font;
    }
  }


  /// state 
  void OpenGLContext::setStrokePaint( IPaint* paint ) {
    if ( paint != _stroke_paint ) {
      IContext::setStrokePaint( paint );
      OpenGLPaint* glPaint = (OpenGLPaint*)_stroke_paint;
      //glPaint->setGLState();
      glPaint->setIsDirty( true );
    }
  }
  
  void OpenGLContext::setFillPaint( IPaint* paint ) {
    if ( paint != _fill_paint ) {
      IContext::setFillPaint( paint );
      OpenGLPaint* glPaint = (OpenGLPaint*)_fill_paint;
      //glPaint->setGLState();
      glPaint->setIsDirty( true );
    }
    
  }

  
  void OpenGLContext::stroke() {
    if ( _stroke_paint ) {
      OpenGLPaint* glPaint = (OpenGLPaint*)_stroke_paint;
      this->setColor4f( glPaint->getPaintColor());
      glPaint->setIsDirty( false );
      // set the fill paint to dirty
      if ( _fill_paint ) {
        glPaint = (OpenGLPaint*)_fill_paint;
        glPaint->setIsDirty( true );
      }
    }
  }
  
  void OpenGLContext::fill() {
    
    if ( _fill_paint && _fill_paint->getPaintType() == VG_PAINT_TYPE_COLOR ) {
      OpenGLPaint* glPaint = (OpenGLPaint*)_fill_paint;
      this->setColor4f(glPaint->getPaintColor());
      glPaint->setIsDirty( false );
      // set the stroke paint to dirty
      if ( _stroke_paint ) {
        glPaint = (OpenGLPaint*)_stroke_paint;
        glPaint->setIsDirty( true );
      }
    }

  }
  
  void OpenGLContext::startBatch( IBatch* batch ) {
    assert( _currentBatch == 0 );	// can't have multiple batches going on at once
    _currentBatch = batch;
  }
    void OpenGLContext::dumpBatch( IBatch *batch, void **vertices, size_t *size ) {
        _currentBatch->dump( vertices, size );
    }
  void OpenGLContext::endBatch( IBatch* batch ) {
    _currentBatch->finalize();
    _currentBatch = 0;
  }

  
  void OpenGLContext::vertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
    glVertexAttribPointer(VERTEX_ATTRIB_POSITION, size, type, GL_FALSE, stride, pointer);
  }
  void OpenGLContext::colorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
    glVertexAttribPointer(VERTEX_ATTRIB_COLOR, size, type, GL_TRUE, stride, pointer);
  }
  void OpenGLContext::texCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
    glVertexAttribPointer(VERTEX_ATTRIB_TEXCOORDS, size, type, GL_FALSE, stride, pointer);
  }
  void OpenGLContext::drawArrays(GLenum mode, GLint first, GLsizei count) {
    glDrawArrays(mode, first, count);
  }

  void OpenGLContext::setColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    //TODO:
    glColor4f(r,g,b,a);
  }

  void OpenGLContext::setColor4f(const GLfloat* color) {
    //TODO:
    glColor4f(color[0], color[1], color[2], color[3]);
  }
  
  void OpenGLContext::bindTexture(GLuint name) {
    //TODO: GL::bindTexture2D(_textureID);
    glBindTexture(GL_TEXTURE_2D, name);
  }

  void OpenGLContext::setImageMode( VGImageMode im ) {
    IContext::setImageMode( im );
    switch ( im ) {
      case VG_DRAW_IMAGE_NORMAL:
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        break;
      case VG_DRAW_IMAGE_MULTIPLY:
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        break;
      case VG_DRAW_IMAGE_STENCIL:
        break;
      default:
        break;
    }
  }
  
  
  
}