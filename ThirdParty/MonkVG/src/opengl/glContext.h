/*
 *  glContext.h
 *  MonkVG-OpenGL
 *
 *  Created by Micah Pearlman on 8/6/10.
 *  Copyright 2010 MP Engineering. All rights reserved.
 *
 */

#ifndef __glContext_h__
#define __glContext_h__

#include "mkContext.h"
#include "glPlatform.h"

namespace MonkVG {
  
  class OpenGLContext : public IContext {
  public:
    static GLuint VERTEX_ATTRIB_POSITION;
    static GLuint VERTEX_ATTRIB_COLOR;
    static GLuint VERTEX_ATTRIB_TEXCOORDS;
  public:
  
    OpenGLContext();
    
    //// factories ////
    virtual IPath* createPath( VGint pathFormat, VGPathDatatype datatype, VGfloat scale, VGfloat bias, VGint segmentCapacityHint, VGint coordCapacityHint, VGbitfield capabilities );
    virtual void destroyPath( IPath* path );	
    virtual void destroyPaint( IPaint* paint );
    virtual IPaint* createPaint();
    virtual IImage* createImage( VGImageFormat format,
                  VGint width, VGint height,
                  VGbitfield allowedQuality );
    virtual void destroyImage( IImage* image );
    virtual IBatch* createBatch();
    virtual void destroyBatch( IBatch* batch );
    virtual IFont* createFont();
    virtual void destroyFont( IFont* font );


    /// paint overrides
    virtual void setStrokePaint( IPaint* paint );
    virtual void setFillPaint( IPaint* paint );

    //// platform specific execution of stroke and fill ////
    virtual void stroke();
    virtual void fill();
    
    virtual void vertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
    virtual void colorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
    virtual void texCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
    virtual void drawArrays(GLenum mode, GLint first, GLsizei count);

    virtual void setColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    virtual void setColor4f(const GLfloat* color);
    virtual void bindTexture(GLuint name);
    
    
    void beginRender();
    void endRender();    
    
    static void checkGLError();
    
    /// batch drawing
    virtual void startBatch( IBatch* batch );
        virtual void dumpBatch( IBatch* batch, void **vertices, size_t *size );
    virtual void endBatch( IBatch* batch );
    
    /// image
    virtual void setImageMode( VGImageMode im );

  private:
    
    // restore values to play nice with other apps
    int		_viewport[4];
    float	_projection[16];
    float	_modelview[16];
    float	_color[4];
  };
}

#endif // __qlContext_h__