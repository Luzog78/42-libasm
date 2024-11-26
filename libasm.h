/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:26:02 by ysabik            #+#    #+#             */
/*   Updated: 2024/11/26 17:02:10 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H

# ifndef size_t
#  define size_t unsigned long
# endif

extern size_t	ft_strlen(char *str);
extern char		*ft_strcpy(char *dst, const char *src);

#endif
