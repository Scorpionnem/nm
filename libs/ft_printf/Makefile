NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES =	-I ./inc/\
			-I ./libft/

SRCS =	src/ft_printf.c\
		src/numbers.c

OBJDIR = obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS = $(SRCS:%.c=$(OBJDIR)/%.d)

all: $(NAME)

re: fclean all

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re run

-include $(DEPS)
