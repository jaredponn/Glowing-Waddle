#pragma once

#include "extern/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "geometry.h"

typedef struct AKY_Renderer {
	GLuint shader_program;
} AKY_Renderer;

// intializes the render with a default shader
void AKY_initRenderer(AKY_Renderer *renderer);

// assings the buffesr to the right spots
void AKY_assignBuffers(struct AKY_Geometry *geometry);

// copy the buffer data to opengl
void AKY_copyBufferData(struct AKY_Geometry const *geometry);

// delete the opengl buffer data
void AKY_deleteBufferData(struct AKY_Geometry const *geometry);
