# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by ysabik            #+#    #+#              #
#    Updated: 2024/11/27 14:01:23 by ysabik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					= nasm
CFLAGS				= -f elf64 -g -I ./src
NAME				= libasm.a
SRC_FILES			= \
						src/ft_strlen.s \
						src/ft_strcpy.s \
						src/ft_strcmp.s

BUILD_FOLDER		= ./build

C_RESET				= \033[0m
C_BOLD				= \033[1m
C_DIM				= \033[2m
C_UNDERLINE			= \033[4m
C_BLINK				= \033[5m
C_BLACK				= \033[30m
C_RED				= \033[31m
C_GREEN				= \033[32m
C_YELLOW			= \033[33m
C_BLUE				= \033[34m
C_MAGENTA			= \033[35m
C_CYAN				= \033[36m
C_WHITE				= \033[37m

OBJ_FILES			= $(SRC_FILES:.s=.o)
BUILD_FILES			= $(addprefix $(BUILD_FOLDER)/, $(OBJ_FILES))

TO_COMPILE			= 0

all : $(NAME)

main : all
	@echo -n "$(C_CYAN)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Compiling $(C_YELLOW)./main$(C_CYAN)... :$(C_RESET)"
	@echo ""
	@echo ""
	@echo -n "  > $(C_YELLOW)$(C_BOLD)./main$(C_RESET):  $(C_DIM)"
	gcc -Wall -Wextra -Werror main.c -L. -lasm -I. -o main
	@echo "$(C_RESET)"
	@echo ""
	@echo -n "$(C_BOLD)$(C_MAGENTA)>$(C_BLUE)>$(C_CYAN)>$(C_GREEN)"
	@echo -n " Compilation success ! "
	@echo "$(C_CYAN)<$(C_BLUE)<$(C_MAGENTA)<$(C_RESET)"
	@echo ""

$(NAME) : $(BUILD_FILES)
	@echo ""
	@echo -n "  > $(C_YELLOW)$(C_BOLD)./$(NAME)$(C_RESET):  $(C_DIM)"
	ar rcs $(NAME) $(BUILD_FILES)
	@echo "$(C_RESET)"
	@echo ""
	@echo -n "$(C_BOLD)$(C_MAGENTA)>$(C_BLUE)>$(C_CYAN)>$(C_GREEN)"
	@echo -n " Compilation success ! "
	@echo "$(C_CYAN)<$(C_BLUE)<$(C_MAGENTA)<$(C_RESET)"
	@echo ""

m_line_break :
	@echo ""

b_flags :
	@$(eval CFLAGS += -D BONUS=1)

bonus : b_flags all

$(BUILD_FOLDER)/%.o : %.s
	@if [ $(TO_COMPILE) -eq 0 ] ; then \
		echo -n "$(C_CYAN)$(C_BOLD)$(C_UNDERLINE)" ; \
		echo "Compiling $(C_YELLOW)./$(NAME)$(C_CYAN)... :$(C_RESET)" ; \
		echo "" ; \
	fi
	@$(eval TO_COMPILE := 1)
	@echo -n "  - $(C_GREEN)$<$(C_RESET):  $(C_DIM)"
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<
	@echo -n "$(C_RESET)"

define del =
	@echo -n "$(C_RED)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Deleting files... :$(C_RESET)$(C_RED)"
	@\
	l=-1 ; \
	for file in $(1) ; do \
		if [ $${#file} -gt $$l ] ; then \
			l=$${#file} ; \
		fi ; \
	done ; \
	cols=$$((64 / $$l)) ; \
	i=0 ; \
	for file in $(1) ; do \
		if [ $$i -eq 0 ] ; then \
			echo -n "    " ; \
		fi ; \
		if [ "$$file" = "./$(NAME)" ] ; then \
			printf "$(C_YELLOW)%-$$((l))s  $(C_RED)" "$$file" ; \
		else \
			printf "%-$$((l))s  " "$$file" ; \
		fi ; \
		if [ $$i -gt $$cols ] ; then \
			echo "" ; \
			i=-1; \
		fi ; \
		i=$$(($$i + 1)); \
	done ; \
	if [ $$i -ne -1 ] ; then \
		echo "" ; \
	fi
	@echo "$(C_RESET)"
endef

clean :
	$(call del, "$(BUILD_FOLDER)" $(BUILD_FILES) main)
	@rm -rf $(BUILD_FILES) $(BUILD_FOLDER) main

fclean :
	$(call del, "./$(NAME)" "$(BUILD_FOLDER)" $(BUILD_FILES) main)
	@rm -rf $(NAME) $(BUILD_FILES) $(BUILD_FOLDER) main

re : fclean m_line_break all

re_bonus : fclean m_line_break bonus

soft_clean :
	$(call del, "$(BUILD_FOLDER)" $(BUILD_FILES))
	@rm -rf $(BUILD_FILES) $(BUILD_FOLDER)

soft_fclean :
	$(call del, "./$(NAME)" "$(BUILD_FOLDER)" $(BUILD_FILES))
	@rm -rf $(NAME) $(BUILD_FILES) $(BUILD_FOLDER)

soft_re : soft_fclean m_line_break all

soft_re_bonus : soft_fclean m_line_break bonus

.PHONY : all bonus clean fclean re re_bonus \
			soft_clean soft_fclean soft_re soft_re_bonus \
			m_line_break b_flags
