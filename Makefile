CC = cc

CFLAGS = -Wall -Wextra #-Werror

DEBUG = -g

NAME = minishell

SRCSDIR = srcs
OBJSDIR = $(SRCSDIR)/objs

LIBFT = libft/libft.a

SRCS = main utils init_all signal user_parsing exec token_split spliter token_utils token builtin cd env exit export command utils2 free redirection init_all2 pipe pipe_utils dollar_quote dollar_quote_length exit_utils exec_redir utils3 ft_split_modified\

OBJS = $(addprefix $(OBJSDIR)/, $(addsuffix .o, $(SRCS)))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(DEBUG) -Llibft -lft -lm -lreadline -o $(NAME)

$(OBJS): $(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG) -Iincludes -I/usr/include -O3 -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -rf $(OBJSDIR)
	cd libft/ && $(MAKE) clean

fclean:	clean
	rm -f $(NAME)
	cd libft/ && $(MAKE) fclean

re:	fclean all

.PHONY: all libft clean fclean re $(OBJSDIR)
