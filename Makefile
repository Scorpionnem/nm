NAME :=	ft_nm

CC :=	cc
CFLAGS := -MP -MMD -Wall -Wextra -Werror
LFLAGS :=

###

INCLUDE_DIRS :=	inc/		\
				libft/		\

C_SRCS :=	src/main.c		\
			src/header.c	\
			src/map.c		\
			src/parse.c		\
			src/sort.c		\


###

LIBFT = ./libft/libft.a

INCLUDE_DIRS :=	$(addprefix -I, $(INCLUDE_DIRS))

###

OBJ_DIR :=	obj


OBJS =	$(C_SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS =	$(C_SRCS:%.c=$(OBJ_DIR)/%.d)

###

TPUT 					= tput -T xterm-256color
_RESET 					:= $(shell $(TPUT) sgr0)
_BOLD 					:= $(shell $(TPUT) bold)
_ITALIC 				:= $(shell $(TPUT) sitm)
_UNDER 					:= $(shell $(TPUT) smul)
_GREEN 					:= $(shell $(TPUT) setaf 2)
_YELLOW 				:= $(shell $(TPUT) setaf 3)
_RED 					:= $(shell $(TPUT) setaf 1)
_GRAY 					:= $(shell $(TPUT) setaf 8)
_PURPLE 				:= $(shell $(TPUT) setaf 5)

compile: $(LIBFT)
	@make -j all --no-print-directory

all: $(NAME)

$(LIBFT):
	@make -C ./libft all --no-print-directory

$(NAME): $(OBJS)
	@echo 'Linking $(_BOLD)$(NAME)$(_RESET)'
	@$(CC) $(CFLAGS) -no-pie $(LFLAGS) $(INCLUDE_DIRS) -o $@ $^ $(LIBFT)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo 'Compiling $(_BOLD)$<$(_RESET)'
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@
	@echo 'Compiled $(_BOLD)$<$(_RESET)'

re: fclean compile

fclean: clean
	@make -C ./libft fclean --no-print-directory
	@echo 'Removed $(_BOLD)$(NAME)$(_RESET)'
	@rm -rf $(NAME)

clean:
	@make -C ./libft clean --no-print-directory
	@echo 'Removed $(_BOLD)$(OBJ_DIR)$(_RESET)'
	@rm -rf $(OBJ_DIR)

.PHONY: all clean fclean re compile

-include $(DEPS)
