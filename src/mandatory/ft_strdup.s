; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strdup.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/11/26 12:00:00 by ysabik            #+#    #+#              ;
;    Updated: 2024/11/26 12:00:00 by ysabik           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%include "defs.inc"

extern	malloc
extern	ft_strlen
extern	ft_strcpy

global	ft_strdup

section	.text

; char	*ft_strdup(const char *s);
ft_strdup:
	cmp		rdi, 0				; if (s == 0)
	je		.null_pt			;   goto .null_pt

	push	rbp
	mov		rbp, rsp
	sub		rsp, 8				; reserve 8 bytes for qword var1

	mov		qword [rbp-8], rdi	; var1 = s
	call	ft_strlen			; rax = ft_strlen(s)
	mov		rdi, rax			; rdi = rax
	inc		rdi					; rdi++
	call	MALLOC				; rax = malloc(rdi)
	cmp		rax, 0				; if (rax == 0)
	je		.no_mem				;   goto .no_mem
	mov		rdi, rax			; rdi = rax
	mov		rsi, qword [rbp-8]	; rsi = var1
	call	ft_strcpy			; ft_strcpy(rdi, var1)
	errno11	0

	.end:
		add		rsp, 8
		mov		rsp, rbp
		pop		rbp
		ret

	.no_mem:
		errno	ENOMEM, 0
		jmp		.end

	.null_pt:
		errno	EINVAL, 0
		ret
