/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 06:16:31 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/20 06:22:49 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
