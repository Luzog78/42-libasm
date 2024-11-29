; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_atoi_base_bonus.s                               :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/11/26 12:00:00 by ysabik            #+#    #+#              ;
;    Updated: 2024/11/26 12:00:00 by ysabik           ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%include "defs.inc"

global	ft_atoi_base_bonus ; int	ft_atoi_base_bonus(const void *str, const void *base);

section	.text

ft_atoi_base_bonus:
	push	rbp
	mov		rbp, rsp
	sub		rsp, 48				; str_save(8), base_save(8), sum(8), base_len(8), neg_mult(8), 8 for alignment

	cmp		rdi, 0
	je		.err
	cmp		rsi, 0
	je		.err

	mov		[rbp-16], rsi		; [rbp-16] = base
	mov		qword [rbp-24], 0	; [rbp-16] = sum = 0

	lea		rdx, [rbp-32]		; args[2] = &base_len
	lea		rcx, [rbp-40]		; args[3] = &neg_mult
	call	init_vars
	cmp		rax, 0
	je		.err
	mov		[rbp-8], rax		; [rbp-8] = str (spaced and signs trimed)

	.loop:
		mov		rdi, [rbp-16]	; args[0] = base
		mov		rdx, [rbp-8]	; rdx = str
		mov		cl, byte [rdx]	; cl = *str
		movzx	rsi, cl			; args[1] = cl
		call	index_of
		cmp		rax, -1
		je		.loop_end
		mov		rdi, rax		; rdi = index of `*str` in `base`
		mov		rax, [rbp-24]	; rax = sum
		mul		qword [rbp-32]	; rax *= base_len
		add		rax, rdi		; rax += rdi
		mov		[rbp-24], rax	; sum = rax
		inc		qword [rbp-8]	; str++
		jmp		.loop

	.loop_end:
		mov		rax, [rbp-24]	; rax (return value) = sum
		mul		qword [rbp-40]	; rax *= neg_mult

	.end:
		add		rsp, 48
		mov		rsp, rbp
		pop		rbp
		ret

	.err:
		xor		rax, rax
		jmp		.end

; int	index_of(char *s, char c)
index_of:
	mov		rax, 0

	.loop:
		cmp		byte [rdi], 0
		je		.end_fail
		cmp		byte [rdi], sil
		je		.end_success
		inc		rdi
		inc		rax
		jmp		.loop

	.end_success:
		ret

	.end_fail:
		mov		rax, -1
		ret

; char	*init_vars(char *str, char *base, int *base_len, int *neg_mult)
init_vars:
	push	rbp
	mov		rbp, rsp
	sub		rsp, 32				; str(8), base(8), 8 for alignment, &neg_mult(8)

	mov		[rbp-8], rdi		; rbp-8 = &str
	mov		[rbp-16], rsi		; rbp-16 = &base
	mov		[rbp-32], rcx		; rbp-32 = &&neg_mult

	; base checks
	mov		qword [rdx], 0		; *base_len = 0
	.base_loop:
		cmp		byte [rsi], 0
		je		.base_end
		inc		rsi				; base++
		inc		qword [rdx]		; *base_len += 1
		jmp		.base_loop

	.base_end:
		cmp		qword [rdx], 2	; if (*base_len < 2)
		jl		.err			;   goto .err
		mov		rdi, [rbp-16]	; args[0] = base
		call	check_errors
		cmp		rax, 0
		je		.err

	; trim + neg str
	.trim_loop:
		mov		rax, [rbp-8]	; rax = str
		movzx	rdi, byte [rax]	; args[0] = *rax
		call	is_whitespace
		cmp		rax, 0
		je		.trim_end
		inc		qword [rbp-8]	; str++
		jmp		.trim_loop

	.trim_end:
		mov		rax, [rbp-8]	; rax = str
		mov		rdx, [rbp-32]	; rdx = &neg_mult

	mov		qword [rdx], 1		; [rdx] (**neg_mult) = 1
	.neg_loop:
		mov		cl, byte [rax]	; cl = *str
		cmp		cl, '+'
		je		.neg_continue
		cmp		cl, '-'
		je		.neg_negation
		jmp		.neg_end

	.neg_negation:
		neg		qword [rdx]		; [rdx] (**neg_mult) *= -1

	.neg_continue:
		inc		rax				; str++
		jmp		.neg_loop

	.neg_end:
	.end:
		add		rsp, 32
		mov		rsp, rbp
		pop		rbp
		ret						; return str

	.err:
		xor		rax, rax
		jmp		.end

; int	check_errors(char *base)
check_errors:
	.loop:
		mov		cl, byte [rdi]	; cl = *base
		cmp		cl, 0
		je		.loop_end
		cmp		cl, '+'			; if (cl == '+')
		je		.err			;   goto .err
		cmp		cl, '-'			; if (cl == '-')
		je		.err			;   goto .err
		cmp		cl, ' '			; if (cl <= ' ')
		jle		.err			;   goto .err
		cmp		cl, '~'			; if (cl > '~')
		jg		.err			;   goto .err

		mov		rdx, rdi		; rdx = base
		inc		rdx				; rdx++

	.sub_loop:
		cmp		byte [rdx], 0
		je		.sub_loop_end
		cmp		byte [rdx], cl	; if (*rdx == cl)
		je		.err			;   goto .err
		inc		rdx				; rdx++
		jmp		.sub_loop

	.sub_loop_end:
		inc		rdi				; base++
		jmp		.loop

	.loop_end:
		mov		rax, 1
		ret

	.err:
		xor		rax, rax
		ret

; boolean	is_whitespace(char c)
is_whitespace:
	cmp		rdi, ' '		; if (c == ' ')
	je		.whitespace		;   goto .whitespace
	cmp		rdi, 0x9		; if (c < '\t')
	jl		.not_whitespace	;   goto .not_whitespace
	cmp		rdi, 0xd		; if (c > '\r')
	jg		.not_whitespace	;   goto .not_whitespace

	.whitespace:
		mov		rax, 1
		ret

	.not_whitespace:
		xor		rax, rax
		ret
