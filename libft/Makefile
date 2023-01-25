#########################
#    BASIC VARIABLES    #
#########################

NAME		:=	libft.a

CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror
INCFLAGS	=	-I $(D_INCS)

AR			:=	ar
ARFLAGS	:=	rc

RM			:=	rm -rf

#############################
#         FILE TREE         #
#############################

# files

LST_CHAROPS	:=	ft_isalnum.c		ft_isalpha.c		ft_isascii.c	\
				ft_isdigit.c		ft_isprint.c		ft_tolower.c	\
				ft_toupper.c

LST_PRINTF	:=	ft_print_bighex.c		ft_print_char.c		ft_print_decimal.c	\
				ft_print_integer.c		ft_print_pointer.c	ft_print_pointer.c	\
				ft_print_smallhex.c		ft_print_string.c	ft_print_unsigned.c	\
				ft_printf_search_type.c		ft_printf.c

LST_GNL		:=	get_next_line.c		get_next_line_utils.c

LST_LINKED_LISTS	:=	ft_lstadd_back.c	ft_lstadd_front.c	ft_lstclear.c	\
						ft_lstdelone.c		ft_lstiter.c		ft_lstmap.c		\
						ft_lstnew.c			ft_lstsize.c		ft_lstlast.c

LST_MEMOPS	:=	ft_bzero.c		ft_calloc.c		ft_memchr.c		\
				ft_memcmp.c		ft_memcpy.c		ft_memmove.c	\
				ft_memset.c

LST_PRINTERS		:=	ft_putchar_fd.c		ft_putendl_fd.c		ft_putnbr_fd.c	\
						ft_putstr_fd.c

LST_STROPS	:=	ft_atoi.c		ft_itoa.c		ft_split.c		\
				ft_strchr.c		ft_strcmp.c		ft_strdup.c		\
				ft_striteri.c	ft_strjoin.c	ft_strlcat.c	\
				ft_strlcpy.c	ft_strlen.c		ft_strlcat.c	\
				ft_strlcpy.c	ft_strlen.c		ft_strmapi.c	\
				ft_strncmp.c	ft_strnstr.c	ft_strrchr.c	\
				ft_strtrim.c	ft_substr.c

LST_MISC	:=	ft_nbrlen.c		ft_putchar.c	ft_putstr.c

LST_INCS	:=	libft.h
LST_OBJS	=	$(SRCS:.c=.o)

# directories

D_SRCS	:=	sources/
D_INCS	:=	includes/
D_OBJS	:=	.objs/

D_CHAROPS	:=	char_operations/
D_PRINTF	:=	ft_printf/
D_GNL		:=	get_next_line/
D_LINKED_LISTS	:=	linked_lists/
D_MEMOPS	:=	memory_operations/
D_PRINTERS	:=	printers/
D_STROPS	:=	string_operations/
D_MISC		:=	misc_functions/

# full paths

SRCS	=	$(addprefix $(D_SRCS)$(D_CHAROPS),$(LST_CHAROPS))	\
			$(addprefix $(D_SRCS)$(D_PRINTF),$(LST_PRINTF))	\
			$(addprefix $(D_SRCS)$(D_GNL),$(LST_GNL))	\
			$(addprefix $(D_SRCS)$(D_LINKED_LISTS),$(LST_LINKED_LISTS))	\
			$(addprefix $(D_SRCS)$(D_MEMOPS),$(LST_MEMOPS))	\
			$(addprefix $(D_SRCS)$(D_PRINTERS),$(LST_PRINTERS))	\
			$(addprefix $(D_SRCS)$(D_STROPS),$(LST_STROPS))	\
			$(addprefix $(D_SRCS)$(D_MISC),$(LST_MISC))
INCS	=	$(addprefix $(D_INCS),$(LST_INCS))
OBJS	=	$(subst $(D_SRCS),$(D_OBJS),$(LST_OBJS))


#####################
#       RULES       #
#####################

all	:	$(NAME)

$(NAME)	:	$(OBJS) $(INCS) Makefile
			$(AR) $(ARFLAGS) $@ $(OBJS)

$(D_OBJS)%.o	:	$(D_SRCS)%.c $(INCS) Makefile | $(D_OBJS)
					$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(D_OBJS)	:
				mkdir -p $(D_OBJS)	\
				$(D_OBJS)$(D_CHAROPS)		$(D_OBJS)$(D_PRINTF)	$(D_OBJS)$(D_GNL)		\
				$(D_OBJS)$(D_LINKED_LISTS)	$(D_OBJS)$(D_MEMOPS)	$(D_OBJS)$(D_PRINTERS)	\
				$(D_OBJS)$(D_STROPS)		$(D_OBJS)$(D_MISC)

# mandatory rules

clean	:
			$(RM) $(OBJS)
			$(RM) $(D_OBJS)

fclean	:
			$(MAKE) clean
			$(RM) $(NAME)

re	:
			$(MAKE) fclean
			$(MAKE) all

.PHONY	: all clean fclean re
