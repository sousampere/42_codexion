# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/03 06:57:12 by gtourdia          #+#    #+#              #
#    Updated: 2026/04/12 11:35:35 by gaspard          ###   ########.fr        #
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
C_FILES=coders/codexion.c\
		coders/time.c\
		coders/heap_moves.c\
		\
		coders/preparation/parsing.c\
		coders/preparation/init.c\
		\
		coders/simulation/simulation.c\
		coders/simulation/monitoring.c\
		coders/simulation/coder_actions.c\
		\
		coders/misc/free.c\
		coders/misc/print.c


# COLORS
YELLOW=\033[0;33m
CYAN=\033[0;36m
GREEN=\033[0;32m
RESET=\033[0m

# Default args
NB_CODERS=10
BURNOUT=3000
COMPILE=200
DEBUG=100
REFACTOR=200
NB_COMPILES=10
DONGLE_COOLDOWN=400
SCHEDULER=fifo

all: $(NAME)

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
	$(COMPILER) $(C_FILES) $(FLAGS) -o $(NAME)

# Run
run: $(NAME)
	clear && clear
	@printf "$(CYAN)[Clean]$(RESET) ➡️  Running program...\n"
	./$(NAME) $(NB_CODERS) $(BURNOUT) $(COMPILE) $(DEBUG) $(REFACTOR) $(NB_COMPILES) $(DONGLE_COOLDOWN) $(SCHEDULER)

dbg: re run

# Run with kebertra prompt (credit: github/keroberos68)
krun: re
	./$(NAME) $(NB_CODERS) $(BURNOUT) $(COMPILE) $(DEBUG) $(REFACTOR) $(NB_COMPILES) $(DONGLE_COOLDOWN) $(SCHEDULER)

clean:
	@printf "$(CYAN)[Clean]$(RESET) ➡️  Cleaning useless folders...\n"
	rm -rf $(NAME).dSYM/

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)