##
## EPITECH PROJECT, 2026
## minishell
## File description:
## Makefile minishell
##

# ─────────────────────────────────────────────────────────────
# PHONY TARGETS
# ─────────────────────────────────────────────────────────────
.PHONY: all clean fclean re unit_tests tests_run functional_tests compile_lib compile_lib_all

# ─────────────────────────────────────────────────────────────
# NAME
# ─────────────────────────────────────────────────────────────
NAME 		= mysh
# ─────────────────────────────────────────────────────────────
# SOURCE FILES AND OBJECT FILES
# ─────────────────────────────────────────────────────────────
SRC 		= src/minishell.c \
			  src/free_alloc.c \
			  src/parsing/alloc_launch_errors.c \
			  src/parsing/logic.c \
			  src/commands_handling/commands.c \
			  src/commands_handling/env.c \
			  src/commands_handling/builtins.c \
			  src/execute/child_proc.c \
			  src/execute/parent_proc.c
SRC_MAIN	= src/main.c
SRC_TEST 	= tests/test_main.c \
			  tests/test_env.c \
			  tests/test_commands.c
OBJ 		:= $(patsubst %.c,%.o,$(SRC))
OBJ_MAIN	:= $(patsubst %.c,%.o,$(SRC_MAIN))
OBJ_TEST 	:= $(patsubst %.c,%.o,$(SRC_TEST))

# ────────────────────────────────────────────────────────────
# COMPILER
# ─────────────────────────────────────────────────────────────
CC			= epiclang

# ─────────────────────────────────────────────────────────────
# COMPILATION FLAGS & LIBS
# ─────────────────────────────────────────────────────────────
CFLAGS      = -Wall -Wextra -g3 -Iinclude -O0 -fno-builtin
LDFLAGS 	= -L./ -lUtilsLib

# ─────────────────────────────────────────────────────────────
# TEST FLAGS & LIBS
# ─────────────────────────────────────────────────────────────
TEST_FLAGS  = --coverage
TEST_LIBS   = -lcmocka

# ─────────────────────────────────────────────────────────────
# TOOLS
# ─────────────────────────────────────────────────────────────
REMOVE 		= rm -f -r
RM_FILES 	= "*.gcno" "*.gcda" "*.html" "*.css" \
			  "*.gcov" "*.log" ".out" "*.o" "*.swp"

# ─────────────────────────────────────────────────────────────
# BUILDING RULES
# ─────────────────────────────────────────────────────────────
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 							      BINARY BUILDING
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
all: compile_lib $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 							      LIB COMPILATION
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
compile_lib_all:
	cd lib && make re && cp libUtilsLib.a ../ && cd ../

compile_lib:
	cd lib && make && cp libUtilsLib.a ../ && cd ../

# ─────────────────────────────────────────────────────────────
# CLEANING RULES
# ─────────────────────────────────────────────────────────────
clean:
	$(REMOVE) $(OBJ) $(OBJ_MAIN) $(OBJ_TEST)

fclean: clean
	$(REMOVE) $(NAME) unit_tests functional_tests ncurses_state libUtilsLib.a hello armbin segf fpe
	for f in $(RM_FILES); do find . -name "$$f" -delete; done
	cd lib && make fclean && cd ../

re: fclean compile_lib_all all

# ─────────────────────────────────────────────────────────────
# TESTING RULES
# ─────────────────────────────────────────────────────────────
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 							  UNIT TESTS BUILDING
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unit_tests: CC = gcc
unit_tests: CFLAGS += $(TEST_FLAGS)
unit_tests: LDFLAGS += $(TEST_LIBS)
unit_tests: $(OBJ) $(OBJ_TEST)
	$(CC) -o unit_tests $^ $(LDFLAGS) $(TEST_FLAGS)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 						FUNCTIONAL TESTS BUILDING
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
functional_tests: CC = gcc
functional_tests: CFLAGS += $(TEST_FLAGS)
functional_tests: LDFLAGS += $(TEST_LIBS)
functional_tests: $(OBJ) $(OBJ_MAIN)
	$(CC) -o functional_tests $^ $(LDFLAGS) $(TEST_FLAGS)

# ─────────────────────────────────────────────────────────────
# RUN TESTS AND GENERATE COVERAGE REPORT
# ─────────────────────────────────────────────────────────────
tests_run: CC = gcc
tests_run: fclean compile_lib unit_tests functional_tests
	./unit_tests
	./tests/tests.sh
	gcovr -b --exclude-directories tests --html-details -o coverage_report.html
	@echo "Coverage report generated: coverage_report.html"
