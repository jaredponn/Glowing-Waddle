#pragma once

#include "extern/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

static inline void AKY_printGLErrors()
{
	for (GLenum flag = glGetError(); flag != GL_NO_ERROR;
	     flag = glGetError()) {
		printf("OpenGL ERROR:  ");
		switch (flag) {
		case GL_INVALID_ENUM:
			printf("GL_INVALID_ENUM\n");
			break;
		case GL_INVALID_VALUE:
			printf("GL_INVALID_VALUE");
			break;
		case GL_INVALID_OPERATION:
			printf("GL_INVALID_OPERATION\n");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			printf("GL_INVALID_FRAMEBUFFER_OPERATION\n");
			break;
		case GL_OUT_OF_MEMORY:
			printf("GL_OUT_OF_MEMORY\n");
			break;
		default:
			printf("Unknown OpenGL error");
		}
	}
}
