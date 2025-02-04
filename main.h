/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:31:45 by amoubine          #+#    #+#             */
/*   Updated: 2025/01/16 12:57:26 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <mlx.h>

# define M_PI 3.14159265358979323846
# define HALFPI 1.5708
# define FLT_MAX 3.40282346638528859811704183484516925e+38F
# define WIDTH 1920
# define HEIGHT 1080
# define EPSILON 1e-21f
# define  BONUS 1

typedef struct s_vec3
{
	float x;
	float y;
	float z;
}	t_vec3;


enum
{
	SPHERE,
	PLANE,
	CYLINDER
};

typedef struct s_matrix
{
	int		rows;
	int		cols;
	float	**matrix;
}	t_matrix;


typedef struct s_camera
{
	t_vec3	origin; // parse
	t_vec3	lookat; // parse
	t_vec3	camera_w; // forward unit vector of the camera
	t_vec3	camera_u; // right unit vector of the camera
	t_vec3	camera_v; // up unit vector of the camera
	t_vec3	screen_center; // center of the screen facing the camera
	float	fov; // fov parse in degree
	float	aspect_ratio; // aspect ratio of the screen (width / height)
	float	horizontal_size; // width of the screen
	t_vec3 screen_u; // right vector of screen center
	t_vec3 screen_v; // up vector of screen center
}	t_camera;

typedef struct s_ray
{
	t_vec3	point1; // origin
	t_vec3	point2; // dir
	t_vec3 dir; // dir normalized
}	t_ray;

typedef struct s_image 
{
	float **red;
	float **green;
	float **blue;
} t_image;


typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;




typedef struct s_info
{
	struct s_object	*e;
	t_vec3			hitpoint;
	t_vec3			localnormal;
}				t_info;

typedef struct s_object
{
	int			type;
	t_vec3		base_color;
	float		radius; // only used in sphere
	t_vec3		translation;
	t_vec3		rotation;
	t_vec3		scale;
	t_matrix** gtfm;
	t_vec3		d_normal; // used for plane and cylinder and cone
	int			(*intersect)(t_ray*, struct s_info *);
} t_object;

typedef struct s_light
{
	t_vec3	position;
	t_vec3	color;
	float	brightness;
}			t_light;

typedef struct s_vars
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_image			*image;
	t_camera		cam;
	t_vec3			*buffer; // stacking images , later
	unsigned int	rng_state;
	int				frames; // frames to stack for antialiasing (max 120)
	int obj_count;
	t_object* objects;
	t_light* lights;
}	t_vars;


// vectors
float dot_product(t_vec3 a, t_vec3 b);
t_vec3 cross_product(t_vec3 a, t_vec3 b);
float	length(t_vec3 a);
t_vec3 scale_vector(t_vec3 vec, float t);
t_vec3 normalize(t_vec3 vec);
void	print_vector(t_vec3 a);
t_vec3 vec_sub(t_vec3 a, t_vec3 b);
t_vec3 vec_add(t_vec3 a, t_vec3 b);
// camera
void setup_camera(t_camera *cam);
t_ray new_ray(t_vec3 point1, t_vec3 point2);
t_ray generate_ray(float x, float y, t_camera *cam);
// image utils
t_image	*new_image(void);
t_data	new_mlx_image(void *mlx_ptr);
void	set_pixel(int x, int y, t_vec3 *color, t_image *image);
unsigned int	rgb_to_int(float red, float green, float blue);
void	render(t_image *image, void *mlx_ptr, void *win_ptr);
// matrix
void	fill_mt(t_matrix *mt, float *values);
float	*create_cols(int c);
t_matrix	*create_matrix(int rows, int cols);
void	set_to_indentity(t_matrix *mt);
void	print_matrix(t_matrix *matrix);
t_matrix	*transpose(t_matrix *mt);
// matrix operations
t_matrix	*mt_multiplication(t_matrix *mt1, t_matrix *mt2);
t_matrix	*safe_matrix_multy(t_matrix *mt1, t_matrix *mt2);
float	determinant(t_matrix *mt);
float	cofactor(t_matrix *mt, int row, int column);
t_matrix	*inverse(t_matrix *mt);
t_matrix	*submatrix(t_matrix *mt, int row, int column);
float	minor(t_matrix *mt, int row, int column);
// matrix utils
t_matrix	*create_matrix(int rows, int cols);
void	delete_matrix(t_matrix *mt);
// gtfm stuff
t_matrix	*rotation_matrix_y(float angle);
t_matrix	*rotation_matrix_x(float angle);
t_matrix	*rotation_matrix_z(float angle);
t_matrix	*translation_matrix(t_vec3 *translation);
t_matrix	*scale_matrix(t_vec3 *scal);
t_matrix	**set_transform(t_vec3 *translation, t_vec3 *rotation, t_vec3 *scale);
t_vec3	apply_transform_vector(t_vec3 inputVector, int dirFlag, t_matrix **gtfm);
t_ray	apply_transform(t_ray *input_ray, t_matrix **gtfm, int dirFlag);
int test_sphere(t_ray * ray,  struct s_info *info);
int	test_plane(t_ray *ray, t_info *info);
void list_object(t_vars* vars);
// diffuse
t_vec3	diffuse_color(t_info *info, t_vars *vars, t_vec3 *base_color);
t_vec3	reflect(t_vec3 d, t_vec3 normal);
// specular
t_vec3	specular_highlight(t_vars *vars, t_info *info, t_ray *camera_ray);
#endif