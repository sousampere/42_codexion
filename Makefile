# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/03 06:57:12 by gtourdia          #+#    #+#              #
#    Updated: 2026/04/03 08:48:45 by gtourdia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# PROJECT CONFIGURATION
AUTHOR=gtourdia
PROJECT_NAME=Codexion
PROJECT_START_DATE=2026-04-03
GITHUB=https://github.com/sousampere/
NAME=codexion
COMPILER=cc
FLAGS=-Wall -Wextra -Werror -pthread -g3
C_FILES=coders/codexion.c coders/parsing.c
H_FILES=coders/codexion.h


# COLORS
YELLOW=\033[0;33m
CYAN=\033[0;36m
GREEN=\033[0;32m
RESET=\033[0m

$(NAME):
	@printf "\033[2J\033[H"
	@printf "$(YELLOW)╔════════════════════════════════════════════════════════════════╗\n"
	@printf "$(YELLOW)║                                                                ║\n"
	@printf "$(YELLOW)║  44  44    2222    $(GREEN)Made by $(AUTHOR) $(YELLOW)\n"
	@printf "$(YELLOW)║  44  44   22  22   Project: $(CYAN)$(PROJECT_NAME) $(YELLOW)\n"
	@printf "$(YELLOW)║  444444      22    Started in: $(CYAN)$(PROJECT_START_DATE) $(YELLOW)\n"
	@printf "$(YELLOW)║      44     22     Github: $(CYAN)$(GITHUB) $(YELLOW)\n"
	@printf "$(YELLOW)║      44   222222                                               ║\n"
	@printf "$(YELLOW)║                                                                ║\n"
	@printf "$(YELLOW)╚════════════════════════════════════════════════════════════════╝\n"
	@printf "\033[3;66H║"
	@printf "\033[4;66H║"
	@printf "\033[5;66H║"
	@printf "\033[6;66H║"
	@printf "\033[7;66H║"
	@printf "\033[8;66H║"
	@printf "\033[9;80H\n"
	@printf "$(CYAN)[Installation]$(RESET) ➡️  Compiling file...\n"
	$(COMPILER) $(C_FILES) $(H_FILES) $(FLAGS)

all: $(NAME)

exe: $(NAME)
	./a.out



clean:
	rm -rf ./a.out
	
# fclean: clean

# re: fclean all