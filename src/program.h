#pragma once
#define UNUSED(val) (void)val

#include "extern/glad/include/glad/glad.h"

#include <stdio.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "scene.h"

// const
#define WINDOWWIDTH 512
#define WINDOWHEIGHT 512

struct PRG_Program {
	GLFWwindow *window;
};


static inline void errorCallback(int error, const char *const description)
{
	printf("GLFW error num %i:\n", error);
	printf("%s", description);
}

static inline void keyCallback(GLFWwindow *window, int key, int scancode,
			       int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	UNUSED(scancode);
	UNUSED(mods);
}

static inline void GLAPIENTRY MessageCallback(GLenum source, GLenum type,
					      GLuint id, GLenum severity,
					      GLsizei length,
					      const GLchar *message,
					      const void *userParam)
{
	UNUSED(source);
	UNUSED(id);
	UNUSED(length);
	UNUSED(userParam);
	fprintf(stderr,
		"GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type,
		severity, message);
}


static inline void PRG_init(struct PRG_Program *program)
{
	if (!glfwInit()) {
		printf("error initalizing glfw -- giving up on life");
		exit(1);
	}

	glfwSetErrorCallback(errorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	program->window =
		glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, "title", 0, 0);

	if (!program->window) {
		printf("error, progrma failed to create glfw window. Termianting..");
		glfwTerminate();
		exit(1);
	}

	// key callback
	glfwSetKeyCallback(program->window, keyCallback);

	// bring window to foreground
	glfwMakeContextCurrent(program->window);

	// initalize gald (finding the appropraite opengl config for sys)
	if (!gladLoadGL()) {
		printf("Failed to load GLAD.. Exiting..");
		exit(1);
	}

	// opengl debug stuff
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

static inline void PRG_run(struct PRG_Program *program)
{
	AKY_Scene scene;
	AKY_initScene(&scene);

	AKY_pushBuffers(&scene);

	while (!glfwWindowShouldClose(program->window)) {
		AKY_renderScene(&scene);
		glfwSwapBuffers(program->window);
		glfwPollEvents();
	}
}

#undef UNUSED
#undef WINDOWWIDTH
#undef WINDOWHEIGHT
