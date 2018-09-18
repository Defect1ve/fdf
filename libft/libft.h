/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 11:41:43 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/20 11:41:45 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <locale.h>
# include <stdarg.h>
# define BUFF 1
# define BUFF_SIZE 100
# define N_STR "(null)"
# define SIZE(c) (c < 128) ? 1 : ((c < 2048) ?  2 : ((c < 65536) ? 3 : 4))
# define LEN(c) (c < 256) ? ((c < 128) ? 1 : 2) : ft_str_len(&c, s, 'c')

size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *src);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *destptr, const char *srcptr);
char				*ft_strncat(char *destptr, char *srcptr, size_t num);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *string, int symbol);
char				*ft_strrchr(const char *string, int symbol);
char				*ft_strstr(const char *string1, const char *string2);
char				*ft_strnstr(const char *haystack,
const char *needle, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_atoi(const char *str);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
char				*ft_itoa(int n);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstbackadd(t_list **alst, t_list *new);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
char				*ft_strjoinfree(char **s1, char *s2);
typedef struct		s_gnl
{
	char			b[BUFF + 1];
	char			*p;
}					t_gnl;
int					get_next_line(const int fd, char **line);
typedef	struct		s_pf
{
	short	flags;
	int		prec;
	int		width;
	char	type;
	char	size[3];
	char	buf[BUFF_SIZE];
	int		i;
	int		sum;
	char	sign;
}					t_pf;
int					ft_printf(const char *format, ...);
void				ft_string(t_pf *s, va_list val);
void				ft_char(t_pf *s, va_list val);
void				ft_numb(t_pf *s, va_list val);
void				ft_buf_print(t_pf *s);
void				ft_manage_str(t_pf *s, int l);
void				ft_buf_add_str(t_pf *s, unsigned char *str);
void				ft_buf_add_numb(t_pf *s, unsigned char symbol);
void				ft_unicode(t_pf *s, int uni);
void				ft_manage_numb(t_pf *s, uintmax_t b, uintmax_t n);
void				ft_mng_nb1(t_pf *s, uintmax_t n);
void				ft_buf_add_char(t_pf *s, unsigned char c);
uintmax_t			ft_pow(uintmax_t b, uintmax_t p);
#endif
