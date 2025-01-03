/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:25:52 by ysabik            #+#    #+#             */
/*   Updated: 2024/11/30 00:21:24 by ysabik           ###   ########.fr       */
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

void	t_list_print(t_list *list, int str) {
	printf("| ");
	while (list) {
		if (str)
			printf("\"%s\" %p -> ", (char *) list->data, list->data);
		else
			printf("%lld -> ", (long long) list->data);
		list = list->next;
	}
	printf("NULL\n");
}

int	cmp1(void *a, void *b) {
	return ft_strcmp((char *) a, (char *) b);
}

int	cmp2(void *a, void *b) {
	return -ft_strcmp((char *) a, (char *) b);
}

int	cmp3(void *a, void *b) {
	return a > b;
}


/* ************************************************************************** */
/*                                ft_atoi_base                                */
/* ************************************************************************** */


#define T_ATOI_BASE \
	printf("Interpret: \"%s\" [%s]\n", str, base); \
	ret = ft_atoi_base(str, base); \
	printf("Number found: %d\n", ret); \
	printf("Errno: %d\n\n", errno); \
	errno = 0;

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
	t_list_print(list, 1); \
	printf("Data to push: \"%s\" to %p\n", data, addr); \
	ft_list_push_front(addr, data); \
	printf("List after: "); \
	t_list_print(list, 1); \
	t_list_free(list); \
	printf("Errno: %d\n\n", errno); \
	errno = 0;

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
/*                                ft_list_size                                */
/* ************************************************************************** */


#define T_LIST_SIZE \
	printf("List: "); \
	t_list_print(list, 1); \
	ret = ft_list_size(list); \
	printf("Size: %lu\n", ret); \
	t_list_free(list); \
	printf("Errno: %d\n\n", errno); \
	errno = 0;

void t_list_size() {
	t_list	*list;
	size_t	ret;

	/* =============================== Test 1 =============================== */
	list = t_list_new("Hello");

	T_LIST_SIZE

	/* =============================== Test 2 =============================== */
	list = NULL;

	T_LIST_SIZE

	/* =============================== Test 3 =============================== */
	list = t_list_new("A");
	list->next = t_list_new("B");
	list->next->next = t_list_new("C");
	list->next->next->next = t_list_new("D");
	list->next->next->next->next = t_list_new("E");
	list->next->next->next->next->next = t_list_new("F");

	T_LIST_SIZE
}


/* ************************************************************************** */
/*                                ft_list_sort                                */
/* ************************************************************************** */


#define T_LIST_SORT \
	printf("List: [%p] ", addr); \
	t_list_print(list, 1); \
	ft_list_sort(addr, func); \
	printf("Sorted (by %p): ", func); \
	t_list_print(list, 1); \
	t_list_free(list); \
	printf("Errno: %d\n\n", errno); \
	errno = 0;

#define LIST_INIT \
	ft_list_push_front(addr, "a"); \
	ft_list_push_front(addr, "c"); \
	ft_list_push_front(addr, "f"); \
	ft_list_push_front(addr, "d"); \
	ft_list_push_front(addr, "b"); \
	ft_list_push_front(addr, "e");

void t_list_sort() {
	t_list	*list;
	t_list	**addr;
	int		(*func)(void *, void *);

	/* =============================== Test 1 =============================== */
	list = NULL;
	addr = &list;
	func = cmp1;
	LIST_INIT

	T_LIST_SORT

	/* =============================== Test 2 =============================== */
	list = NULL;
	addr = &list;
	func = cmp2;
	LIST_INIT

	T_LIST_SORT

	/* =============================== Test 3 =============================== */
	list = NULL;
	addr = &list;
	func = cmp3;
	LIST_INIT

	T_LIST_SORT

	/* =============================== Test 4 =============================== */
	list = NULL;
	addr = &list;
	func = cmp1;

	T_LIST_SORT

	/* =============================== Test 5 =============================== */
	list = NULL;
	addr = NULL;
	func = cmp1;

	T_LIST_SORT

	/* =============================== Test 6 =============================== */
	list = t_list_new("a");
	addr = &list;
	func = cmp1;

	T_LIST_SORT

	/* =============================== Test 7 =============================== */
	list = t_list_new("a");
	addr = &list;
	func = NULL;

	T_LIST_SORT
}


