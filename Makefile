################################
#        BASIC VARIABLES       #
################################

CSAN	:=	-fsanitize=address -g3

NAME	:=	cub3D
CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror #$(CSAN)

ARLIBFT	=	$(D_LIBFT)/libft.a

RM		:=	rm -rf

######################
#      FILE TREE     #
######################

# files

LST_PARSING		:=		parsing.c

LST_EXEC		:=

LST_MISC		:=		free_fct.c

LST_MAIN		:=		main.c


LST_INCS		:=		cub3D.h
LST_OBJS		:=		$(SRCS:.c=.o)

# directories

D_LIBFT		:=	libft/

D_SRCS		:=	sources/
D_INCS		:=	includes/
D_OBJS		:=	.objs/

D_PARSING	:=	parsing/
D_EXEC		:=	exec/
D_MISC		:=	miscs/

# full paths

SRCS	=	$(addprefix $(D_SRCS),$(LST_MAIN))
			$(addprefix $(D_SRCS)$(D_PARSING),$(LST_PARSING))
			$(addprefix $(D_SRCS)$(EXEC),$(LST_EXEC))
			$(addprefix $(D_SRCS)$(MISC),$(LST_MISC))

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
			$(D_OBJS)$(D_PARSING) $(D_OBJS)$(D_EXEC)

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
