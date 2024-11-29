; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_list_remove_if_bonus.s                          :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/11/26 12:00:00 by ysabik            #+#    #+#              ;
;    Updated: 2024/11/26 12:00:00 by ysabik           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%include "defs.inc"

global	ft_list_remove_if

section	.text

; void	ft_list_remove_if(t_list **lst, void *ref_data,
; 			int (*cmp)(void *, void *), void (*free_fct)(void *));
ft_list_remove_if:
	cmp		rdi, 0
	je		.err
	cmp		rdx, 0
	je		.err

	push	rbp
	mov		rbp, rsp
	sub		rsp, 48				; tmpA(8), cmp(8), tmpB(8),
								; 	ref_data(8), free_fct(8), prev(8)

	mov		[rbp-8], rdi		; list = lst
	mov		[rbp-16], rdx		; cmp = cmp
	mov		[rbp-32], rsi		; ref_data = ref_data
	mov		[rbp-40], rcx		; free_fct = free_fct

	; first loop: update lst directly
	.loop1:
		mov		rdi, [rdi]		; rdi = *lst
		cmp		rdi, 0
		je		.loop1_end

		mov		rdi, [rdi]		; args[0] = *rdi (== rdi->data)
		mov		rsi, [rbp-32]	; args[1] = ref_data
		call	[rbp-16]		; cmp(...)
		cmp		eax, 0			; EAX != RAX => INT != LONG LONG
		jne		.loop1_end

		mov		rdx, [rbp-8]	; rdx = tmpA
		mov		rdi, [rdx]		; rdi = *rdx
		mov		[rbp-24], rdi	; tmpB = rdi   (--> tmpB = *tmpA)
		mov		rcx, [rdi+8]	; rcx = rdi->next
		mov		[rdx], rcx		; *rdx = rcx   (--> *tmpA = (*tmpA)->next)
		cmp		qword [rbp-40], 0
		je		.loop1_next

	.loop1_free:
		mov		rdi, [rdi]		; args[0] = (*tmpA)->data
		call	[rbp-40]		; free_fct(...)

	.loop1_next:
		mov		rdi, [rbp-24]	; args[0] = tmpB
		call	FREE
		mov		rdi, [rbp-8]	; rdi = tmpA
		jmp		.loop1

	.loop1_end:
		mov		rsi, [rbp-8]	; rsi = list
		mov		rsi, [rsi]		; *rsi = rsi
		mov		[rbp-48], rsi	; prev = rsi

	; second loop: remove using prev
	.loop2:
		cmp		rsi, 0
		je		.end
		mov		rdi, [rsi+8]
		cmp		rdi, 0
		je		.end

		mov		rdi, [rdi]		; args[0] = *rdi (== rdi->data)
		mov		rsi, [rbp-32]	; args[1] = ref_data
		call	[rbp-16]		; cmp(...)
		cmp		eax, 0			; EAX != RAX => INT != LONG LONG
		je		.loop2_remove
		mov		rsi, [rbp-48]	; rsi = prev
		mov		rsi, [rsi+8]	; rsi = rsi->next
		mov		[rbp-48], rsi	; prev = rsi
		jmp		.loop2

	.loop2_remove:
		mov		rsi, [rbp-48]	; rsi = prev
		mov		rdx, [rsi+8]	; rdx = rsi->next
		mov		rdi, [rdx]		; args[0] = rdx->data
		mov		[rbp-24], rdx	; tmpB = rdx
		mov		rcx, [rdx+8]	; rcx = rdx->next
		mov		[rsi+8], rcx	; rsi->next = rcx
		cmp		qword [rbp-40], 0
		je		.loop2_next

	.loop2_free:
		call	[rbp-40]		; free_fct(...)

	.loop2_next:
		mov		rdi, [rbp-24]	; args[0] = tmpB
		call	FREE
		mov		rsi, [rbp-48]	; rsi = prev
		jmp		.loop2

	.end:
		errno11	0
		add		rsp, 48
		mov		rsp, rbp
		pop		rbp
		ret

	.err:
		errno	EINVAL, 0
		ret
