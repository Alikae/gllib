#define STB_IMAGE_IMPLEMENTATION
#include "gllib.h"

typedef struct	s_obj
{
	float	x;
	float	y;
	void	*sprite;
	float	sprite_x;
	float	sprite_y;
}		t_obj;

int main(int ac, char **av)
{
	t_obj	robert;
	int	sprites[10];

	create_graphics_interface();

	sprites[0] = create_sprite("textures/texture1.jpg");
	robert.sprite = sprites[0];
	add_to_vbo(1, 1, sprites[0]);
	//draw_sprite_to_framebuffer(x, y, rot, scale, sprites[0]);
	draw_world();
	while (1);
	destroy_graphics_interface();
	return (0);
}
