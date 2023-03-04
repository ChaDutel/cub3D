################################
#        BASIC VARIABLES       #
################################

CSAN	:=	-fsanitize=address -g3

NAME	:=	cub3D
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror -Ofast -march=native #$(CSAN)

AR_LIBFT	=	$(D_LIBFT)libft.a

LIBFT_LIB	=	-L$(D_LIBFT) -lft

MLX_INCS	:=	-Imlx_linux
MLX_LIB		:=	-Lmlx_linux -lmlx_Linux -lXext -lX11 -lm

RM		:=	rm -rf

######################
#      FILE TREE     #
######################

# files

LST_PARSING		:=		parsing.c				\
						pre_parsing.c			\
						pre_parsing_utils.c		\
						split_config.c			\
						split_config_utils.c	\
						parse_elems.c			\
						parse_colors.c			\
						parse_map.c

LST_EVENTS		:=		events.c				\
						movement.c

LST_DISPLAY		:=		minimap_draw.c			\
						draw.c

LST_EXEC		:=		raycaster.c			\
						raycaster_utils.c

LST_MISCS		:=		error_handling.c	\
						free_memory.c		\
						libc_ft.c

LST_MAIN		:=		main.c				\
						init.c


LST_INCS		:=		cub3D.h
LST_OBJS		=		$(SRCS:.c=.o)

# directories

D_LIBFT		:=	libft/
D_MLX		:=	mlx_linux/

D_SRCS		:=	sources/
D_INCS		:=	includes/
D_OBJS		:=	.objs/

D_PARSING	:=	parsing/
D_EVENTS	:=	events/
D_DISPLAY	:=	display/
D_EXEC		:=	exec/
D_MISCS		:=	miscs/

# full paths

SRCS	=	$(addprefix $(D_SRCS),$(LST_MAIN))					\
			$(addprefix $(D_SRCS)$(D_PARSING),$(LST_PARSING))	\
			$(addprefix $(D_SRCS)$(D_EVENTS), $(LST_EVENTS))	\
			$(addprefix $(D_SRCS)$(D_DISPLAY), $(LST_DISPLAY))	\
			$(addprefix $(D_SRCS)$(D_EXEC),$(LST_EXEC))			\
			$(addprefix $(D_SRCS)$(D_MISCS),$(LST_MISCS))

INCS	=	$(addprefix $(D_INCS),$(LST_INCS))

OBJS	=	$(subst $(D_SRCS),$(D_OBJS),$(LST_OBJS))

#######################
#        RULES        #
#######################

all		:	make_libft make_mlx $(NAME)


$(NAME)	:	$(OBJS) $(AR_LIBFT) $(INCS) Makefile
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX_LIB) -o $@

$(D_OBJS)%.o	:	$(D_SRCS)%.c $(INCS) $(AR_LIBFT) Makefile | $(D_OBJS)
					$(CC) $(CFLAGS) -c $< -o $@

$(D_OBJS)	:
			mkdir -p $(D_OBJS)		\
			$(D_OBJS)$(D_PARSING)	\
			$(D_OBJS)$(D_EVENTS)	\
			$(D_OBJS)$(D_DISPLAY)	\
			$(D_OBJS)$(D_EXEC)		\
			$(D_OBJS)$(D_MISCS)

$(AR_LIBFT)	:
				$(MAKE) -C $(D_LIBFT)

make_libft	:
			$(MAKE) -C $(D_LIBFT)

make_mlx	:
			$(MAKE) -C $(D_MLX)

clean	:
		$(RM) $(OBJS)
		$(RM) $(O_BONUS)
		$(RM) $(D_OBJS)
		$(RM) $(D_OBONUS)

fclean	:
		$(MAKE) clean
		$(RM) $(NAME)
		$(MAKE) fclean -C $(D_LIBFT)
		$(MAKE) clean -C $(D_MLX)

re	:
	$(MAKE) fclean
	$(MAKE) all

.PHONY:	all clean fclean re makelibft bonus
