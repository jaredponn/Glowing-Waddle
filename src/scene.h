#pragma once

#include "extern/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "vertex_types.h"
#include "GenericVector.h"
#include "geometry.h"
#include "renderer.h"


// -----------------------------------------
//    abstract all of the rendering here
// -----------------------------------------


VECTOR_DECLARE(struct AKY_Geometry, Geometry)

typedef struct Vector_Geometry_t Vector_Geometry_t;

typedef struct AKY_Scene {
	struct AKY_Renderer renderer;
	Vector_Geometry_t geometries;
} AKY_Scene;

// initalizes the vectors and stuff
void AKY_initScene(AKY_Scene *scene);

// actually where things are renderered
void AKY_pushBuffers(AKY_Scene *scene);

void AKY_renderScene(AKY_Scene *scene);
