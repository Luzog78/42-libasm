/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:25:52 by ysabik            #+#    #+#             */
/*   Updated: 2024/11/28 15:59:38 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "libasm.h"


void t_strlen() {
	char *str;
	size_t len;

	/* =============================== Test 1 =============================== */
	str = "Hello World!";
	len = ft_strlen(str);

	printf("Length of \"%s\" is %lu\n", str, len);
	printf("Errno: %d\n\n", errno);


	/* =============================== Test 2 =============================== */
	str = "";
	len = ft_strlen(str);

	printf("Length of \"%s\" is %lu\n", str, len);
	printf("Errno: %d\n\n", errno);


	/* =============================== Test 3 =============================== */
	str = NULL;
	len = ft_strlen(str);

	printf("Length of \"%s\" is %lu\n", str, len);
	printf("Errno: %d\n\n", errno);
}

void t_strcpy() {
	char *src;
	char *dst;

	/* =============================== Test 1 =============================== */
	src = "Hello World!";
	dst = calloc(ft_strlen(src) + 1, 1);
	ft_strcpy(dst, src);

	printf("String to copy: \"%s\"\n", src);
	printf("Copied string: \"%s\"\n", dst);
	printf("Errno: %d\n\n", errno);
	free(dst);

	
	/* =============================== Test 2 =============================== */
	src = "";
	dst = calloc(ft_strlen(src) + 1, 1);
	ft_strcpy(dst, src);
	
	printf("String to copy: \"%s\"\n", src);
	printf("Copied string: \"%s\"\n", dst);
	printf("Errno: %d\n\n", errno);
	free(dst);
	
	
	/* =============================== Test 3 =============================== */
	src = NULL;
	dst = calloc(ft_strlen(src) + 1, 1);
	ft_strcpy(dst, src);
	
	printf("String to copy: \"%s\"\n", src);
	printf("Copied string: \"%s\"\n", dst);
	printf("Errno: %d\n\n", errno);
	free(dst);
}

void t_strcmp() {
	char *s1;
	char *s2;

	/* =============================== Test 1 =============================== */
	s1 = "Hello World!";
	s2 = "Hello World!";

	printf("s1: \"%s\" | s2: \"%s\"  ==>  %d\n", s1, s2, ft_strcmp(s2, s1));
	printf("Errno: %d\n\n", errno);

	
	/* =============================== Test 2 =============================== */
	s1 = "abc";
	s2 = "aaa";

	printf("s1: \"%s\" | s2: \"%s\"  ==>  %d\n", s1, s2, ft_strcmp(s2, s1));
	printf("Errno: %d\n\n", errno);

	
	/* =============================== Test 3 =============================== */
	s1 = "abc";
	s2 = "abcdef";

	printf("s1: \"%s\" | s2: \"%s\"  ==>  %d\n", s1, s2, ft_strcmp(s2, s1));
	printf("Errno: %d\n\n", errno);
	
	
	/* =============================== Test 4 =============================== */
	s1 = "Hello World!";
	s2 = NULL;

	printf("s1: \"%s\" | s2: \"%s\"  ==>  %d\n", s1, s2, ft_strcmp(s2, s1));
	printf("Errno: %d\n\n", errno);
}

void t_strdup() {
	char *str;
	char *dup;

	/* =============================== Test 1 =============================== */
	str = "Hello World!";
	dup = ft_strdup(str);

	printf("Original string: \"%s\"\n", str);
	printf("Duplicated string: \"%s\"\n", dup);
	printf("Errno: %d\n\n", errno);
	free(dup);

	
	/* =============================== Test 2 =============================== */
	str = "";
	dup = ft_strdup(str);

	printf("Original string: \"%s\"\n", str);
	printf("Duplicated string: \"%s\"\n", dup);
	printf("Errno: %d\n\n", errno);
	free(dup);

	
	/* =============================== Test 3 =============================== */
	str = NULL;
	dup = ft_strdup(str);

	printf("Original string: \"%s\"\n", str);
	printf("Duplicated string: \"%s\"\n", dup);
	printf("Errno: %d\n\n", errno);
	free(dup);
}

int main() {
	t_strlen();
	printf("================================\n\n");
	t_strcpy();
	printf("================================\n\n");
	t_strcmp();
	printf("================================\n\n");
	t_strdup();
	return 0;
}
