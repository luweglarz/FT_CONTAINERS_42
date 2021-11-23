NAME = ft_containers.a

CC = clang++

STD = -std=c++98

FLAGS = -Wall -Wextra -Werror

RM = rm -f

SRCS = srcs/ft_map.cpp srcs/ft_stack.cpp srcs/ft_vector.cpp

OBJS = $(SRCS:.cpp=.o)

.cpp.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
	$(CC) $(FLAGS) $(STD) main.cpp $(NAME)
clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) -f $(NAME)
	$(RM) -f a.out

re: fclean all
