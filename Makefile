#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/01 17:23:01 by ckrommen          #+#    #+#              #
#    Updated: 2018/05/06 20:15:23 by ckrommen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRCS = ft_ls.c tools.c sort.c error.c display.c print.c utilities.c free.c

FLAGS = -Wall -Wextra -Werror

NAME = ft_ls

LIBFT = libft

all: $(NAME)

$(NAME):
	@echo "\033[32mCompiling source files\033[0m"
	@make -C $(LIBFT)
	@gcc $(FLAGS) $(SRCS) -L$(LIBFT) -lft -o $(NAME)

clean:
	@echo "\033[32mCleaning up\033[0m"
	@rm -rf $(NAME)
	@make clean -C $(LIBFT)

fclean: clean
	@echo "\033[32mFull clean\033[0m"
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: clean fclean all re