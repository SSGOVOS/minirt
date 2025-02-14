NAME = minirt

CFLAGS = -Wall -Wextra -Werror -O2 -g3

SRCS = main.c image.c vectors.c camera.c\
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

OBJS = $(SRCS:.c=.o)


all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -c $< -o $@

	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

	
clean:
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: clean fclean all re