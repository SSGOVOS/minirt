#include "main.h"

float	**make_channel(void)
{
	float	**new;
	int		i;
	int		j;

	i = 0;
	new = malloc(sizeof(float *) * HEIGHT);
	while (i < HEIGHT)
	{
		new[i] = malloc(sizeof(float) * WIDTH);
		j = 0;
		while (j < WIDTH)
			new[i][j++] = 0.0f;
		i++;
	}
	return (new);
}

t_image	*new_image(void)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	image->red = make_channel();
	image->green = make_channel();
	image->blue = make_channel();
	return (image);
}

t_data	new_mlx_image(void *mlx_ptr)
{
	t_data	image;

	image.img = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	return (image);
}

void	my_mlx_put_pixel(t_data *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	set_pixel(int x, int y, t_vec3 *color, t_image *image)
{
	image->red[y][x] = color->x;
	image->green[y][x] = color->y;
	image->blue[y][x] = color->z;
}

unsigned int	rgb_to_int(float red, float green, float blue)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	value;

	// protect color overflow beyond 255
	if (red > 1)
		red = 1;
	if (green > 1)
		green = 1;
	if (blue > 1)
		blue = 1;
	r = (red) * 255.0;
	g = (green) * 255.0;
	b = (blue) * 255.0;
	value = (r << 16) | (g << 8) | b;
	return (value);
}

void	render(t_image *image, void *mlx_ptr, void *win_ptr)
{
	t_data			mlx_image;
	unsigned int	color;
	int				x;
	int				y;

	mlx_image = new_mlx_image(mlx_ptr);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = rgb_to_int(image->red[y][x],
					image->green[y][x], image->blue[y][x]);
			my_mlx_put_pixel(&mlx_image, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, mlx_image.img, 0, 0);
	mlx_destroy_image(mlx_ptr, mlx_image.img);
}


