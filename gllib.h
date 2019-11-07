#ifndef GLLIB_H
# define GLLIB_H

# include "stb_image.h"

# include <glad/glad.h>
# include <GLFW/glfw3.h>

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct	s_graphics_interface
{
	GLFWwindow	*window;
	int		shader;
	float		vbo_world[20000];
	int		vbo_world_occupation;
	int		vao;
	int		vbo;
	int		veo;
}		t_graphics_interface;

//singleton who store params
t_graphics_interface	*p_gfx();

void			create_graphics_interface();
void			destroy_graphics_interface();
int			create_shader(const char *vertex_src, const char *fragment_src);
char			*read_file(const char *file_name);

#endif
