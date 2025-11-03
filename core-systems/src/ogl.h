#pragma once

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef void GLvoid;
typedef signed long long int GLsizeiptr;
typedef char GLchar;

#define GL_FALSE 0
#define GL_TRUE 1

#define GL_POINTS         0x0000
#define GL_LINES          0x0001
#define GL_LINE_LOOP      0x0002
#define GL_LINE_STRIP     0x0003
#define GL_TRIANGLES      0x0004
#define GL_TRIANGLE_STRIP 0x0005
#define GL_TRIANGLE_FAN   0x0006

#define GL_BYTE           0x1400
#define GL_UNSIGNED_BYTE  0x1401
#define GL_SHORT          0x1402
#define GL_UNSIGNED_SHORT 0x1403
#define GL_INT            0x1404
#define GL_UNSIGNED_INT   0x1405
#define GL_FLOAT          0x1406
#define GL_2_BYTES        0x1407
#define GL_3_BYTES        0x1408
#define GL_4_BYTES        0x1409
#define GL_DOUBLE         0x140A

#define GL_DEPTH_BUFFER_BIT   0x00000100
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_COLOR_BUFFER_BIT   0x00004000

#define GL_VENDOR   0x1F00
#define GL_RENDERER 0x1F01
#define GL_VERSION  0x1F02

#define GL_MULTISAMPLE 0x809D

#define GL_ARRAY_BUFFER         0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_COPY_READ_BUFFER     0x8F36
#define GL_COPY_WRITE_BUFFER    0x8F37
#define GL_UNIFORM_BUFFER       0x8A11

#define GL_STREAM_DRAW  0x88E0
#define GL_STREAM_READ  0x88E1
#define GL_STREAM_COPY  0x88E2
#define GL_STATIC_DRAW  0x88E4
#define GL_STATIC_READ  0x88E5
#define GL_STATIC_COPY  0x88E6
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_DYNAMIC_READ 0x88E9
#define GL_DYNAMIC_COPY 0x88EA

#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER   0x8B31
#define GL_GEOMETRY_SHADER 0x8DD9

bool TryLoadOGL();
const void* CreateContext(const void* windowHandle, const void* sharedContext = nullptr);
void UnloadOGL();

extern void          (*glAttachShader)(GLuint program, GLuint shader);
extern void          (*glBindBuffer)(GLenum target, GLuint buffer);
extern void          (*glBindVertexArray)(GLuint array);
extern void          (*glBufferData)(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
extern void          (*glClear)(GLbitfield mask);
extern void          (*glClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern void          (*glCompileShader)(GLuint shader);
extern GLuint        (*glCreateProgram)();
extern GLuint        (*glCreateShader)(GLenum shaderType);
extern void          (*glDeleteBuffers)(GLsizei n, GLuint* arrays);
extern void          (*glDeleteProgram)(GLuint program);
extern void          (*glDeleteShader)(GLuint shader);
extern void          (*glDeleteVertexArrays)(GLsizei n, GLuint* arrays);
extern void          (*glDrawArrays)(GLenum mode, GLint first, GLsizei count);
extern void          (*glDrawElements)(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
extern void          (*glEnable)(GLenum cap);
extern void          (*glEnableVertexAttribArray)(GLuint index);
extern void          (*glGenBuffers)(GLsizei n, GLuint* buffers);
extern void          (*glGenVertexArrays)(GLsizei n, GLuint* arrays);
extern const GLubyte*(*glGetString)(GLenum name);
extern GLint         (*glGetUniformLocation)(GLuint program, const GLchar* name);
extern GLboolean     (*glIsProgram)(GLuint program);
extern GLboolean     (*glIsVertexArray)(GLuint array);
extern void          (*glLinkProgram)(GLuint program);
extern void          (*glShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
extern void          (*glUseProgram)(GLuint program);
extern void          (*glUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
extern void          (*glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
extern void          (*glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
