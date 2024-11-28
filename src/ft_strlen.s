; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strlen.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/11/26 12:00:00 by ysabik            #+#    #+#              ;
;    Updated: 2024/11/26 12:00:00 by ysabik           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%include "defs.inc"

global	ft_strlen ; size_t	ft_strlen(const char *s);

section	.text

ft_strlen:
	mov		rax, rdi			; rax = s
	cmp		rax, 0				; if (s == 0)
	je		.err				;   goto .err

	.loop:
		cmp		byte [rax], 0	; if (*(char *)rax == 0)
		je		.end			;   goto .end
		inc		rax				; rax++
		jmp		.loop

	.end:
		sub		rax, rdi		; rax -= rdi
		errno11	0
		ret

	.err:
		errno	EINVAL, 0
		ret
