NAME = libft.a

SOURCES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
		ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
		ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putnbr_fd.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c ft_strtrim.c ft_split.c ft_strjoin_free.c free_2d.c ft_putchar.c\
		ft_strcmp.c \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

SOURCESALL = $(SOURCES) $(BONUS)

OBJECTS = $(SOURCES:.c=.o)

OBJECTSALL = $(SOURCESALL:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

%.o : %.c
		@echo Compiling $<
		@$(CC) $(CFLAGS) -o $@ -c $<

all:
	@make -j compile --no-print-directory

compile: $(NAME)

$(NAME): $(OBJECTS)
		@echo Compiling $(NAME)
		@ar rcs $(NAME) $(OBJECTS)

bonus: $(OBJECTSALL)
		@echo Compiling $(NAME)
		@ar rcs $(NAME) $(OBJECTSALL)

clean:
		@rm -f $(OBJECTS) $(OBJECTSALL)

fclean: clean
		@echo Cleaning $(NAME)
		@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
