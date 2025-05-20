# *************************************************************************** #
#                                                                             #
#                                                        :::      ::::::::    #
#   Makefile                                           :+:      :+:    :+:    #
#                                                    +:+ +:+         +:+      #
#   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+         #
#                                                +#+#+#+#+#+   +#+            #
#   Created: 2025/04/20 19:04:43 by jtuomi            #+#    #+#              #
#   Updated: 2025/04/20 19:04:43 by jtuomi           ###   ########.fr        #
#                                                                             #
# *************************************************************************** #

NAME = philo
FLAG = -Wall -Wextra -Werror -pthread -O3
HEADER= philo.h
SRC = philo.c utils.c life.c

all: $(NAME)
$(NAME): $(SRC) $(HEADER)
	cc $(SRC) -I . $(FLAG) -o $@
clean:
fclean:
	rm -f $(NAME)
re: fclean all
debug:
	cc -g2 $(SRC) -o $(NAME)
.PHONY:
	all, $(NAME), clean, fclean, re
