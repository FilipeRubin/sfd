#pragma once

typedef unsigned int GLenum;
typedef unsigned char GLubyte;

#define GL_VENDOR   0x1F00
#define GL_RENDERER 0x1F01
#define GL_VERSION  0x1F02

bool TryLoadOGL();
void UnloadOGL();

const GLubyte* glGetString(GLenum name);
