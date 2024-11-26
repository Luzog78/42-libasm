; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strcpy.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/11/26 12:00:00 by ysabik            #+#    #+#              ;
;    Updated: 2024/11/26 12:00:00 by ysabik           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%include "defs.inc"

global	ft_strcpy ; char	*ft_strcpy(char *dst, const char *src);

section	.text

ft_strcpy:
	mov		rax, rdi				; rax = dst
	cmp		rax, 0					; if (dst == 0)
	je		.err					;   goto .err
	cmp		rsi, 0					; if (src == 0)
	je		.err					;   goto .err

	.loop:
		mov		cl, byte [rsi]		; cl (8 bits register) = *(char *)src
		mov		byte [rdi], cl		; *(char *)dst = cl
		inc		rsi					; src++
		inc		rdi					; dst++
		cmp		byte [rsi], 0		; if (*(char *)src == 0)
		je		.end				;   goto .end
		jmp		.loop

	.end:
		errno11	0
		ret							; return rax (original dst)

	.err:
		errno	EFAULT, 0
		ret
