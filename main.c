/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:25:52 by ysabik            #+#    #+#             */
/*   Updated: 2024/11/26 17:12:12 by ysabik           ###   ########.fr       */
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

int main() {
	t_strlen();
	printf("================================\n\n");
	t_strcpy();
	return 0;
}
