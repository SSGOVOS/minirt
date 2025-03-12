/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:31:45 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/12 03:03:31 by amoubine         ###   ########.fr       */
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
# define WIDTH 1280
# define HEIGHT 720
# define EPSILON 1e-21f
# define  BACKWARD 0
# define  FORWARD 1

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
	t_vec3	origin; // parse *
	t_vec3	lookat; // parse *
	t_vec3	camera_w; // forward unit vector of the camera
	t_vec3	camera_u; // right unit vector of the camera
	t_vec3	camera_v; // up unit vector of the camera
	t_vec3	screen_center; // center of the screen facing the camera
	float	fov; // fov parse in degree *
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
	int			type; // *
	t_vec3		base_color; //* 
	float		radius; // only used in sphere *
	t_vec3		translation; // *
	t_vec3		rotation;
	t_vec3		scale;
	float		height;
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
	int obj_count;
	t_object* objects;
	t_light* lights;
}	t_vars;

//parse_structs ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef enum e_type
{
	SPHERE_PARSE,
	PLANE_PARSE,
	CYLINDER_PARSE,
}	t_type;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct t_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray_parse;

typedef struct s_ambient
{
	double	lighting;
	t_color	color;
}	t_ambient;

typedef struct t_light
{
	t_vector	position;
	t_color		color;
	double		brightness;
}	t_light_parse;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct t_camera
{
	t_vector	position;
	t_vector	orientation;
	double		fov;
}	t_camera_parse;

typedef struct t_object
{
	t_type		type;
	void		*object;
	t_color		color;
	t_vector	position;
	t_object	*next;
}	t_object_parse;

typedef struct s_rt
{
	void		*mlx;
	void		*win;
	int			file_fd;
	int			object_count;
	char		*file;
	t_ambient	ambient;
	t_camera_parse	camera;
	t_img		img;
	t_light		light;
	t_object_parse	*object;
}	t_rt;

// vectors
float dot_product(t_vec3 a, t_vec3 b);
t_vec3 cross_product(t_vec3 a, t_vec3 b);
float	length(t_vec3 a);
t_vec3 scale_vector(t_vec3 vec, float t);
t_vec3 normalize(t_vec3 vec);
void	print_vector(t_vec3 a);
t_vec3 vec_sub(t_vec3 a, t_vec3 b);
t_vec3 vec_add(t_vec3 a, t_vec3 b);
t_vec3	get_rotation_vector(t_vec3 normal);
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

// cylinder
float	get_min(float *t, int *min_index, int size);
int	calculate_props(int min_index, t_vec3 *poi, t_info *info, t_vec3 *vhat);
int	test_cylinder(t_ray *ray, t_info *info);


//parse_functions --------------------------------------------------------------------------------------------------------------------------

void			ft_add_back(t_object **list, t_object *new, int type);
int				check_file(t_rt *rt);
void			list_objects(t_rt *rt);
int				arg_error(char *msg);
int				is_rt_file(char *path);
int				destroy(t_rt *rt);
void			open_file(t_rt *rt, char *path);
void			free_objects(t_object *object);
int				main(int ac, char **av);
int				parse(t_rt *rt);
double			atoi_double(char *str);
void			free_array(char *arr[]);
int				array_length(char **arr);
void			parsing_error(char *msg);
int				is_float(const char *c);
int				check_range(char *line, int count, const int range[2]);
void			set_direction(char *line, t_vector *directions);
void			set_rgb(char *line, t_color *colors);
int				parse_sphere(t_rt *rt, char *line);
void			set_sphere(char **line, t_object **object);
int				parse_plane(t_rt *rt, char *line);
void			set_plane(char **line, t_object **object);
int				parse_cylinder(t_rt *rt, char *line);
void			set_cylinder(char **line, t_object **object);
int				parse_ambient(t_rt *rt, char *line);
void			set_ambient(char **line, t_ambient *ambient);
int				parse_camera(t_rt *rt, char *line);
void			set_camera(char **line, t_camera *camera);

// Debugging functions
// void			show_sphere(t_sphere *sphere);
// void			show_plane(t_object *object);
// void			show_cylinder(t_object *object);
// void			list_objects(t_rt *rt);

#endif