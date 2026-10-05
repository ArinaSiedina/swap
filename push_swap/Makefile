NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I.

COMMON = utils.c memory.c options.c parse.c stack.c operations.c measure.c
SORT = sort_utils.c sort_simple.c sort_medium.c sort_complex.c benchmark.c
SRCS = main.c $(COMMON) $(SORT)
OBJS = $(SRCS:%.c=.build/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

.build/%.o: %.c push_swap.h Makefile
	@mkdir -p .build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf .build

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

test: all
	python3 tests/test_push_swap.py

.PHONY: all clean fclean re test
