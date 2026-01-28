#include "utils.h"

void print_opengl_properties()
{
    int buffer;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &buffer);
    MSG("MAX VERTEX ATTRIBS " << buffer);
}