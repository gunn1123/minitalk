# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cthamsur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 15:52:04 by cthamsur          #+#    #+#              #
#    Updated: 2022/08/22 15:19:48 by cthamsur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 CFLAGS = -Wall -Werror -Wextra
 CC = cc
 CLIENT = client
 SERVER = server
 CLIENT_BONUS = client_bonus
 SERVER_BONUS = server_bonus

all: $(CLIENT) $(SERVER)

$(CLIENT) : client.c
				$(CC) $(FLAGS) client.c utils.c -o client
$(SERVER) : server.c
				$(CC) $(FLAGS) server.c utils.c -o server

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS) : client_bonus.c
						$(CC) $(FLAGS) client_bonus.c utils.c -o client_bonus
$(SERVER_BONUS) : server_bonus.c
						$(CC) $(FLAGS) server_bonus.c utils.c -o server_bonus
fclean:
		rm -rf $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

re: fclean all bonus
