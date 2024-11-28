; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    defs.inc                                           :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/11/26 12:00:00 by ysabik            #+#    #+#              ;
;    Updated: 2024/11/26 12:00:00 by ysabik           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

bits	64 ; System V AMD64 ABI
section .note.GNU-stack noexec

%define STDIN			0
%define STDOUT			1
%define STDERR			2

%define BUFF_SZ			0x1000

%define SYS_READ		0
%define SYS_WRITE		1
%define SYS_EXIT		60

%define EXIT_SUCCESS	0
%define EXIT_FAILURE	1

%define MALLOC			malloc wrt ..plt
%define ERRNO_LOC		__errno_location wrt ..plt
%define EINVAL			22
%define EFAULT			14
%define ENOMEM			12
%define EBADF			9

%macro errno 2					; errno = %1, rax = %2
	call	ERRNO_LOC			; rax = __errno_location()
	mov		dword [rax], %1		; *rax = %1
	mov		rax, %2				; rax = %2
%endmacro

%macro errno11 1				; errno = %1, using r11
	mov		r11, rax			; r11 = rax --> save the return value
	call	ERRNO_LOC			; rax = __errno_location()
	mov		dword [rax], %1		; *rax = %1
	mov		rax, r11			; rax = r11 --> get back the return value
%endmacro

extern __errno_location
extern malloc
