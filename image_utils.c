/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 06:18:34 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/20 06:18:55 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

unsigned int	rgb_to_int(float red, float green, float blue)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	value;

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
			color = rgb_to_int(image->red[y][x], image->green[y][x],
					image->blue[y][x]);
			my_mlx_put_pixel(&mlx_image, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, mlx_image.img, 0, 0);
	mlx_destroy_image(mlx_ptr, mlx_image.img);
}