SERVER = server
CLIENT = client

SRCS_SERVER	= 	server.c utils.c
OBJS_SERVER  = $(SRCS_SERVER:%.c=%.o)
			
SRCS_CLIENT =	client.c utils.c
OBJS_CLIENT = $(SRCS_CLIENT:%.c=%.o)

RM			= rm -rf
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror


all:		$(SERVER) $(CLIENT)

$(SERVER):	$(OBJS_SERVER)
			$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(SERVER)

$(CLIENT):	$(OBJS_CLIENT)
			$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(CLIENT)

%.o:		%.c minitalk.h Makefile
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) *.o

fclean:		clean
			$(RM) $(SERVER) $(CLIENT)

re:			fclean all

.PHONY:		all clean fclean re