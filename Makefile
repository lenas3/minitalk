SERVER_SRC = 	./mandatory/server.c
CLIENT_SRC = 	./mandatory/client.c
BONUS_CLIENT_SRC = 	./bonus/client_bonus.c
BONUS_SERVER_SRC = 	./bonus/server_bonus.c

CC = cc
CFLAGS = -Wall -Wextra -Werror 

SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

SERVER_OBJS = $(SERVER_SRC:.c=.o)
CLIENT_OBJS = $(CLIENT_SRC:.c=.o)
BONUS_CLIENT_OBJS = $(BONUS_CLIENT_SRC:.c=.o)
BONUS_SERVER_OBJS = $(BONUS_SERVER_SRC:.c=.o)

all : $(SERVER) $(CLIENT) 

$(SERVER) : $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJS)

$(CLIENT) :  $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJS)

$(SERVER_BONUS) :  $(BONUS_SERVER_OBJS)
	$(CC) $(CFLAGS) -o $(SERVER_BONUS) $(BONUS_SERVER_OBJS)

$(CLIENT_BONUS) :  $(BONUS_CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT_BONUS) $(BONUS_CLIENT_OBJS)

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)
clean :
	rm -rf $(SERVER_OBJS) $(CLIENT_OBJS) $(BONUS_CLIENT_OBJS) $(BONUS_SERVER_OBJS)
fclean : clean
	rm -rf $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
re : clean all

.PHONY: all clean fclean re 

