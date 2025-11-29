SERVER_SRC = 	./server_file/server.c
CLIENT_SRC = 	./client_file/client.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER = server
CLIENT = client

SERVER_OBJS = $(SERVER_SRC:.c=.o)
CLIENT_OBJS = $(CLIENT_SRC:.c=.o)
all : $(SERVER) $(CLIENT)

$(SERVER) : $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJS)

$(CLIENT) :  $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJS)
clean :
	rm -rf $(SERVER_OBJS) $(CLIENT_OBJS)
fclean : clean
	rm -rf $(SERVER) $(CLIENT)
re : clean all

.PHONY: all clean fclean re 

