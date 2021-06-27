##
## EPITECH PROJECT, 2021
## MAKEFILE
## File description:
## My supra makefilator
##

# =========================================================================== #
# =================================== VAR =================================== #
# =========================================================================== #

# binary output
BIN = zappy_server

# sources
C_SRCS = $(shell find src -name "*.c")
LIBS = net list
SYSTEM_LIBS = m

# the C compiler to use
CC = gcc -fdiagnostics-color=always

# include flags
INCLUDE_DIR = include include/libs
IFLAGS = $(addprefix -I, $(INCLUDE_DIR))

# warning flags
WFLAGS = -W -Wall -Wextra -Wpedantic \
	-Wshadow -Wundef -Wuninitialized -Wmaybe-uninitialized -Wnonnull -Wnull-dereference \
	-Wshift-overflow=2 -Wformat=2 -Wformat-truncation -Wrestrict \
	-Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wjump-misses-init \
	-Wcast-align -Wcast-qual -Wreturn-type -Wsequence-point \
	-Wstrict-aliasing=2 -Wframe-larger-than=32768 \
	-Wsync-nand -Wtrampolines -Wenum-compare -Wsign-compare -Wfloat-equal -Wimplicit-int \
	-Wparentheses -Wmissing-parameter-type -Wmissing-braces -Wpointer-sign \
	-Wsuggest-final-types -Wsuggest-final-methods \
	-Wempty-body -Wmain -Winit-self \
	-Waggressive-loop-optimizations \
	-Wwrite-strings -Waddress -Warray-bounds -Wchar-subscripts \
	-Wvolatile-register-var -Wignored-qualifiers \
	-Wdouble-promotion -Wodr -Wformat-signedness \
	-fno-common

# security flags
SECURITY_FLAGS = -D_FORTIFY_SOURCE=2 -O2 -fPIE \
	-fstack-protector-all -fstack-protector-strong -Wstack-protector --param ssp-buffer-size=4
LD_SECURITY_FLAGS = -pie -Wl,-z,defs -Wl,-z,now -Wl,-z,relro

# compilation flag for C source files
CFLAGS = -std=gnu11
# flags for the c-preprocessor (C and C++)
CPPFLAGS = $(IFLAGS) $(WFLAGS)
# linker flags
LDFLAGS = -Llibs
# libraries to link
LDLIBS = $(addprefix -l, $(SYSTEM_LIBS) $(LIBS))

# debug
DEBUG_BIN = $(BIN)_debug
DEBUG_FLAGS = -g3 -ffunction-sections -fdata-sections
DEBUG_LDLIBS = $(addprefix -l, $(SYSTEM_LIBS) $(addsuffix _debug, $(LIBS)))

# test
TESTS_BIN = unit_tests-$(BIN)
TESTS_SOURCES = $(filter-out src/main.c, $(C_SRCS)) $(shell find tests/ -name "*.c")
TESTS_FLAGS = -I./tests --coverage -DTESTS_RUN -O3
TESTS_LIBS = -lcriterion

# =========================================================================== #
# ================================ OBJS-DEPS ================================ #
# =========================================================================== #

# release
OBJS = $(C_SRCS:.c=.c.o)
DEPENDS = $(OBJS:.o=.d)
-include $(DEPENDS)

# debug
DEBUG_OBJS = $(C_SRCS:.c=.c.debug.o)
DEBUG_DEPENDS = $(DEBUG_OBJS:.o=.d)
-include $(DEBUG_DEPENDS)

DEBUG_DUSTS = $(wildcard vgcore.*)

# test
TESTS_OBJS = $(TESTS_SOURCES:.c=.c.tests.o)
TESTS_DEPENDS = $(TESTS_OBJS:.o=.d)
-include $(TESTS_DEPENDS)

TEST_DUSTS = $(TESTS_OBJS:.o=.gcno) $(TESTS_OBJS:.o=.gcda)

# =========================================================================== #
# ================================= DISPLAY ================================= #
# =========================================================================== #

## echo
ECHO = echo -e

