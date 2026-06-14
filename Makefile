NAME :=	ft_nm

CC :=	cc
CFLAGS := -g -MP -MMD -Wall -Wextra -Werror
LFLAGS :=

###

INCLUDE_DIRS :=	inc/					\
				libs/libft/				\
				libs/ft_printf/inc/		\

C_SRCS :=	src/main.c			\
			src/header.c		\
			src/map.c			\
			src/parse64.c		\
			src/parse32.c		\
			src/sort.c			\
			src/itoa.c			\


###

LIBFT = ./libs/libft/libft.a
LIBFT_PRINTF = ./libs/ft_printf/libftprintf.a

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

compile: $(LIBFT) $(LIBFT_PRINTF)
	@make -j all --no-print-directory

all: $(NAME)

$(LIBFT):
	@make -C ./libs/libft all --no-print-directory

$(LIBFT_PRINTF):
	@make -C ./libs/ft_printf all --no-print-directory

$(NAME): $(OBJS)
	@echo 'Linking $(_BOLD)$(NAME)$(_RESET)'
	@$(CC) $(CFLAGS) -no-pie $(LFLAGS) $(INCLUDE_DIRS) -o $@ $^ $(LIBFT) $(LIBFT_PRINTF)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo 'Compiling $(_BOLD)$<$(_RESET)'
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@
	@echo 'Compiled $(_BOLD)$<$(_RESET)'

re: fclean compile

fclean: clean
	@make -C ./libs/libft fclean --no-print-directory
	@make -C ./libs/ft_printf fclean --no-print-directory
	@echo 'Removed $(_BOLD)$(NAME)$(_RESET)'
	@rm -rf $(NAME)

clean:
	@make -C ./libs/libft clean --no-print-directory
	@make -C ./libs/ft_printf clean --no-print-directory
	@echo 'Removed $(_BOLD)$(OBJ_DIR)$(_RESET)'
	@rm -rf $(OBJ_DIR)

.PHONY: all clean fclean re compile

-include $(DEPS)
