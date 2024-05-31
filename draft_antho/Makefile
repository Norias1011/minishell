CC = cc

CFLAGS = -Wall -Wextra -Werror

DEBUG = -g

NAME = minishell

SRCSDIR = srcs
OBJSDIR = $(SRCSDIR)/objs

SRCS = main utils init_all signal user_parsing exec init_utils spliter token_utils token builtin \

OBJS = $(addprefix $(OBJSDIR)/, $(addsuffix .o, $(SRCS)))

all: $(NAME)

$(NAME): $(OBJS) libft
	$(CC) $(OBJS) $(CFLAGS) $(DEBUG) -Llibft -lft -lm -lreadline -o $(NAME)

$(OBJS): $(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG) -Iincludes -I/usr/include -O3 -c $< -o $@

libft:
	cd libft/ && $(MAKE) all

clean:
	rm -rf $(OBJSDIR)
	cd libft/ && $(MAKE) clean

fclean:	clean
	rm -f $(NAME)
	cd libft/ && $(MAKE) fclean

re:	fclean all

.PHONY: all libft clean fclean re $(OBJSDIR)
