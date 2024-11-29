; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_list_push_front_bonus.s                         :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/11/26 12:00:00 by ysabik            #+#    #+#              ;
;    Updated: 2024/11/26 12:00:00 by ysabik           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%include "defs.inc"

global	ft_list_push_front

section	.text

; void	ft_list_push_front(t_list **lst, void *data);
ft_list_push_front:
	cmp		rdi, 0
	je		.null_pt

	push	rbp
	mov		rbp, rsp
	sub		rsp, 16				; lst(8), data(8)

	mov		[rbp-8], rdi		; lst = args[0]
	mov		[rbp-16], rsi		; data = args[1]

	mov		rdi, 16				; args[0] = 16
	call	MALLOC
	cmp		rax, 0
	je		.no_mem

	mov		rcx, [rbp-8]		; rcx = lst
	mov		rdx, [rcx]			; rdx = *lst
	mov		rdi, [rbp-16]		; rdi = data

	mov		qword [rax], rdi	; *rax = data
	mov		qword [rax+8], rdx	; *(rax+8) = *lst

	mov		[rcx], rax			; *lst = rax
	errno11	0

	.end:
		add		rsp, 16
		mov		rsp, rbp
		pop		rbp
		ret

	.null_pt:
		errno	EINVAL, 0
		ret

	.no_mem:
		errno	ENOMEM, 0
		jmp		.end
