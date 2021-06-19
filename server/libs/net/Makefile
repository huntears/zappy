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
NAME = net
LIBNAME = lib$(NAME).a

# sources
C_SRCS = $(shell find src/ -name "*.c")
INCLUDE_DIR = include

# the C compiler to use
CC = gcc -fdiagnostics-color=always
AR = ar
ARFLAGS = rcs

# include flags
IFLAGS = $(addprefix -I, $(shell find include/ -type d))

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
LDFLAGS =
# libraries to link
LDLIBS =

# debug
DEBUG_LIBNAME = lib$(NAME)_debug.a
DEBUG_FLAGS = -g3

## lib vars
LIB_DEST = ../$(LIBNAME)
DEBUG_LIB_DEST = ../$(DEBUG_LIBNAME)
HEADERS_DEST = ../../include/libs/$(NAME)/

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

all: $(LIBNAME)
.PHONY: all

$(LIBNAME): $(OBJS)
	@$(ECHO) "lib: $(OK_STRING) $(NAME)/build $(NAME)"
	@$(RM) $(LIBNAME)
	@$(AR) $(ARFLAGS) $@ $^
	@$(MAKE) -s put_libh

put_libh:
	@if [ -f $(LIBNAME) ]; then cp -f $(LIBNAME) $(LIB_DEST); fi
	@if [ -f $(DEBUG_LIBNAME) ]; then cp -f $(DEBUG_LIBNAME) $(DEBUG_LIB_DEST); fi
	@mkdir -p $(HEADERS_DEST)
	@cp -r $(INCLUDE_DIR)/. $(HEADERS_DEST)
	@rm -rf $(HEADERS_DEST)/private
.PHONY: put_libh

%.c.o: %.c
	@$(ECHO) "lib: $(OK_STRING) $(NAME)/compile $<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(SECURITY_FLAGS) -MMD -MP -c -o $@ $<

re:
	@$(MAKE) -s fclean
	@$(MAKE) -s $(LIBNAME)
.PHONY: re

# debug
debug: $(DEBUG_LIBNAME)
.PHONY: debug

$(DEBUG_LIBNAME): $(DEBUG_OBJS)
	@$(RM) $(DEBUG_LIBNAME)
	@$(AR) $(ARFLAGS) $@ $^
	@$(MAKE) -s put_libh

%.c.debug.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEBUG_FLAGS) -MMD -MP -c -o $@ $<

# clean
clean:
	@$(ECHO) "lib: $(OK_STRING) $(NAME)/clean"
	@$(RM) $(OBJS) $(DEPENDS)
	@$(RM) $(DEBUG_OBJS) $(DEBUG_DEPENDS)
	@$(RM) $(DEBUG_DUSTS)
.PHONY: clean

fclean: clean
	@$(ECHO) "lib: $(OK_STRING) $(NAME)/fclean"
	@$(RM) $(LIBNAME) $(LIB_DEST)
	@$(RM) $(DEBUG_LIBNAME) $(DEBUG_LIB_DEST)
	@$(RM) -r $(HEADERS_DEST)
.PHONY: fclean

# default target
.DEFAULT_GOAL = all