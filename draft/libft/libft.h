/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeandel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:32:12 by ajeandel          #+#    #+#             */
/*   Updated: 2024/02/29 14:23:49 by ajeandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

typedef struct v_list
{
	char			*content;
	struct v_list	*next;
}		t_lis;

unsigned int	ft_strlcat(char *dest, char const *src, unsigned int size);
unsigned int	ft_strlcpy(char *dest, char const *src, unsigned int size);

t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*d)(void *));


void			dealloc(t_lis **list, t_lis *clean, char *buf);
void			*ft_calloc(size_t nitems, size_t size);
void			ft_putchar(char c);
void			ft_putnbr_base(unsigned long long nbr2, char *base);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_bzero(void *str, unsigned int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			*ft_memcpy(void *dest, const void *src, unsigned int n);
void			*ft_memmove(void *dest, const void *src, unsigned int n);
void			*ft_calloc(size_t nitems, size_t size);
void			*ft_memset(void *str, int c, unsigned int n);
void			*ft_memchr(const void *s, int c, unsigned int n);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *src);
char			*ft_strnstr(char const *big, char const *l, unsigned int n);
char			*ft_strrchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_itoa(int n);
char			*get_line(t_lis *stash, int i, int j);
char			*get_next_line(int fd);
int				newline(t_lis *stash);
int				malloc_line(t_lis *stash);
int				ft_hex_len(unsigned int num);
int				ft_print_hex(unsigned int num);
int				ft_print_hexmaj(unsigned int num);
int				ft_print_pointeur(void	*adr);
int				ft_print_int(int args);
int				ft_print_string(char *str);
int				ft_print_char(char c);
int				ft_print_prcent(void);
int				ft_print_unsigned_int(unsigned int x);
int				ft_printf(const char *str, ...);
int				ft_strlen(const char *str);
int				ft_putnbr_len(unsigned long long nbr, char *base);
int				ft_lstsize(t_list *lst);
int				ft_atoi(char const *str);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isascii(int c);
int				ft_strlen(const char *str);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_strncmp(char const *s1, char const *s2, unsigned int n);
int				ft_memcmp(const void *str1, const void *str2, unsigned int n);

#endif
