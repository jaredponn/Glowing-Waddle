#include <stdio.h>
#include <stdlib.h>

#include "shader_tools.h"

// error handlinh
static inline void printErrorMsg(GLuint shaderPrg, GLenum errorMsgType)
{
	// error handling
	GLint status;
	glGetShaderiv(shaderPrg, errorMsgType, &status);
	if (status == GL_FALSE) {
		GLint errorMsgLen;
		glGetShaderiv(shaderPrg, GL_INFO_LOG_LENGTH, &errorMsgLen);

		char *errorMsgBuf = malloc(errorMsgLen * sizeof(char));

		glGetShaderInfoLog(shaderPrg, errorMsgLen, &errorMsgLen,
				   errorMsgBuf);
		printf("\n---------\n ERROR with shader. OpenGL error message:\n%s\n---------\n",
		       errorMsgBuf);

		free(errorMsgBuf);
	}
}

// creates and returns a shader from the soruce
static inline GLuint compileShader(GLenum shaderType, const char *source)
{
	GLuint shaderPrg = glCreateShader(shaderType);
	glShaderSource(shaderPrg, 1, &source, 0);
	glCompileShader(shaderPrg);

	// error handling
	printErrorMsg(shaderPrg, GL_COMPILE_STATUS);

	return shaderPrg;
}

// links the shaders
static inline GLuint linkShaders(GLuint vertexShader, GLuint geometryShader,
				 GLuint fragmentShader)
{
	GLuint shaderPrg = glCreateProgram();

	// attaches it to the program if it exists
	if (vertexShader)
		glAttachShader(shaderPrg, vertexShader);
	if (geometryShader)
		glAttachShader(shaderPrg, geometryShader);
	if (fragmentShader)
		glAttachShader(shaderPrg, fragmentShader);

	// links rthe program
	glLinkProgram(shaderPrg);

	// error handling
	printErrorMsg(shaderPrg, GL_LINK_STATUS);

	return shaderPrg;
}

GLuint AKY_compileAndLinkShaders(const char *vertexSource,
				 const char *geometrySource,
				 const char *fragmentSource)
{
	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;

	// tests if the shaders actually exist and compiles them
	if (vertexSource)
		vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
	if (geometrySource)
		geometryShader =
			compileShader(GL_GEOMETRY_SHADER, geometrySource);
	if (fragmentSource)
		fragmentShader =
			compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	// actually creates the program
	GLuint shaderPrg =
		linkShaders(vertexShader, geometryShader, fragmentShader);

	// tests if the shaders actually exist and eletes them
	if (vertexShader)
		glDeleteShader(vertexShader);
	if (geometryShader)
		glDeleteShader(geometryShader);
	if (fragmentShader)
		glDeleteShader(fragmentShader);

	return shaderPrg;
}
