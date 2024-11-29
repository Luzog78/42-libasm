/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:26:02 by ysabik            #+#    #+#             */
/*   Updated: 2024/11/30 00:35:38 by ysabik           ###   ########.fr       */
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
extern size_t	ft_list_size(t_list *lst);
/**
 * @brief Sorts the list using the cmp function.
 *
 * @param lst 	The address of list's head.
 * @param cmp 	The comparison function.
 * 					|| Parameters: (void *a, void *b)
 * 					|| [< 0]: a then b, [== 0]: a equals b, [> 0]: b then a
 */
extern void		ft_list_sort(t_list **lst, int (*cmp)());
/**
 * @brief Removes all elements from the list that are equal to ref_data.
 *
 * @param lst 		The address of list's head.
 * @param ref_data 	The reference data.
 * @param cmp 		The comparison function.
 * 						|| Parameters: (void *a, void *b)
 * 						|| [< 0]: a then b, [== 0]: a equals b, [> 0]: b then a
 * @param free_fct 	The function to free the data: free_fct(lst->data).
 * 						|| Parameters: (void *data)
 */
extern void		ft_list_remove_if(t_list **lst, void *ref_data,
									int (*cmp)(), void (*free_fct)(void *));

# endif

#endif
