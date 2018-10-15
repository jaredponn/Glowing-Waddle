#include "extern/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "program.h"


int main(void)
{
	struct PRG_Program p;

	PRG_init(&p);

	PRG_run(&p);

	return 0;
}