NO_COLOR = \x1b[0m
OK_COLOR = \x1b[32;01m
ERROR_COLOR = \x1b[31;01m
WARN_COLOR = \x1b[33;01m

OK_STRING = $(OK_COLOR)[✔]$(NO_COLOR)
ERROR_STRING = $(ERROR_COLOR)[X]$(NO_COLOR)
WARN_STRING = $(WARN_COLOR)[!]$(NO_COLOR)

# =========================================================================== #
# ================================== OTHER ================================== #
# =========================================================================== #

RM = rm -f

# =========================================================================== #
# ================================== RULES ================================== #
# =========================================================================== #

all: make_libs
	@$(MAKE) --no-print-directory $(BIN)
.PHONY: all

$(BIN): $(OBJS)
	@$(ECHO) "$(OK_STRING) $(BIN)/build $(BIN)"
	@$(CC) $(LDFLAGS) $(LD_SECURITY_FLAGS) -o $(BIN) $(OBJS) $(LDLIBS)

%.c.o: %.c
	@$(ECHO) "$(OK_STRING) $(BIN)/compile $<"
	@$(CC) $(CFLAGS) $(SECURITY_FLAGS) $(CPPFLAGS) -MMD -MP -c -o $@ $<

re: fclean
	@$(MAKE) -s all
.PHONY: re

# debug

debug: make_debug_libs
	$(MAKE) $(DEBUG_BIN)
.PHONY: debug

$(DEBUG_BIN): $(DEBUG_OBJS)
	$(CC) $(LDFLAGS) -o $(DEBUG_BIN) $(DEBUG_OBJS) $(DEBUG_LDLIBS)

%.c.debug.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEBUG_FLAGS) -MMD -MP -c -o $@ $<

# tests
tests_run: make_libs
	@$(MAKE) -s $(TESTS_BIN)
	@./$(TESTS_BIN)
.PHONY: tests_run

$(TESTS_BIN): $(TESTS_OBJS)
	@$(ECHO) "$(OK_STRING) $(BIN)/build $(TESTS_BIN)"
	@$(CC) $(LDFLAGS) $(TESTS_FLAGS) -o $(TESTS_BIN) $(TESTS_OBJS) $(LDLIBS) $(TESTS_LIBS)

%.c.tests.o: %.c
	@$(ECHO) "$(OK_STRING) $(BIN)/compile $<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(TESTS_FLAGS) -MMD -MP -c -o $@ $<

functional_tests_run: all
.PHONY: functional_tests_run

# coverage
coverage:
	@$(MAKE) -s tests_run &&:||:
	@gcovr --exclude tests/ --branch 2> /dev/null
	@gcovr --exclude tests/ 2> /dev/null
.PHONY: coverage

# clean
clean: clean_libs
	@$(ECHO) "$(OK_STRING) $(BIN)/clean"
	@$(RM) $(OBJS) $(DEPENDS)
	@$(RM) $(DEBUG_OBJS) $(DEBUG_DEPENDS)
	@$(RM) $(DEBUG_DUSTS)
	@$(RM) $(TESTS_OBJS) $(TESTS_DEPENDS)
	@$(RM) $(TEST_DUSTS)
.PHONY: clean

fclean: fclean_libs clean
	@$(ECHO) "$(OK_STRING) $(BIN)/fclean"
	@$(RM) -rf include/libs
	@$(RM) $(BIN)
	@$(RM) $(DEBUG_BIN)
	@$(RM) $(TESTS_BIN)
.PHONY: fclean

full_clean: fclean
	@echo -e "\x1b[32;01m[✔]\x1b[0m full_clean"
	@find . -name "*a.out" -delete
	@find . -name "*.o" -delete
	@find . -name "*.d" -delete
	@find . -name "*.a" -delete
	@find . -name "*.so" -delete
	@find . -name "*.gch" -delete
	@find . -name "*.gcov" -delete
	@find . -name "*.gcda" -delete
	@find . -name "*.gcno" -delete
	@find . -name "vgcore.*" -delete
	@find . -name "*.c.tmp" -delete
	@find . -name "*.h.tmp" -delete
.PHONY: full_clean

# libs
make_libs:
	@for i in $(LIBS); do \
		(cd libs/$$i/ && $(MAKE) -s all); \
	done

make_debug_libs:
	@for i in $(LIBS); do \
		(cd libs/$$i/ && $(MAKE) debug); \
	done

clean_libs:
	@for i in $(LIBS); do \
		(cd libs/$$i/ && $(MAKE) -s clean); \
	done

fclean_libs:
	@for i in $(LIBS); do \
		(cd libs/$$i/ && $(MAKE) -s fclean); \
	done

# default target
.DEFAULT_GOAL = all