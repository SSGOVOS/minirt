NAME = minirt

CFLAGS = -Wall -Wextra -Werror -O2 -g3 -g
LDFLAGS = -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

SRCS = main.c image.c image_utils.c intersec_utils.c\
		vectors.c vectors_2.c camera.c prepare_object.c\
		Objects/Sphere.c \
		Objects/Plane.c \
		Objects/Cylinder.c \
		Objects/Cylinder_utils.c \
		Transformation/Gtfm.c \
		Transformation/setup.c \
		Matrix/init.c \
		Matrix/matrix.c \
		Matrix/inverse.c \
		Matrix/minor.c \
		Matrix/multiplication.c \
		init_objects.c \
		Materials/Diffuse.c \

SRCS +=	parse/parsing/atoi_double.c \
		parse/parsing/file.c \
		parse/parsing/parse_objects.c \
		parse/parsing/parsing_utils.c \
		parse/parsing/parsing.c \
		parse/parsing/set_objects.c \
		parse/parsing/set_data.c \
		parse/parsing/parsing_utils_1.c
		

OBJS = $(SRCS:.c=.o)

LIBFT_A  = libft/libft.a

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

	
$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $(NAME)

$(LIBFT_A):
	make -C libft/

clean:
	rm -rf $(OBJS)
	make clean -C libft/

fclean : clean
	rm -rf $(NAME)
	make fclean -C libft/

re : fclean all

.PHONY: clean fclean all re
