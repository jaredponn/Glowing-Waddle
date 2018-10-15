#include "scene.h"
#include "logging.h"
static int fuckall = 0;

// initalizes the vectors and stuff
void AKY_initScene(AKY_Scene *scene)
{
	Vector_Geometry_t_init(&scene->geometries);
	AKY_initRenderer(&scene->renderer);
}

// actually where things are renderered
void AKY_pushBuffers(AKY_Scene *scene)
{

	// Create a single triangle
	// Additional triangles can be created by pushing groups of
	// three more vertices into the verts vector
	struct AKY_Geometry triangle;
	AKY_initGeometry(&triangle);

	// veritices
	Vector_Vec3_t_push_back(&triangle.verticies,
				(struct Vec3){-0.5f, -0.5f, 1.0f});
	Vector_Vec3_t_push_back(&triangle.verticies,
				(struct Vec3){-0.5f, 0.0f, 1.0f});
	Vector_Vec3_t_push_back(&triangle.verticies,
				(struct Vec3){0.0f, 0.0f, 1.0f});
	/* Vector_Vec3_t_push_back(&triangle.verticies, */
	/* 			(struct Vec3){0.0f, -0.5f, 1.0f}); */

	// Colors are stored per vertex in the order of the vertices
	Vector_Vec3_t_push_back(&triangle.colors,
				(struct Vec3){1.0f, 0.0f, 0.0f});
	Vector_Vec3_t_push_back(&triangle.colors,
				(struct Vec3){0.0f, 1.0f, 0.0f});
	Vector_Vec3_t_push_back(&triangle.colors,
				(struct Vec3){0.0f, 0.0f, 1.0f});
	/* Vector_Vec3_t_push_back(&triangle.colors, */
	/* 			(struct Vec3){0.0f, 0.0f, 0.0f}); */


	/* triangle.draw_mode = GL_TRIANGLES; */
	triangle.draw_mode = GL_TRIANGLE_FAN;
	/* triangle.draw_mode = GL_LINE_LOOP; */

	// Construct vao and vbos for the triangle
	AKY_assignBuffers(&triangle);

	// Send the triangle data to the GPU
	// Must be done every time the triangle is modified in any way, ex.
	// verts, colors, normals, uvs, etc.
	AKY_copyBufferData(&triangle);

	// Add the triangle to the scene objects
	Vector_Geometry_t_push_back(&scene->geometries, triangle);
}

void AKY_renderScene(AKY_Scene *scene)
{
	// gives us a sexy dark grey background
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// usesthe shader program
	glUseProgram(scene->renderer.shader_program);

	// rendering all the geometry objects
	size_t geometryVecLen = Vector_Geometry_t_size(&scene->geometries);
	struct AKY_Geometry *tmp;

	for (size_t i = 0; i < geometryVecLen; ++i) {
		tmp = Vector_Geometry_t_get_p(&scene->geometries, i);
		glBindVertexArray(tmp->vao);
		glDrawArrays(tmp->draw_mode, 0,
			     Vector_Vec3_t_size(&tmp->verticies));

		// reset state to default with no shader or geometry bound
		glBindVertexArray(0);
	}

	// resets current used program
	glUseProgram(0);

	// prints any rendering erorros
	AKY_printGLErrors();
}
