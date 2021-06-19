##
## EPITECH PROJECT, 2021
## MAKEFILE
## File description:
## My supra makefilator
##

# build
all: server ai
.PHONY: all

ai:
	@$(MAKE) -C ai --no-print-directory all
.PHONY: ai

server:
	@$(MAKE) -C server --no-print-directory all
	@cp server/zappy_server ./
.PHONY: server

re:
	@$(MAKE) -s fclean
	@$(MAKE) -s all
.PHONY: re

# debug
debug:
	@$(MAKE) -C server --no-print-directory debug
	@cp server/zappy_server_debug ./
.PHONY: debug

# tests
tests_run:
	@$(MAKE) -C server --no-print-directory tests_run
.PHONY: tests_run

functional_tests_run:
	@$(MAKE) -C server --no-print-directory functional_tests_run
.PHONY: functional_tests_run

# coverage
coverage:
	@$(MAKE) -s tests_run
	@gcovr --exclude tests/ --branch 2> /dev/null
	@gcovr --exclude tests/ 2> /dev/null
.PHONY: coverage

# clean
clean:
	@$(MAKE) -C server --no-print-directory clean
.PHONY: clean

fclean: clean
	@$(MAKE) -C server --no-print-directory fclean
	@rm -f zappy_server_debug
	@rm -f zappy_server
.PHONY: fclean
