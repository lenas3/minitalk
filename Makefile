SERVER_SRC = 	./server/server.c
CLIENT_SRC = 	./client/client.c

OBJS = $(SERVER_SRC:.c=.o) $(CLIENT_SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER = server_exe
CLIENT = client_exe
all : $(SERVER) $(CLIENT)

$(SERVER) : 
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_SRC:.c=.o)

$(CLIENT) :  
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_SRC:.c=.o)
clean :
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(SERVER) $(CLIENT)
re : clean all

.PHONY: all clean fclean re 