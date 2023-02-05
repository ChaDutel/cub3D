/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:46:26 by maxperei          #+#    #+#             */
/*   Updated: 2023/02/05 12:38:02 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <math.h>

/////////////////////////////////////////////////////////////////////////
////////////                   CUSTOM TYPES               ///////////////
/////////////////////////////////////////////////////////////////////////

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/////////////////////////////////////////////////////////////////////////.
////////////////          CHAR OPERATIONS            ////////////////////
/////////////////////////////////////////////////////////////////////////

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

/////////////////////////////////////////////////////////////////////////
///////////////// .     STRING OPERATIONS            ////////////////////
/////////////////////////////////////////////////////////////////////////

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strdup(const char *s1);

//////////////////////////////////////////////////////////////////////////
//////////////////           MEMORY OPERATIONS          //////////////////
//////////////////////////////////////////////////////////////////////////

void	*ft_memset(void *b, int c, size_t len);
void	*ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
//void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);

/////////////////////////////////////////////////////////////////////////
/////////////                  PRINTERS                 /////////////////
/////////////////////////////////////////////////////////////////////////

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

///////////////////////////////////////////////////////////////////////////
/////////////////////          LINKED LISTS            ////////////////////
///////////////////////////////////////////////////////////////////////////

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//////////////////////////////////////////////////////////////////////////
//////////////                GET_NEXT_LINE            //////////////////
/////////////////////////////////////////////////////////////////////////

# ifndef  BUFFER_SIZE
#  define   BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_n(char *line, char *buf);

///////////////////////////////////////////////////////////////////////////
/////////////                    FT_PRINTF                  ///////////////
///////////////////////////////////////////////////////////////////////////

int		ft_printf(const char *fmt, ...);
int		ft_search_type(va_list ap, const char *fmt);

int		ft_print_char(va_list ap);
int		ft_print_string(va_list ap);
int		ft_print_pointer(va_list ap);
int		ft_print_decimal(va_list ap);
int		ft_print_integer(va_list ap);
int		ft_print_unsigned(va_list ap);
int		ft_print_smallhex(va_list ap);
int		ft_print_bighex(va_list ap);

/////////////////////////////////////////////////////////////////////////
///////// .                      MISC                        ////////////
/////////////////////////////////////////////////////////////////////////

void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_nbrlen(int nbr);

#endif
