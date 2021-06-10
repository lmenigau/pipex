SRC		= main.c ft_split.c ft_memcpy.c  ft_strncmp.c ft_strjoin.c safeutil.c
OBJ		= $(SRC:.c=.o)
CFLAGS	= -g -Wall -Wextra -fsanitize=address
NAME	= pipex
ifeq  '$(shell ar V 2>/dev/null | head -c 3)' 'GNU'
	ARFLAGS	= Ur
endif

$(NAME) : $(OBJ) 
	$(CC)  -o $(NAME) $(CFLAGS) $(OBJ) 

.PHONY	: re clean fclean all

fclean	: clean
		$(RM) $(NAME)

clean	:
		$(RM) *.o

re		: fclean  all

all		: $(NAME)
