; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_list_sort_bonus.s                               :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/11/26 12:00:00 by ysabik            #+#    #+#              ;
;    Updated: 2024/11/26 12:00:00 by ysabik           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%include "defs.inc"

global	ft_list_sort ; void	ft_list_sort(t_list **lst, int (*cmp)(void *, void *));

section	.text

ft_list_sort:
	cmp		rdi, 0
	je		.err
	cmp		rsi, 0
	je		.err

	push	rbp
	mov		rbp, rsp
	sub		rsp, 32					; list(8), cmp(8), tmpA(8), 8 for alignment

	mov		rdi, [rdi]				; rdi = *lst
	mov		[rbp-8], rdi			; list = rdi (== *lst)
	mov		[rbp-16], rsi			; cmp = cmp

	.loop:
		cmp		rdi, 0
		je		.end
		mov		rsi, [rdi+8]		; rsi = rdi->next
		cmp		rsi, 0
		je		.end
		mov		[rbp-24], rdi		; tmpA = rdi

		mov		rdi, [rdi]			; args[0] = *rdi (== rdi->data)
		mov		rsi, [rsi]			; args[1] = *rsi (== rsi->data)
		call	[rbp-16]			; cmp(...)
		cmp		eax, 0				; EAX != RAX => INT != LONG LONG
		jg		.switch
		jmp		.loop_next

	.switch:
		mov		rdi, [rbp-24]		; rcx = tmpA
		mov		rsi, [rdi+8]		; rsi = rcx->next
		mov		rcx, [rdi]			; rcx = *rdi (== rdi->data)
		mov		rdx, [rsi]			; rdx = *rsi (== rsi->data)
		mov		[rdi], rdx			; *rdi (== rdi->data) = rdx
		mov		[rsi], rcx			; *rsi (== rsi->data) = rcx
		mov		rdi, [rbp-8]		; rdi = *lst
		jmp		.loop

	.loop_next:
		mov		rdi, [rbp-24]		; rdi = tmpA
		mov		rdi, [rdi+8]		; rdi = rdi->next
		jmp		.loop

	.end:
		errno11	0
		add		rsp, 32
		mov		rsp, rbp
		pop		rbp
		ret

	.err:
		errno	EINVAL, 0
		ret
