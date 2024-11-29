/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:26:02 by ysabik            #+#    #+#             */
/*   Updated: 2024/11/29 16:06:57 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H

# ifndef size_t
#  define size_t unsigned long
# endif

# ifndef ssize_t
#  define ssize_t signed long
# endif

extern size_t	ft_strlen(const char *s);
extern char		*ft_strcpy(char *dst, const char *src);
extern char		*ft_strdup(const char *s);
extern int		ft_strcmp(const char *s1, const char *s2);
extern ssize_t	ft_read(int fd, const void *buf, size_t count);
extern ssize_t	ft_write(int fd, const void *buf, size_t count);

# ifndef BONUS
#  define BONUS 0
# else

typedef struct		s_list {
	void			*data;
	struct s_list	*next;
}	t_list;

extern int		ft_atoi_base(const void *str, const void *base);
extern void		ft_list_push_front(t_list **lst, void *data);

# endif

#endif
