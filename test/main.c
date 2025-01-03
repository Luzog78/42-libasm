/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:25:52 by ysabik            #+#    #+#             */
/*   Updated: 2024/11/29 12:07:58 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "libasm.h"


/* ************************************************************************** */
/*                                  ft_strlen                                 */
/* ************************************************************************** */


#define T_STRLEN \
	len = ft_strlen(str); \
	printf("Length of \"%s\" is %lu\n", str, len); \
	printf("Errno: %d\n\n", errno);

void t_strlen() {
	char	*str;
	size_t	len;

	/* =============================== Test 1 =============================== */
	str = "Hello World!";

	T_STRLEN

	/* =============================== Test 2 =============================== */
	str = "";

	T_STRLEN

	/* =============================== Test 3 =============================== */
	str = NULL;

	T_STRLEN
}


/* ************************************************************************** */
/*                                  ft_strcpy                                 */
/* ************************************************************************** */


#define T_STRCPY \
	dst = calloc(ft_strlen(src) + 1, 1); \
	ft_strcpy(dst, src); \
	printf("String to copy: \"%s\"\n", src); \
	printf("Copied string: \"%s\"\n", dst); \
	printf("Errno: %d\n\n", errno); \
	free(dst);

void t_strcpy() {
	char	*src;
	char	*dst;

	/* =============================== Test 1 =============================== */
	src = "Hello World!";

	T_STRCPY

	/* =============================== Test 2 =============================== */
	src = "";

	T_STRCPY

	/* =============================== Test 3 =============================== */
	src = NULL;

	T_STRCPY
}


/* ************************************************************************** */
/*                                  ft_strcmp                                 */
/* ************************************************************************** */


#define T_STRCMP \
	ret = ft_strcmp(s1, s2); \
	printf("s1: \"%s\" | s2: \"%s\"  ==>  %d\n", s1, s2, ret); \
	printf("Errno: %d\n\n", errno); \

void t_strcmp() {
	char	*s1;
	char	*s2;
	int		ret;

	/* =============================== Test 1 =============================== */
	s1 = "Hello World!";
	s2 = "Hello World!";

	T_STRCMP

	/* =============================== Test 2 =============================== */
	s1 = "abc";
	s2 = "aaa";

	T_STRCMP

	/* =============================== Test 3 =============================== */
	s1 = "abc";
	s2 = "abcdef";

	T_STRCMP

	/* =============================== Test 4 =============================== */
	s1 = "Hello World!";
	s2 = NULL;

	T_STRCMP
}


/* ************************************************************************** */
/*                                  ft_strdup                                 */
/* ************************************************************************** */


#define T_STRDUP \
	dup = ft_strdup(str); \
	printf("Original string: \"%s\"\n", str); \
	printf("Duplicated string: \"%s\"\n", dup); \
	printf("Errno: %d\n\n", errno); \
	free(dup);

void t_strdup() {
	char	*str;
	char	*dup;

	/* =============================== Test 1 =============================== */
	str = "Hello World!";

	T_STRDUP

	/* =============================== Test 2 =============================== */
	str = "";

	T_STRDUP

	/* =============================== Test 3 =============================== */
	str = NULL;

	T_STRDUP
}


/* ************************************************************************** */
/*                                  ft_write                                  */
/* ************************************************************************** */


#define T_WRITE \
	ret = ft_write(fd, buf, count); \
	printf("\nString to write: \"%s\"\n", buf); \
	printf("Bytes to write: %lu  |  on fd: %d\n", count, fd); \
	printf("Bytes written: %ld\n", ret); \
	printf("Errno: %d\n\n", errno);

void t_write() {
	int		fd;
	char	*buf;
	size_t	count;
	ssize_t	ret;

	/* =============================== Test 1 =============================== */
	fd = 1;
	buf = "Hello World!";
	count = ft_strlen(buf);

	T_WRITE

	/* =============================== Test 2 =============================== */
	fd = 2;
	buf = "Hello World!";
	count = 3;

	T_WRITE

	/* =============================== Test 3 =============================== */
	fd = 1;
	buf = "Hello World!";
	count = 0;

	T_WRITE

	/* =============================== Test 4 =============================== */
	fd = 1;
	buf = NULL;
	count = 10;

	T_WRITE

	/* =============================== Test 5 =============================== */
	fd = -42;
	buf = "Hello World!";
	count = ft_strlen(buf);

	T_WRITE

	/* =============================== Test 6 =============================== */
	fd = 42;
	buf = "Hello World!";
	count = ft_strlen(buf);

	T_WRITE
}


/* ************************************************************************** */
/*                                   ft_read                                  */
/* ************************************************************************** */


#define T_READ \
	printf("Bytes to read: %lu  |  on fd: %d\n", count, fd); \
	ret = ft_read(fd, buf, count); \
	printf("Read: \"%s\" (%ld)\n", buf, ret); \
	printf("Errno: %d\n\n", errno); \
	free(buf);

void t_read() {
	int		fd;
	char	*buf;
	size_t	count;
	ssize_t	ret;

	/* =============================== Test 1 =============================== */
	fd = 0;
	buf = calloc(1, 255);
	count = 100;

	T_READ

	/* =============================== Test 2 =============================== */
	fd = 0;
	buf = calloc(1, 255);
	count = 3;

	T_READ

	/* =============================== Test 3 =============================== */
	fd = 0;
	buf = calloc(1, 255);
	count = 0;

	T_READ

	/* =============================== Test 4 =============================== */
	fd = 0;
	buf = NULL;
	count = 3;

	T_READ

	/* =============================== Test 5 =============================== */
	fd = -42;
	buf = calloc(1, 255);
	count = 255;

	T_READ

	/* =============================== Test 6 =============================== */
	fd = 42;
	buf = calloc(1, 255);
	count = 255;

	T_READ
}


/* ************************************************************************** */
/*                                    main                                    */
/* ************************************************************************** */


#define DELIM printf("================================\n\n");

int main() {
	t_strlen();
	DELIM
	t_strcpy();
	DELIM
	t_strcmp();
	DELIM
	t_strdup();
	DELIM
	t_write();
	DELIM
	t_read();
	return 0;
}
