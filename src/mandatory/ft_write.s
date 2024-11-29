; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_write.s                                         :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/11/26 12:00:00 by ysabik            #+#    #+#              ;
;    Updated: 2024/11/26 12:00:00 by ysabik           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%include "defs.inc"

global	ft_write

section	.text

; ssize_t	ft_write(int fd, const void *buf, size_t count);
ft_write:
	mov		rax, SYS_WRITE
	syscall					; rax = write(...)
	cmp		rax, 0			; if (rax < 0)
	jl		.err			;   goto .err
	errno11	0				; errno = 0
	ret

	.err:
		neg		rax			; rax = -rax
		mov		rcx, rax	; rcx = rax
		errno	ecx, -1		; errno = rcx ; rax = -1
		ret
