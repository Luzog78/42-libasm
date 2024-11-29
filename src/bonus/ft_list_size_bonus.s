; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_list_size_bonus.s                               :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/11/26 12:00:00 by ysabik            #+#    #+#              ;
;    Updated: 2024/11/26 12:00:00 by ysabik           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%include "defs.inc"

global	ft_list_size

section	.text

; size_t	ft_list_size(t_list *lst);
ft_list_size:
	xor		rax, rax

	.loop:
		cmp		rdi, 0
		je		.end
		inc		rax
		mov		rdi, [rdi+8]
		jmp		.loop

	.end:
		ret
