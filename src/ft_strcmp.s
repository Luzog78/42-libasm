; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strcmp.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/11/26 12:00:00 by ysabik            #+#    #+#              ;
;    Updated: 2024/11/26 12:00:00 by ysabik           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%include "defs.inc"

global	ft_strcmp ; int	ft_strcmp(const char *s1, const char *s2);

section	.text

ft_strcmp:
	cmp		rdi, 0					; if (s1 == 0)
	je		.err					;   goto .err
	cmp		rsi, 0					; if (s2 == 0)
	je		.err					;   goto .err

	.loop:
		mov		al, byte [rdi]		; al (8 bits register) = *(char *)s1
		mov		cl, byte [rsi]		; cl (8 bits register) = *(char *)s1
		cmp		al, cl
		jne		.diff				; if (al != cl) goto .diff
		cmp		al, 0
		je		.equal				; if (al == 0) goto .equal
		inc		rdi					; s1++
		inc		rsi					; s2++
		jmp		.loop

	.equal:
		xor		rax, rax
		jmp		.end

	.diff:
		movzx	rax, al				; rax (int64) = al (int8)
		movzx	rcx, cl				; rcx (int64) = cl (int8)
		sub		rax, rcx			; rax = (int64) al - (int64) cl

	.end:
		errno11	0
		ret

	.err:
		errno	EINVAL, 0
		ret