/* ************************************************************************** */
/*                             ft_list_remove_if                              */
/* ************************************************************************** */


#define T_LIST_REMOVE_IF \
	printf("List: [%p] ", addr); \
	t_list_print(list, str_format); \
	if (str_format) \
		printf("Data reference: \"%s\" [%p] (comp:%p free:%p)\n", \
			(char *) data, data, func, ffunc); \
	else \
		printf("Data reference: %lld (comp:%p free:%p)\n", \
			(long long) data, func, ffunc); \
	ft_list_remove_if(addr, data, func, ffunc); \
	printf("List after: "); \
	t_list_print(list, str_format); \
	t_list_free(list); \
	printf("Errno: %d\n\n", errno); \
	errno = 0;

void t_list_remove_if() {
	t_list	*list;
	t_list	**addr;
	void	*data;
	int		(*func)(void *, void *);
	void	(*ffunc)(void *);
	int		str_format;

	/* =============================== Test 1 =============================== */
	list = NULL;
	addr = &list;
	data = "a";
	func = cmp1;
	ffunc = free;
	str_format = 1;
	ft_list_push_front(addr, "c");
	ft_list_push_front(addr, "b");
	ft_list_push_front(addr, ft_strdup("a"));

	T_LIST_REMOVE_IF

	/* =============================== Test 2 =============================== */
	list = NULL;
	addr = &list;
	data = "b";
	func = cmp1;
	ffunc = free;
	str_format = 1;
	ft_list_push_front(addr, "c");
	ft_list_push_front(addr, "c");
	ft_list_push_front(addr, "c");
	ft_list_push_front(addr, ft_strdup("b"));
	ft_list_push_front(addr, ft_strdup("b"));
	ft_list_push_front(addr, ft_strdup("b"));
	ft_list_push_front(addr, "a");
	ft_list_push_front(addr, "a");
	ft_list_push_front(addr, "a");

	T_LIST_REMOVE_IF

	/* =============================== Test 3 =============================== */
	list = NULL;
	addr = &list;
	data = (void *) 2000;
	func = cmp3;
	ffunc = NULL;
	str_format = 0;
	ft_list_push_front(addr, (void *) 0);
	ft_list_push_front(addr, (void *) 123);
	ft_list_push_front(addr, (void *) 4096);
	ft_list_push_front(addr, (void *) 99999999);

	T_LIST_REMOVE_IF

	/* =============================== Test 4 =============================== */
	list = t_list_new("Hello World!");
	addr = &list;
	data = "Some value...";
	func = cmp1;
	ffunc = NULL;
	str_format = 1;

	T_LIST_REMOVE_IF

	/* =============================== Test 5 =============================== */
	list = t_list_new("Heyy");
	addr = &list;
	data = "Heyy";
	func = cmp1;
	ffunc = NULL;
	str_format = 1;

	T_LIST_REMOVE_IF

	/* =============================== Test 6 =============================== */
	list = t_list_new("Heyy");
	addr = NULL;
	data = "Heyy";
	func = cmp1;
	ffunc = NULL;
	str_format = 1;

	T_LIST_REMOVE_IF

	/* =============================== Test 7 =============================== */
	list = t_list_new("Heyy");
	addr = &list;
	data = "Heyy";
	func = NULL;
	ffunc = NULL;
	str_format = 1;

	T_LIST_REMOVE_IF

	/* =============================== Test 8 =============================== */
	list = NULL;
	addr = &list;
	data = "Heyy";
	func = cmp1;
	ffunc = NULL;
	str_format = 1;

	T_LIST_REMOVE_IF
}


/* ************************************************************************** */
/*                                    main                                    */
/* ************************************************************************** */


#define DELIM printf("================================\n\n");

int main() {
	t_atoi_base();
	DELIM
	t_list_push_front();
	DELIM
	t_list_size();
	DELIM
	t_list_sort();
	DELIM
	t_list_remove_if();
	return 0;
}
