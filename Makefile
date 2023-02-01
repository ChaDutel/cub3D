################################
#        BASIC VARIABLES       #
################################

CSAN	:=	-fsanitize=address -g3

NAME	:=	cub3D
CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror $(CSAN)

AR_LIBFT	=	$(D_LIBFT)libft.a

RM		:=	rm -rf

######################
#      FILE TREE     #
######################

# files

LST_PARSING		:=		parsing.c			\
						pre_parsing.c		\
						pre_parsing_utils.c

LST_EXEC		:=

LST_MISCS		:=		error_handling.c

LST_MAIN		:=		main.c


LST_INCS		:=		cub3D.h
LST_OBJS		=		$(SRCS:.c=.o)

# directories

D_LIBFT		:=	libft/

D_SRCS		:=	sources/
D_INCS		:=	includes/
D_OBJS		:=	.objs/

D_PARSING	:=	parsing/
D_EXEC		:=	exec/
D_MISCS		:=	miscs/

# full paths

SRCS	=	$(addprefix $(D_SRCS),$(LST_MAIN))					\
			$(addprefix $(D_SRCS)$(D_MISCS),$(LST_MISCS))		\
			$(addprefix $(D_SRCS)$(D_PARSING),$(LST_PARSING))	\
			$(addprefix $(D_SRCS)$(D_EXEC),$(LST_EXEC))			

INCS	=	$(addprefix $(D_INCS),$(LST_INCS))

OBJS	=	$(subst $(D_SRCS),$(D_OBJS),$(LST_OBJS))

#######################
#        RULES        #
#######################

all		:	makelibft $(NAME)

$(NAME)	:	$(OBJS) $(AR_LIBFT) $(INCS) Makefile
			$(CC) $(CFLAGS) $(AR_LIBFT) $(OBJS) -o $@

$(D_OBJS)%.o	:	$(D_SRCS)%.c $(INCS) $(AR_LIBFT) Makefile | $(D_OBJS)
					$(CC) $(CFLAGS) -c $< -o $@

$(D_OBJS)	:
			mkdir -p $(D_OBJS)		\
			$(D_OBJS)$(D_PARSING) $(D_OBJS)$(D_EXEC) $(D_OBJS)$(D_MISCS)

$(AR_LIBFT)	:
				$(MAKE) -C $(D_LIBFT)

makelibft	:
			$(MAKE) -C $(D_LIBFT)

clean	:
		$(RM) $(OBJS)
		$(RM) $(D_OBJS)

fclean	:
		$(MAKE) clean
		$(RM) $(NAME)
		$(MAKE) fclean -C $(D_LIBFT)

re	:
	$(MAKE) fclean
	$(MAKE) all

.PHONY:	all clean fclean re makelibft
