#pragma once

typedef unsigned int GLenum;
typedef unsigned int GLbitfield;
typedef unsigned char GLubyte;
typedef float GLfloat;

#define GL_FALSE 0
#define GL_TRUE 1

#define GL_DEPTH_BUFFER_BIT   0x00000100
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_COLOR_BUFFER_BIT   0x00004000

#define GL_VENDOR   0x1F00
#define GL_RENDERER 0x1F01
#define GL_VERSION  0x1F02

bool TryLoadOGL();
const void* CreateContext(const void* windowHandle);
void UnloadOGL();

extern void (*glClear)(GLbitfield mask);
extern void (*glClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern const GLubyte* (*glGetString)(GLenum name);
