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
FLAG = -Wall -Wextra -Werror -pthread
HEADER= philo.h
SRC = philo.c utils.c

all: $(NAME)
$(NAME): $(SRC)
	cc $(SRC) -I . $(FLAG) -o $@
clean:
fclean:
	rm $(NAME)
re: fclean all
.PHONY:
	all, $(NAME), clean, fclean, re
