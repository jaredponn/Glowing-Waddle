#include <stdlib.h>
#include <stdio.h>

#include "renderer.h"
#include "shader_tools.h"
#include "shader_programs.h"
#include "vertex_types.h"
#include "logging.h"

void AKY_initRenderer(AKY_Renderer *renderer)
{
	renderer->shader_program = AKY_compileAndLinkShaders(
		defaultVertexShader, defaultGeometryShader,
		defaultFragmentShader);
	AKY_printGLErrors();

	if (!renderer->shader_program) {
		printf("Really bad error in initlaizing shaders. exiting evreything hope you figure this out fam, maybe contact the dev");
		exit(1);
	}
}


void AKY_assignBuffers(struct AKY_Geometry *geometry)
{
	// Generate vao for the object
	// Constant 1 means 1 vao is being generated
	glGenVertexArrays(1, &geometry->vao);
	glBindVertexArray(geometry->vao);

	// Generate vbos for the object
	// Constant 1 means 1 vbo is being generated
	glGenBuffers(1, &geometry->vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->vertex_buffer);
	// Parameters in order: Index of vbo in the vao, number of primitives
	// per element, primitive type, etc.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);

	/*glGenBuffers(1, &geometry.normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry.normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);*/

	glGenBuffers(1, &geometry->color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->color_buffer);
	// Parameters in order: Index of vbo in the vao, number of primitives
	// per element, primitive type, etc.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(1);

	/*glGenBuffers(1, &geometry.uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry.uvBuffer);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(3);*/
}

void AKY_copyBufferData(struct AKY_Geometry const *geometry)
{
	// Send geometry to the GPU
	glBindBuffer(GL_ARRAY_BUFFER, geometry->vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(struct Vec3)
			     * Vector_Vec3_t_size(&geometry->verticies),
		     geometry->verticies.data, GL_STATIC_DRAW);

	/*glBindBuffer(GL_ARRAY_BUFFER, geometry.normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) *
	geometry.normals.size(), geometry.normals.data(), GL_STATIC_DRAW);*/

	glBindBuffer(GL_ARRAY_BUFFER, geometry->color_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(struct Vec3)
			     * Vector_Vec3_t_size(&geometry->colors),
		     geometry->colors.data, GL_STATIC_DRAW);

	/*glBindBuffer(GL_ARRAY_BUFFER, geometry.uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * geometry.uvs.size(),
	geometry.uvs.data(), GL_STATIC_DRAW);*/
}

void AKY_deleteBufferData(struct AKY_Geometry const *geometry)
{

	glDeleteBuffers(1, &geometry->vertex_buffer);
	glDeleteBuffers(1, &geometry->normal_buffer);
	glDeleteBuffers(1, &geometry->color_buffer);
	glDeleteBuffers(1, &geometry->uv_buffer);
	glDeleteVertexArrays(1, &geometry->vao);
}
