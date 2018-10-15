#pragma once

#include "extern/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>


GLuint AKY_compileAndLinkShaders(const char *vertexSource,
				 const char *geometrySource,
				 const char *fragmentSource);
