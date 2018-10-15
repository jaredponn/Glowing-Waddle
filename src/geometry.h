#pragma once

#include <GLFW/glfw3.h>

#include "vertex_types.h"
#include "GenericVector.h"

// -----------------------------------------
//    One group of objecrts
// -----------------------------------------
VECTOR_DECLARE(struct Vec3, Vec3)

struct AKY_Geometry {
	// data for verticies
	struct Vector_Vec3_t verticies;
	struct Vector_Vec3_t normals;
	struct Vector_Vec3_t colors;
	struct Vector_Vec3_t uvs; // texture coords

	// pointers to things associated with geomtry
	GLuint vao;
	GLuint vertex_buffer;
	GLuint normal_buffer;
	GLuint uv_buffer;
	GLuint color_buffer;

	// draw mode for opengGl
	GLuint draw_mode;
};

void AKY_initGeometry(struct AKY_Geometry *geometry);

void AKY_reserveGeometry(struct AKY_Geometry *geometry, size_t memory);

void AKY_freeGeometry(struct AKY_Geometry *geometry);
