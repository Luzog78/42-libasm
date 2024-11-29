/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:25:52 by ysabik            #+#    #+#             */
/*   Updated: 2024/11/29 16:32:16 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#ifndef BONUS
# define BONUS 1
#endif
#include "libasm.h"


/* ************************************************************************** */
/*                                 list utils                                 */
/* ************************************************************************** */


t_list	*t_list_new(void *data) {
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->data = data;
	new->next = NULL;
	return (new);
}

void	t_list_free(t_list *list) {
	t_list	*tmp;

	while (list) {
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void	t_list_print(t_list *list) {
	printf("| ");
	while (list) {
		printf("%s -> ", (char *)list->data);
		list = list->next;
	}
	printf("NULL\n");
}


/* ************************************************************************** */
/*                                ft_atoi_base                                */
/* ************************************************************************** */


#define T_ATOI_BASE \
	printf("Interpret: \"%s\" [%s]\n", str, base); \
	ret = ft_atoi_base(str, base); \
	printf("Number found: %d\n", ret); \
	printf("Errno: %d\n\n", errno);

void t_atoi_base() {
	char	*str;
	char	*base;
	int		ret;

	/* =============================== Test 1 =============================== */
	str = "   \t \t \v   +++--+-000945105";
	base = "0123456789";

	T_ATOI_BASE

	/* =============================== Test 2 =============================== */
	str = "2147483648";
	base = "0123456789";

	T_ATOI_BASE

	/* =============================== Test 3 =============================== */
	str = "fe";
	base = "0123456789abcdef";

	T_ATOI_BASE

	/* =============================== Test 4 =============================== */
	str = NULL;
	base = "01";

	T_ATOI_BASE

	/* =============================== Test 5 =============================== */
	str = "123";
	base = NULL;

	T_ATOI_BASE

	/* =============================== Test 6 =============================== */
	str = "123";
	base = "1";

	T_ATOI_BASE

	/* =============================== Test 7 =============================== */
	str = "123";
	base = "01234567890";

	T_ATOI_BASE

	/* =============================== Test 8 =============================== */
	str = "123";
	base = "0123456789-";

	T_ATOI_BASE

	/* =============================== Test 9 =============================== */
	str = "-0000000000101010";
	base = "01";

	T_ATOI_BASE
}


/* ************************************************************************** */
/*                             ft_list_push_front                             */
/* ************************************************************************** */


#define T_LIST_PUSH_FRONT \
	printf("List before: "); \
	t_list_print(list); \
	printf("Data to push: \"%s\" to %p\n", data, addr); \
	ft_list_push_front(addr, data); \
	printf("List after: "); \
	t_list_print(list); \
	t_list_free(list); \
	printf("Errno: %d\n\n", errno);

void t_list_push_front() {
	t_list	*list;
	t_list	**addr;
	char	*data;

	/* =============================== Test 1 =============================== */
	list = t_list_new("Hello");
	addr = &list;
	data = "World";

	T_LIST_PUSH_FRONT

	/* =============================== Test 2 =============================== */
	list = NULL;
	addr = &list;
	data = "Hi";

	T_LIST_PUSH_FRONT

	/* =============================== Test 3 =============================== */
	list = NULL;
	addr = &list;
	data = NULL;

	T_LIST_PUSH_FRONT

	/* =============================== Test 4 =============================== */
	list = t_list_new("A");
	list->next = t_list_new("B");
	addr = &list;
	data = "C";

	T_LIST_PUSH_FRONT

	/* =============================== Test 5 =============================== */
	list = t_list_new("Some element");
	addr = NULL;
	data = "Some data";

	T_LIST_PUSH_FRONT
}


/* ************************************************************************** */
/*                                    main                                    */
/* ************************************************************************** */


#define DELIM printf("================================\n\n");

int main() {
	t_atoi_base();
	DELIM
	t_list_push_front();
	return 0;
}
