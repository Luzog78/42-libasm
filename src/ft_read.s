; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_read.s                                         :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/11/26 12:00:00 by ysabik            #+#    #+#              ;
;    Updated: 2024/11/26 12:00:00 by ysabik           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%include "defs.inc"

global	ft_read ; ssize_t	ft_read(int fd, const void *buf, size_t count);

section	.text

ft_read:
	mov		rax, SYS_READ
	syscall					; rax = read(...)
	cmp		rax, 0			; if (rax < 0)
	jl		.err			;   goto .err
	errno11	0				; errno = 0
	ret

	.err:
		neg		rax			; rax = -rax
		mov		rcx, rax	; rcx = rax
		errno	ecx, -1		; errno = rcx ; rax = -1
		ret
