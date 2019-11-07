#include "gllib.h"

t_graphics_interface	*p_gfx(void)
{
	//singleton who stock graphics_interface params
	static t_graphics_interface	*interface = 0;

	if (!interface)
		if (!(interface = (t_graphics_interface*)malloc(sizeof(t_graphics_interface))))
			exit(1);
	return (interface);
}

void	draw_sprite_to_framebuffer(float x, float y, int theta_rot, int scale, int sprite)
{
	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void	create_graphics_interface()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	if (!(p_gfx()->window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL)))
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(p_gfx()->window);
	//glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(p_gfx()->window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return ;
	}
	p_gfx()->shader = create_shader("shaders/shader.vert", "shaders/shader.frag");
	p_gfx()->vbo_world_occupation = 1;
	 glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
}

int	create_sprite(const char *name)
{
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(1); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(name, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		printf("Failed to load texture\n");
	stbi_image_free(data);
}

void	draw_world()
{
	glBindBuffer(GL_ARRAY_BUFFER, p_gfx()->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, p_gfx()->vbo_world_occupation * 20, p_gfx()->vbo_world);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, p_gfx()->vbo_world_occupation * 4, p_gfx()->veo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glUseProgram(p_gfx()->shader);
	glUniform1i(glGetUniformLocation(p_gfx()->shader, "texture1"), 0);
}

void	add_to_vbo(float x, float y, float tex)
{
	int	pos = p_gfx()->vbo_world_occupation;
	int	vbo_size = 20;/*TO UPDATE*/

	p_gfx()->vbo_world[pos * vbo_size] = x;
	p_gfx()->vbo_world[pos * vbo_size + 1] = y;
	p_gfx()->vbo_world[pos * vbo_size + 2] = 0.0f;
	p_gfx()->vbo_world[pos * vbo_size + 3] = 0.0f;
	p_gfx()->vbo_world[pos * vbo_size + 4] = tex;

	p_gfx()->vbo_world[pos * vbo_size + 5] = x + 1;
	p_gfx()->vbo_world[pos * vbo_size + 6] = y;
	p_gfx()->vbo_world[pos * vbo_size + 7] = 1.0f;
	p_gfx()->vbo_world[pos * vbo_size + 8] = 0.0f;
	p_gfx()->vbo_world[pos * vbo_size + 9] = tex;

	p_gfx()->vbo_world[pos * vbo_size + 10] = x + 1;
	p_gfx()->vbo_world[pos * vbo_size + 11] = y + 1;
	p_gfx()->vbo_world[pos * vbo_size + 12] = 1.0f;
	p_gfx()->vbo_world[pos * vbo_size + 13] = 1.0f;
	p_gfx()->vbo_world[pos * vbo_size + 14] = tex;

	p_gfx()->vbo_world[pos * vbo_size + 15] = x;
	p_gfx()->vbo_world[pos * vbo_size + 16] = y + 1;
	p_gfx()->vbo_world[pos * vbo_size + 17] = 0.0f;
	p_gfx()->vbo_world[pos * vbo_size + 18] = 1.0f;
	p_gfx()->vbo_world[pos * vbo_size + 19] = tex;

	p_gfx()->veo[pos * 4] = 0;
	p_gfx()->veo[pos * 4 + 1] = 1;
	p_gfx()->veo[pos * 4 + 2] = 2;
	p_gfx()->veo[pos * 4 + 3] = 0;
	p_gfx()->veo[pos * 4 + 4] = 2;
	p_gfx()->veo[pos * 4 + 5] = 3;

	p_gfx()->vbo_world_occupation++;
}

//VBO EXIST
//ADD OBJECT ADD VERTICES TO VBO, NB_ELEMENTS EBO


/*void	render_sprite(int x, int y, int rot, int scale, int sprite)
{
	float	vbo[12] = {x, }
}*/

void	destroy_graphics_interface()
{
	glfwTerminate();
	free(p_gfx());
}
